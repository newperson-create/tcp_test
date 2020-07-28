#include "server.hpp"
#include <algorithm>
#include "protocol.hpp"
#include "servercommon.hpp"
#include "messagehandle.hpp"

Server::Server() : m_sock(INVALID_SOCKET), last_pos(0)
{
    memset(msgbuff, 0, sizeof(msgbuff));

    m_msg_handle = new MessageHandle;
}

Server::~Server()
{
    this->CloseSocket();

    if(nullptr != m_msg_handle)
    {
        delete m_msg_handle;
    }
}


bool Server::InitSocket()
{
#ifdef _WIN32
    WORD ver = MAKEWORD(2, 2);
    WSADATA dat;
    WSAStartup(ver, &dat);
#endif
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(INVALID_SOCKET == m_sock)
    {
        DEBUG_LOG("build sock fail!");
        return false;
    }
    else
    {
        DEBUG_LOG("build sock success!");
    }

    if(SOCKET_ERROR == this->Bind())
    {
        this->CloseSocket();
        return false;
    }

    if(SOCKET_ERROR == this->Listen())
    {
        this->CloseSocket();
        return false;
    }

    return true;
}

int Server::Bind(const char* ip, int port)
{
    sockaddr_in _sin = {};
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(port);

    int tmp_ip = 0;
    if(nullptr == ip)
    {
        tmp_ip = INADDR_ANY;
    }
    else
    {
        tmp_ip = inet_addr(ip); 
    }

#ifdef _WIN32
    _sin.sin_addr.S_un.S_addr = tmp_ip;   
#else
    _sin.sin_addr.s_addr = tmp_ip;  
#endif
    int ret = bind(m_sock, (const sockaddr*)&_sin, sizeof(sockaddr_in));
    if(SOCKET_ERROR == ret)
    {
        DEBUG_LOG("bind failed!");
        return SOCKET_ERROR;
    }

    DEBUG_LOG("bind success!");

    return 0;
}

int Server::Listen()
{
    int ret = listen(m_sock, 5);
    if(SOCKET_ERROR == ret)
    {
        DEBUG_LOG("listen failed!");
        return SOCKET_ERROR;
    }

    DEBUG_LOG("listen success!");

    return 0;
}

bool Server::Run()
{
    fd_set fd_read;
    fd_set fd_write;
    fd_set fd_except;

    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    FD_ZERO(&fd_except);

    FD_SET(m_sock, &fd_read);
    FD_SET(m_sock, &fd_write);
    FD_SET(m_sock, &fd_except);

    for(SOCKET sock : m_client_set)
    {
        FD_SET(sock, &fd_read);
    }

    timeval t{0, 0};
    int ret = select(m_sock + 1, &fd_read, &fd_write, &fd_except, &t);
    if(-1 == ret)
    {
        DEBUG_LOG("select error!");
        return false;
    }

    if(FD_ISSET(m_sock, &fd_read))
    {
        FD_CLR(m_sock, &fd_read);

        sockaddr_in _cli = {};
        socklen_t cli_len = sizeof(sockaddr_in);
        SOCKET _cSock = accept(m_sock,(sockaddr*)&_cli, &cli_len);
        if(INVALID_SOCKET == _cSock)
        {
            DEBUG_LOG("accept invalid client socket!");
        }
        else
        {
            m_client_set.insert(_cSock);
            DEBUG_LOG("accept success! IP=%s, socket=%d", inet_ntoa(_cli.sin_addr), _cli.sin_port);
        }
    }

    for(auto set_it = m_client_set.begin(); set_it != m_client_set.end();)
    {
        if(-1 == this->MsgRecv(*set_it))
        {
            // 删除退出的socket
            set_it = m_client_set.erase(set_it);
        }
        else
        {
            ++set_it;
        }
    }

    return true;
}

int Server::MsgRecv(SOCKET sock)
{
    char buff[10240]{};
    int len = recv(sock, buff, sizeof(buff), 0);
    if(len > 0)
    {
        // 处理粘包、黏包
        memcpy(msgbuff + last_pos, buff, len);
        last_pos += len;

        while( last_pos>= sizeof(Protocol::MessageHeader))
        {
            Protocol::MessageHeader* header = (Protocol::MessageHeader*)msgbuff;
            if(last_pos < header->msg_length)
            {
                break;
            }

            m_msg_handle->HandleMessage(sock, msgbuff);

            // 移动缓存数据
            int len = last_pos - header->msg_length;
            memcpy(msgbuff, msgbuff + header->msg_length, len);
            last_pos = len;
        }
    }
	else
	{
		return -1;
	}

    return 0;
}

bool Server::MsgSend(SOCKET sock, const char* buff, int buff_size)
{
    if(nullptr == buff || buff_size < sizeof(Protocol::MessageHeader))
    {
        return false;
    }

    Protocol::MessageHeader* header = (Protocol::MessageHeader*)buff;
    header->msg_length = buff_size;

    send(sock, buff, buff_size, 0);

    return true;
}

void Server::CloseSocket()
{
    if(INVALID_SOCKET != m_sock)
    {
#ifdef _WIN32
        closesocket(m_sock);
#else
        close(m_sock);
        m_sock = INVALID_SOCKET;
#endif
    }

#ifdef _WIN32
        WSACleanup();
#endif
}