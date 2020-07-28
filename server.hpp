#ifndef __MY_SERVER_HPP__
#define __MY_SERVER_HPP__

#ifdef _WIN32
    #include <WinSock2.h>
    #include <windows.h>

    #pragma comment(lib, "ws2_32.lib")   

    #define socklen_t int
#else
    #include <unistd.h>
    #include <arpa/inet.h>

    #define SOCKET  unsigned int
    #define SOCKET_ERROR    -1
    #define INVALID_SOCKET  (SOCKET)(-0)
#endif

#include <set>

class MessageHandle;

class Server
{
public:
    Server();
    virtual ~Server();

    bool InitSocket();

    bool Run();
private:
    int Bind(const char* ip = nullptr, int port = 12700);
    int Listen();

    int MsgRecv(SOCKET sock);
    void CloseSocket();
private:
    SOCKET m_sock;
    std::set<SOCKET> m_client_set;

    char msgbuff[102400];
    int last_pos;

    MessageHandle* m_msg_handle;
};

#endif