#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

void System::update(){
    processes_={};
    Processes();
    proc=-1;
    proc_r=-1;
    return;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    if (processes_.size()==0){
        for (auto x:LinuxParser::Pids()){
            Process t{x};
            if (t.Command().size()<1)
                continue;
            processes_.push_back(t);
        }
    }
    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
    if (kernel==""){
        kernel=LinuxParser::Kernel();
    }
    return kernel;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {
    if (mem_util==-1){
        mem_util=LinuxParser::MemoryUtilization();
    }
    return mem_util;
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    if(this->os==""){
        this->os=LinuxParser::OperatingSystem();
    }
    return this->os;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
    if (proc_r==-1){
        proc_r=LinuxParser::RunningProcesses();
    }
    return proc_r;
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
    if (proc==-1){
        proc=LinuxParser::TotalProcesses();
    }
    return proc;
}

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime();}//not very big so just tunnel