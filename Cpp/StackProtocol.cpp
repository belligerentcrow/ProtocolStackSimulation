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

void Application::printToScreen(std::string m){
    std::cout << "Your message is:\t"<<m<<"!";
}

std::string Application::decode(std::string encoded){
    //decoding through stringstreams in blocks of 8 bits     
    std::stringstream sstream(encoded);
    std::string message;
    while(sstream.good()){
        std::bitset<8> bits;
        sstream>>bits;
        char c = char(bits.to_ulong());
        message+=c;
    }
    return message;
}

void Application::decapsulate(Message m){
    std::cout << "Application Decapsulate\n";
    std::string originalMessg= this->decode(m.payload);
    this->printToScreen(originalMessg);

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
    //std::cout << "Transport Incapsulate\n";
    //if the messages are longer than the maximum length of a segment 
    if(m.payload.length()>this->maxSegmentSize){
        int packNumbers = ceil(m.payload.length()/maxSegmentSize); //then identify how many segments the transport level has to fragment it in
        std::vector<std::string> packPayls=segmentate(m.payload, m.payload.length()); //then segment it and put the segments in a vector
        //std::cout<<"\n Segments: \n";
        //incapsulate each segment in a datagram through internetwork level below
        for(int i = 0; i<packPayls.size(); ++i){
            Segment segm = Segment(packPayls[i], this->source, dest, i); //create segment 
            this->netw->incapsulate(segm); //to internetwork level
        }
    }
}

void Transport::decapsulate(std::vector<Segment> s){
    std::cout << "Transport Decapsulate\n";
    std::string payl;
    //decapsulating all the segments to the original message
    for(int i = 0; i<s.size(); ++i){
        
        payl+=s.at(i).payload;
    }
    std::cout <<"payload back at the transport decapsulation: "<<payl<<'\n';
    //putting the payload inside a message and sending it up - primitive for now
    Message m = (payl);
    this->appl->decapsulate(payl);
}
void Transport::setAppl(Application* appls){
    this->appl = appls;

}
void Transport::setNetw(Internetwork* netwrk){
    this->netw = netwrk;
}

//Internetwork Methods

//converts a "x.x.x.x" kind of string into a xxxx kind of int 
int Internetwork::getIP(std::string ip){ 
    std::string ipconcat ="";
    for(char& c: ip){
        if(c!='.'){
            ipconcat+=c;
        }
    }
    return stoi(ipconcat);
}

Internetwork::Internetwork(std::string ipaddr){
    int v = getIP(ipaddr);
    // convert ipaddr string to bitset
    this->ipAddress = v; 
    //assing to internetwork level: this will be this machine's IP - Assigned at creation only, for now
}

Internetwork::Internetwork(){

}

void Internetwork::incapsulate(Segment s){
    //std::cout << "Internetwork Incapsulate\n";
    Datagram data = Datagram(s, this->ipAddress); //casting from int to bitset with the Datagram creation
    this->netaccs->incapsulate(data);
}

void Internetwork::decapsulate(std::vector<Datagram> d){
    std::cout << "Internetwork Decapsulate\n";
    std::vector<Segment> bunchaSegments;
    //extracting the segments from inside the datagrams and passing them on
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
    //Putting the Datagram inside a frame, putting the frame in the stack
    //std::cout << "NetworkAccess Incapsulate\n";
    Frame f = Frame(d, this->naccs);
    
    putFrameInMemory(f);
    
}

void NetworkAccess::decapsulate(){
    //using a vector 
    std::vector<Datagram> bunchaDatagrams;
    std::cout << "NetworkAccess Decapsulate\n";

    bool emptyStack = false;
    //assuming to have full control of the stack - and to have only one message at a time. for now
    std::cout<<"Payloads inside the frames inside the stack:\n";
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