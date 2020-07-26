#ifndef __MY_SERVER_HPP__
#define __MY_SERVER_HPP__

#ifdef _WIN32
    #include <WinSock2.h>
    #include <windows.h>

    #pragma comment(lib, ws2_32.lib);
#else
    #include <unistd.h>
    #include <arpa/inet.h>

    #define SOCKET  unsigned int
    #define SOCKET_ERROR    -1
    #define INVALID_SOCKET  (SOCKET)(-0)
#endif

#include "servercommon.hpp"
#include <set>
#include <map>
#include <functional>

class Server
{
public:
    Server();
    ~Server();

    bool InitSocket();

    bool Run();
private:
    int Bind(const char* ip = nullptr, int port = 12700);
    int Listen();

    int MsgHandler(SOCKET sock);
    void CloseSocket();
private:
    SOCKET m_sock;
    std::set<SOCKET> m_client_set;

    char msgbuff[102400];
    int last_pos;
};

#endif