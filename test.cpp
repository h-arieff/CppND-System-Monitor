#include "system.h"
#include <iostream>
int main(){
    System s;
    std::cout<<s.Processes()[0].CpuUtilization()<<std::endl;
}