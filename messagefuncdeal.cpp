#include "messagehandle.hpp"
#include "servercommon.hpp"
#include "msgcode.hpp"

void MessageHandle::OnTest(void* msg)
{
    if(nullptr == msg) return;

    Protocol::Test* info = (Protocol::Test*)msg;

    DEBUG_LOG("a=%hd,b=%hd", info->a, info->c);
}