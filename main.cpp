#include "server.hpp"
#include "servercommon.hpp"
#include "engineadapter.hpp"

int main(int, char**) 
{
    Server server;
    bool is_init = server.InitSocket();
    
    EngineAdapter::Instance().Init(&server);

    while(is_init)
    {
        if(!server.Run())
        {
            ERROR_LOG("return");
            break;
        }
    }
}
