#include <string>
#include <iostream> 
#include <cstring>
#include <stack>
#include "PDUs.h"
#include "Protocols.h"
class Frame;
class Device{
    public:
    std::stack<Frame> * sharedStack;
    Application app;
    Transport transp;
    Internetwork internetw;
    NetworkAccess netwacc;
    std::string deviceName;
    Device(std::string name, std::string ip, std::stack<Frame> * stack);

    void sendMessage(std::string str);
    void receiveMessage();

};