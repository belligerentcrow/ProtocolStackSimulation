#include <string>
class Application;
class Transport;
class Internetwork;
class NetworkAccess;

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
        void incapsulate(Message m, std::string d);
        void decapsulate();
        void setAppl(Application* appls);
        void setNetw(Internetwork* netwk);
        Transport(std::string src);
        Transport(){};
};

class Internetwork : public Protocol{
        Transport * transp;
        NetworkAccess * netaccs;
    public:
        void incapsulate(Segment s);
        void decapsulate();
        void setTransp(Transport* transprt);
        void setNetAcc(NetworkAccess* netaccess);
};

class NetworkAccess : public Protocol{
        Internetwork *netwk;
    public:
    void incapsulate();
    void decapsulate();
    void setNetw(Internetwork* internetwk);
};