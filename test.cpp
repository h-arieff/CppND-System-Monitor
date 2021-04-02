#include "system.h"
#include <iostream>
int main(){
    System s;
    std::cout<<s.Processes()[0].Ram()<<std::endl;
}