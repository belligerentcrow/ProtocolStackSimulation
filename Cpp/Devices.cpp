#include "Devices.h"
#include <string>
#include <bitset>
#include <stack>
//#include <sys/
//#include <netinet/in.h>

class Frame;

Device::Device(std::string name, std::string ip, std::stack<Frame> * sharedStack){
    this->deviceName = name;
    this->sharedStack = sharedStack;

    //create levels
    this->app = Application();
    this->internetw = Internetwork(ip);
    this->netwacc = NetworkAccess(12121);
    this->transp = Transport("29303");

    //give references
    app.setTransp(&transp);
    transp.setAppl(&app);
    transp.setNetw(&internetw);
    internetw.setTransp(&transp);
    internetw.setNetAcc(&netwacc);
    netwacc.setNetwAndStack(&internetw,sharedStack);
}

void Device::sendMessage(std::string str){
    this->app.incapsulate(str, "8080");
}
void Device::receiveMessage(){
    this->netwacc.decapsulate();
}

int main(int argc, char *argv[]){
    std::stack<Frame> sharedStack = std::stack<Frame>();
    std::stack<Frame> * stackp = &sharedStack; 
    std::cout<<"Create device\n";
    Device d1("computer1", "151.92.39.15",stackp);
    Device d2("computer2", "123.234.2.1",stackp);
    std::cout<<"Sending message\n";
    d1.sendMessage("hello world");
    d2.receiveMessage();
    //std::cout <<"\nworks?\n";
}