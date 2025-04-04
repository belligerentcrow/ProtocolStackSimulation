#include "Devices.h"
#include <string>

Device::Device(std::string name){
    //create levels
    this->app = Application();
    this->deviceName = name;
    this->internetw = Internetwork();
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
    this->app.incapsulate(str);
}

int main(){
    Device d1("computer1");
    d1.app.incapsulate("hello");
    std::cout <<"works?";
}