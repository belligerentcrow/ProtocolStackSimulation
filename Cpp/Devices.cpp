#include "Devices.h"
#include <string>
#include <bitset>
#include <stack>

class Frame; //forward declaration 

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

    std::stack<Frame> sharedStack = std::stack<Frame>(); //creating a shared stack for the devices
    std::stack<Frame> * stackp = &sharedStack;  // pointer to the stack
    std::cout<<"Creating devices\n";
    Device d1("computer1", "151.92.39.15",stackp);
    Device d2("computer2", "123.234.2.1",stackp);
    
    std::string x = "hello world";
    std::cout<<"Sending message:"<< x <<"\n";
    d1.sendMessage(x);
    std::cout<<"\t\n";
    std::cout<<"Receiving message from second device:"<<"\n";
    d2.receiveMessage();
}