#include "debuglog.hpp"
#include "stdarg.h"

DebugLog::DebugLog(const char* file)
{
    if(nullptr == file)
    {
        return;
    }

    str = "./log/";
    str += file;    
}

void DebugLog::Print(const char* format, ...)
{
    FILE* file = fopen(str.c_str(), "a");
    if(nullptr == file)
    {
        return;
    }

    va_list args;
    va_start(args, format);
    vfprintf(file, format, args);
    va_end(args);

    fclose(file);
}