#include <string>
#include <cstring>
#include <stdlib.h>
#include <bitset>

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
    Segment(){};
};

class Datagram : public PDU{
    public:
    std::bitset<32> ip_add;
    Segment myseg;
    Datagram(Segment s, std::bitset<32> a){
        this->myseg = s;
        this->ip_add=a;
    }
    Datagram(){};

};

class Frame : public PDU{
    public:
    int header;
    int padding;
    Datagram datg;
    Frame(Datagram d, int na){
        this->datg=d;
        this->header=12121;
        this->padding=-1;
    }
    Frame(){}
};