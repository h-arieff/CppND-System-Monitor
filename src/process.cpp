#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <pwd.h>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int p){
    pid=p;
    status=LinuxParser::getStatus(*this);
}


// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return LinuxParser::CpuUtilization(*this);; }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(*this); }

// TODO: Return this process's memory utilization
long Process::Ram() {
    std::stringstream ss{status["VmSize:"]};
    long ret;
    ss>>ret;
    return ret;
}

// TODO: Return the user (name) that generated this process
string Process::User() {
    if (user==""){
        struct passwd *pswd;
        std::stringstream ss{status["Uid:"]};
        int uid;
        ss>>uid;
        pswd=getpwuid(uid);
        user=pswd->pw_name;
    }
    return user;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
    return LinuxParser::UpTime(*this);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process &a )  { return Ram()<a.Ram(); }