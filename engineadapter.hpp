#ifndef __ENGINE_ADAPTER_HPP__
#define __ENGINE_ADAPTER_HPP__

class EngineAdapter
{
public:
    bool Send(unsigned int sock, const char* buff, int len);

private:
};

#endif