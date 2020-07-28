#ifndef __MSGCODE_HPP__
#define __MSGCODE_HPP__

#include "protocol.hpp"

namespace Protocol{

    enum PROTOCOL_MSG_TYPE
    {
        MSG_TEST = 0,

        MSG_TYPE_END,
    };

class Test
{
public:
    MessageHeader header = MSG_TEST;

    short a = 0;
    short c = 0;
};

}

#endif