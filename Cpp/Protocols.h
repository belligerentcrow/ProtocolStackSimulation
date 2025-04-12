#include <string>
#include <vector>
#include <bitset>
#include <stack>
class Application;
class Transport;
class Internetwork;
class NetworkAccess;
class Message;
class Segment;
class Datagram;
class Frame;


class Protocol{
    public:
    void incapsulate();
    void decapsulate();
};


class Application : public Protocol{
        Transport * tr;
    public:
        void incapsulate(std::string str, std::string d);
        std::string decode(std::string encode);
        void decapsulate(Message m);
        void setTransp(Transport * transp);
        void printToScreen(std::string s);
        
};

class Transport : public Protocol{
    private: 
        std::string source;
        std::string dest;
        int maxSegmentSize=32;
        std::vector<std::string> segmentate(std::string s, int num);
        Application * appl;
        Internetwork *netw;
    public:
        void incapsulate(Message m, std::string dest);
        void decapsulate(std::vector<Segment> s);
        void setAppl(Application* appls);
        void setNetw(Internetwork* netwk);
        Transport(std::string src);
        Transport(){};
};

//Note: the initial idea was to create InternetWork with the sockaddr_in struct. 
//Idea abandoned due to Linux - Windows network interface incompatibilities. 
class Internetwork : public Protocol{
        Transport * transp;
        NetworkAccess * netaccs;
        int ipAddress;
        int getIP(std::string ip);
    public:
        void incapsulate(Segment s);
        void decapsulate(std::vector<Datagram> d);
        void setTransp(Transport* transprt);
        void setNetAcc(NetworkAccess* netaccess);
        Internetwork(std::string ip);
        Internetwork();
        
};

class NetworkAccess : public Protocol{
        Internetwork *netwk;
        std::stack<Frame> * datastack;
        int naccs;
    public:
    void incapsulate(Datagram d);
    void decapsulate();
    void setNetwAndStack(Internetwork* internetwk, std::stack<Frame> * stk);
    void putFrameInMemory(Frame f);
    NetworkAccess(int naccsAddr);
    NetworkAccess();
};