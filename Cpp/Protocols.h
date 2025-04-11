#include <string>
#include <vector>
#include <bitset>
class Application;
class Transport;
class Internetwork;
class NetworkAccess;
class Message;
class Segment;

class Protocol{
    public:
    void incapsulate();
    void decapsulate();
};


class Application : public Protocol{
        Transport * tr;
    public:
        void incapsulate(std::string str, std::string d);
        void decapsulate();
        void setTransp(Transport * transp);
        
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
        void decapsulate();
        void setAppl(Application* appls);
        void setNetw(Internetwork* netwk);
        Transport(std::string src);
        Transport(){};
};

class Internetwork : public Protocol{
        Transport * transp;
        NetworkAccess * netaccs;
        std::bitset<32> ipAddress;

    public:
        void incapsulate(Segment s);
        void decapsulate();
        void setTransp(Transport* transprt);
        void setNetAcc(NetworkAccess* netaccess);
        Internetwork(sockaddr_in ip)
        
};

class NetworkAccess : public Protocol{
        Internetwork *netwk;
    public:
    void incapsulate();
    void decapsulate();
    void setNetw(Internetwork* internetwk);
};