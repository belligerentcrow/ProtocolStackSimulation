#include "Protocols.h"
#include <string>
#include "PDUs.h"
#include <bitset>
#include <iostream>
#include <cmath>
#include <vector>
#include <arpa/inet.h>

// Application Methods
void Application::incapsulate(std::string msg, std::string dest){
    std::string encodedString;
    for(char& _char : msg){
        encodedString+=std::bitset<8>(_char).to_string();
    }
    //std::cout<<encodedString;
    Message message(encodedString);
    this->tr->incapsulate(message, dest);

    
}
void Application::decapsulate(){

}
void Application::setTransp(Transport* transp){
    this->tr = transp;

}

//Transport Methods


Transport::Transport(std::string src){
    this->source = src;
}


//Add zeroes trailing after last packet? 
std::vector<std::string> Transport::segmentate(std::string s, int num){
    std::vector<std::string> v;
    for(int i =0; i<num;i+=maxSegmentSize){
        v.push_back(s.substr(i,this->maxSegmentSize));
    }
    return v;
}

void Transport::incapsulate(Message m, std::string dest){

    if(m.payload.length()>this->maxSegmentSize){
        int packNumbers = ceil(m.payload.length()/maxSegmentSize);
        std::vector<std::string> packPayls=segmentate(m.payload, m.payload.length());
        std::cout<<"\n Segments: \n";
        for(int i = 0; i<packPayls.size(); ++i){
            std::cout << packPayls[i]<<"\n";
            Segment segm = Segment(packPayls[i], this->source, dest, i);
            this->netw->incapsulate(segm);
        }
    }
}

void Transport::decapsulate(){
    
}
void Transport::setAppl(Application* appls){
    this->appl = appls;

}
void Transport::setNetw(Internetwork* netwrk){
    this->netw = netwrk;
}

//Internetwork Methods

Internetwork::Internetwork(sockaddr_in ipaddr){
    char *some_addr = inet_atoa(ipaddr.sin_addr);
    std::bitset<32> bitIP =std::bitset<32>(some_addr).to_string();
    this->ipAddress = bitIP;

}

void Internetwork::incapsulate(Segment s){
    Datagram data = Datagram(s, this->ipAddress);
    this->netw->incapsulate(data);
}

void Internetwork::decapsulate(){
    
}

void Internetwork::setTransp(Transport* transprt){
    this->transp = transprt;
}
void Internetwork::setNetAcc(NetworkAccess* netaccess){
    this->netaccs = netaccess;
}

//NetworkAccess Methods
void NetworkAccess::incapsulate(){
    
}
void NetworkAccess::decapsulate(){
    
}

void NetworkAccess::setNetw(Internetwork* interntw){
    this->netwk = interntw;
}