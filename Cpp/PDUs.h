#include <string>
#include <cstring>

class PDU{
    public:
    std::string payload;
    std::string source;
    std::string destination;
};


class Message : public PDU{
    //std::string extension;

    public:
    Message(std::string msg){
        this->payload = msg;
    }
    
};

class Segment : public PDU{
    int seqNumber;
    public:
    Segment(std::string p, std::string src, std::string dst, int sqnmb){
        this->payload = p;
        this->source = src;
        this->destination = dst;
        this->seqNumber= sqnmb;
    }
};

class Datagram : public PDU{

};

class Frame : public PDU{

};