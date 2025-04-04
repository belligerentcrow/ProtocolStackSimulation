#include <string>
#include <iostream> 
#include <cstring>
#include "PDUs.h"
#include "Protocols.h"

class Device{
    public:
    Application app;
    Transport transp;
    Internetwork internetw;
    NetworkAccess netwacc;
    std::string deviceName;
    Device(std::string name);

    void sendMessage(std::string str);

};