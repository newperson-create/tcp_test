#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

namespace{

class MessageHeader
{
public:
    MessageHeader(){}
    MessageHeader(short tmp) : header(tmp){}

    short header = 0;
    short msg_length = 0;
};



}

#endif