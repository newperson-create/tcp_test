#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

namespace Protocol{

class MessageHeader
{
public:
    MessageHeader(){}
    MessageHeader(short tmp) : msg_type(tmp){}

    short msg_type = 0;
    short msg_length = 0;
};



}

#endif