#include "messagehandle.hpp"
#include "servercommon.hpp"
#include "msgcode.hpp"
#include "engineadapter.hpp"

void MessageHandle::OnTest(SOCKET sock, void* msg)
{
    if(nullptr == msg) return;

    Protocol::Test* info = (Protocol::Test*)msg;

    DEBUG_LOG("a=%hd,b=%hd", info->a, info->c);

	Protocol::Test t;
	t.a = 2000;
	t.c = 3000;
	t.header.msg_length = sizeof(Protocol::Test);

	EngineAdapter::Instance().Send(sock, (const char*)&t, sizeof(Protocol::Test));
}