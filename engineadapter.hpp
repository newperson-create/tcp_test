#ifndef __ENGINE_ADAPTER_HPP__
#define __ENGINE_ADAPTER_HPP__

class Server;

class EngineAdapter
{
public:
    static EngineAdapter& Instance();

    void Init(Server* _server);

    bool Send(unsigned int sock, const char* buff, int len);
private:
    EngineAdapter(){};
    EngineAdapter(const EngineAdapter& other) = delete;
    EngineAdapter& operator=(const EngineAdapter& other) = delete;

private:
    Server *m_server;
};

#endif