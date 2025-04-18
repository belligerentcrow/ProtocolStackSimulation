TODO
* Implement some "input" syntax check  
    * es: check for correct IP format
* Let IP Addr and string to send be collected from CLI user input 
  * add CHECKS! especially characters to bitset, 
    be sure input is cast compliant
* Fix trailing spaces in `StackProtocol.cpp`
* Maybe program checksum methods at Transport Level  
* Use seqNumber to desegment in Transport Level. 
  * seqNumber should represent bytes, not number of segments
* Incapsulate payload more "realistically" 
    in Internetwork and NetworkAccess Levels.
* Change the way Device 1 and 2 exchange Frames.
  * Avoid Shared Stack. Create 2 separate Stacks 
