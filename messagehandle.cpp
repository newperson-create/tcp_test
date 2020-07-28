#include "messagehandle.hpp"
#include "protocol.hpp"
#include "servercommon.hpp"
#include "msgcode.hpp"

MessageHandle::MessageHandle()
{
    memset(m_msg_handle_list, 0, sizeof(m_msg_handle_list));
    
    m_msg_handle_list[Protocol::MSG_TEST] = HandleItem(&MessageHandle::OnTest, sizeof(Protocol::Test));
}

void MessageHandle::HandleMessage(void* msg)
{
    Protocol::MessageHeader* header = (Protocol::MessageHeader*)msg;
    if(header->msg_type < 0 || header->msg_type >= MAX_MSG_TYPE)
    {
        return;
    }

    // 检查是否有处理接口
    int msg_type = static_cast<int>(header->msg_type);
    if(nullptr == m_msg_handle_list[msg_type].func)
    {
        return;
    }

    // 检查协议长度
    int length = m_msg_handle_list[msg_type].data_size;
    if(header->msg_length < length)
    {
        ERROR_LOG("msg_type=[%d], length error! recv_length=[%d], length=[%d]",
            msg_type, header->msg_length, length);
        return;
    }

    // 调用协议处理函数
    (this->*m_msg_handle_list[msg_type].func)(msg);
}