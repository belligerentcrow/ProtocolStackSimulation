# ProtocolStackSimulation
A simulation of the TCP-IP Protocol Stack written in C++. Computer Networks UniCT Exercise.

### C++ version

The protocols are defined in the `Protocols.h` header, and implemented in the `StackProtocol.cpp` file.  
The PDUs (Message, Segment, etc) are defined and implemented in the `PDUs.h` header.   
The Device class is defined in the `Devices.h` header, and implemented in the `Devices.cpp` file.  
  
The `main` is in `Devices.cpp`. When one invokes the Device method `sendMessage()`, the message will travel through all the layers: it will be incapsulated on its way down, and segmented at the Transport Layer. It will be deposited on the shared stack, which is for now a stack of Frames.  

When one invokes the Device method `receiveMessage()`, the NetworkAccess level of the Device will take the frames from the Shared Stack, and decapsulate them all the way up to the Application level, which will then decode the message back to ASCII characters and print it to screen.
  
`Devices.cpp` and `StackProtocol.cpp` should be compiled together. (`$g++ Devices.cpp StackProtocol.cpp` then `\a.out` or `\a.exe` if you are a Windows user.)

TODO:   
* TODO