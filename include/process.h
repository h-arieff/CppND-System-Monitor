#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <unordered_map>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid(){
      return pid;
  }
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  long Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process & a);  // TODO: See src/process.cpp
  operator std::string()const{return std::to_string(pid);}
  // TODO: Declare any necessary private members
  std::unordered_map<std::string,std::string> status;
 private:
    float util{0};
    int pid;
    std::string user{""};
    std::string command;
};

#endif