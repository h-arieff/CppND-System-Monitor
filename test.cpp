#include "system.h"
#include <iostream>
int main(){
    System s;
    std::cout<<s.MemoryUtilization()<<std::endl;
    std::cout<<s.RunningProcesses()<<std::endl;
    std::cout<<s.UpTime()<<std::endl;
}