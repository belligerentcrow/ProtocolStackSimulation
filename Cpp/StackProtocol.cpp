#include "Protocols.h"
#include <string>
#include "PDUs.h"
#include <bitset>
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
//#include <arpa/inet.h>
//#include <ws2tcpip.h>
//#include <winsock2.h>
#include <stack>

// Application Methods
void Application::incapsulate(std::string msg, std::string dest){
    std::cout << "Application Incapsulate\n";
    std::string encodedString;
    for(char& _char : msg){
        encodedString+=std::bitset<8>(_char).to_string();
    }
    //std::cout<<encodedString;
    Message message(encodedString);
    this->tr->incapsulate(message, dest);

    
}

void Application::decode(std::string encoded){
    /*
    unsigned long i= stoi(encoded);
    std::string message;
    for(int i = 0; i <encoded.length(); ++i){
        message[i] =static_cast<unsigned char>(encoded[i]); 
    }
    std::cout<<message;
    */
    
    std::stringstream sstream(encoded);
    std::string message;
    while(sstream.good()){
        std::bitset<8> bits;
        sstream>>bits;
        char c = char(bits.to_ulong());
        message+=c;
    }
    std::cout << message;

}

void Application::decapsulate(std::string s){
    std::cout << "Application Decapsulate\n";
    this->decode(s);

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
    std::cout << "Transport Incapsulate\n";
    //if the message bytes are longer than the maximum length of a segment 
    if(m.payload.length()>this->maxSegmentSize){
        int packNumbers = ceil(m.payload.length()/maxSegmentSize); //then identify how many segments the transport level has to fragment it in
        std::vector<std::string> packPayls=segmentate(m.payload, m.payload.length()); //then segment it and put the segments in a vector
        //std::cout<<"\n Segments: \n";
        //incapsulate each segment in a datagram through internetwork level below
        for(int i = 0; i<packPayls.size(); ++i){
            std::cout << packPayls[i]<<"\n";
            Segment segm = Segment(packPayls[i], this->source, dest, i); //create segment 
            this->netw->incapsulate(segm); //to internetwork level
        }
    }
}

void Transport::decapsulate(std::vector<Segment> s){
    std::cout << "Transport Decapsulate\n";
    std::string payl;
    std::cout <<"payload at transport: "<<payl<<", segment number: "<<s.size()<<'\n';
    for(int i = 0; i<s.size(); ++i){
        
        payl+=s.at(i).payload;
    }
    std::cout <<"payload at transport: "<<payl<<", segment number: "<<s.size()<<'\n';
    this->appl->decapsulate(payl);
}
void Transport::setAppl(Application* appls){
    this->appl = appls;

}
void Transport::setNetw(Internetwork* netwrk){
    this->netw = netwrk;
}

//Internetwork Methods

int getIP(std::string ip){

    std::string ipconcat ="";
    for(char& c: ip){
        if(c!='.'){
            ipconcat+=c;
        }
    }
    std::cout<<ipconcat;
    return stoi(ipconcat);
}

Internetwork::Internetwork(std::string ipaddr){
    /* 
    //Initial plan to convert IP to 32bitset
    char *some_addr = inet_atoa(ipaddr.sin_addr);
    std::bitset<32> bitIP = std::bitset<32>(some_addr).to_string();
    this->ipAddress = bitIP;*/
    
    int v = getIP(ipaddr);
    
    
    // convert ipaddr string to bitset
    this->ipAddress = v; //assing to internetwork level: this will be this machine's IP - Assigned at creation only, for now
}

Internetwork::Internetwork(){

}

void Internetwork::incapsulate(Segment s){
    std::cout << "Internetwork Incapsulate\n";
    Datagram data = Datagram(s, this->ipAddress);
    this->netaccs->incapsulate(data);
}

void Internetwork::decapsulate(std::vector<Datagram> d){
    std::cout << "Internetwork Decapsulate\n";
    std::vector<Segment> bunchaSegments;
    std::cout <<"segment number at internetwork: "<<d.size()<<'\n';
    for(int i = d.size()-1; i >=0; --i){
        bunchaSegments.push_back(d.at(i).myseg);
    }
    this->transp->decapsulate(bunchaSegments);
}

void Internetwork::setTransp(Transport* transprt){
    this->transp = transprt;
}
void Internetwork::setNetAcc(NetworkAccess* netaccess){
    this->netaccs = netaccess;
}

//NetworkAccess Methods

void NetworkAccess::putFrameInMemory(Frame f){
    this->datastack->push(f);
}

void NetworkAccess::incapsulate(Datagram d){
    std::cout << "NetworkAccess Incapsulate\n";
    Frame f = Frame(d, this->naccs);
    
    putFrameInMemory(f);
    
}
void NetworkAccess::decapsulate(){
   
    std::vector<Datagram> bunchaDatagrams;
    std::cout << "NetworkAccess Decapsulate\n";
    bool emptyStack = false;
    while(!emptyStack){
        if(!(this->datastack->empty())){
             Frame f = this->datastack->top();
             std::cout<<f.datg.myseg.payload<<"\n";
             bunchaDatagrams.push_back(f.datg);
             this->datastack->pop();
             
        }else{
            emptyStack = true;
        }
    }
    
    this->netwk->decapsulate(bunchaDatagrams);
}

void NetworkAccess::setNetwAndStack(Internetwork* interntw, std::stack<Frame> * st){
    this->netwk = interntw;
    this->datastack = st;
    
}

NetworkAccess::NetworkAccess(int na){
    this->naccs =na;
}

NetworkAccess::NetworkAccess(){

}