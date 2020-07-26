#ifndef __MSGCODE_HPP__
#define __MSGCODE_HPP__

#include "protocol.hpp"

namespace{

class Test
{
public:
    MessageHeader header = 9;

    short a = 0;
    short c = 1;
};

}

#endif