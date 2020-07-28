#include "engineadapter.hpp"
#include "server.hpp"

EngineAdapter& EngineAdapter::Instance()
{
    static EngineAdapter instance;
    return instance;
}

void EngineAdapter::Init(Server* _server)
{
    if(nullptr == _server)
    {
        return;
    }

    m_server = _server;
}

bool EngineAdapter::Send(unsigned int sock, const char* buff, int len)
{
    return m_server->MsgSend(static_cast<SOCKET>(sock), buff, len);
}