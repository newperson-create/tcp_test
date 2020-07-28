#ifndef __DEBUG_LOG_HPP__
#define __DEBUG_LOG_HPP__

#include <string>

class DebugLog
{
public:
    DebugLog(const char* file);

    void Print(const char* format, ...);
private:
    std::string str;
};

#endif