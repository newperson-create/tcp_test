#ifndef __MESSAGE_HANDLE_HPP__
#define __MESSAGE_HANDLE_HPP__
#include <limits.h>

class MessageHandle
{
public:
    MessageHandle();

    void HandleMessage(void* msg);
protected:
    typedef void (MessageHandle::*HandleFunc)(void* msg);

    struct HandleItem
    {
        HandleItem() : func(0), data_size(0) {}
        HandleItem(HandleFunc f, int d) : func(f), data_size(d) {}

        HandleFunc  func;
        int         data_size;
    };
    
    HandleItem m_msg_handle_list[MAX_MSG_TYPE];
};

#endif