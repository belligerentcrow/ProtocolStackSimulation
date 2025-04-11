#include "Devices.h"
#include <string>
#include <bitset>
#include <sys/
#include <netinet/in.h>

Device::Device(std::string name){
    //create levels
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    inet_aton("151.97.34.220", &myaddr.sin_addr.s_addr);
    
    this->app = Application();
    this->deviceName = name;
    this->internetw = Internetwork(sockaddr_in myaddr);
    this->netwacc = NetworkAccess();
    this->transp = Transport("29303");

    //give references
    app.setTransp(&transp);
    transp.setAppl(&app);
    transp.setNetw(&internetw);
    internetw.setTransp(&transp);
    internetw.setNetAcc(&netwacc);
    netwacc.setNetw(&internetw);
}

void Device::sendMessage(std::string str){
    this->app.incapsulate(str, "8080");
}

int main(int argc, char *argv[]){
    Device d1("computer1");
    d1.sendMessage("hello");
    std::cout <<"\nworks?\n";
}