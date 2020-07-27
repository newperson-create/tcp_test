#include "server.hpp"
#include "servercommon.hpp"

int main(int, char**) 
{
    Server server;
    bool is_init = server.InitSocket();

    while(is_init)
    {
        if(!server.Run())
        {
            ERROR_LOG("return");
            break;
        }
    }
}
