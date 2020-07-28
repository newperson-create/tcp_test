#ifndef __SERVER_COMMOM_HPP__
#define __SERVER_COMMOM_HPP__

#include <iostream>
#include <time.h>
#include <cstring>

#define MYTIMER MyTimer::Instance()

class MyTimer
{
public:

    static MyTimer& Instance()
    {
        static MyTimer instance;
        return instance;
    }

    const char* GetTimeFormat(unsigned int timestamp = 0)
    {
        time_t now_time = time(nullptr);
        if(0 != timestamp)
        {
            now_time = static_cast<time_t>(timestamp);
        }

        struct tm t;
#ifdef _WIN32
        ::localtime_s(&t, &now_time);
#else
        ::localtime_r(&now_time, &t);
#endif
        strftime(m_time_format, sizeof(m_time_format), "%Y-%m-%d %H:%M:%S", &t);

        return m_time_format;
    }

private:
    MyTimer()
    {
        memset(m_time_format, 0, sizeof(m_time_format));
    }

    MyTimer(const MyTimer& other) = delete;
    MyTimer& operator=(const MyTimer& other) = delete;
private:
    char m_time_format[64];
};

#define NONE            "\033[m"
#define GREEN           "\033[0;32m"
#define LIGHT_RED       "\033[1;31m"

#define DEBUG_LOG(format, ...) \
    printf(GREEN"[%s] " format NONE"\n", MYTIMER.GetTimeFormat(), ##__VA_ARGS__); 
#define ERROR_LOG(format, ...) \
    printf(LIGHT_RED"[%s] " format NONE"\n", MYTIMER.GetTimeFormat(), ##__VA_ARGS__); 


#endif