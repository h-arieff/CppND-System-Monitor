#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <pwd.h>

#include "linux_parser.h"
#include "process.h"
namespace fs=std::filesystem;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

bool mem_parsed=false;
std::unordered_map<std::string,float> mem_map;
bool stat_parsed=false;
std::unordered_map<std::string,std::vector<int>> stat_map;
// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

void parse_stat(bool u=false){
  if (stat_parsed&&u){
    return;
  }
  std::ifstream f{LinuxParser::kProcDirectory+LinuxParser::kStatFilename};
  std::string line,key;
  std::vector<int> v;
  int t;
  while (std::getline(f,line)){
    v={};
    std::stringstream s{line};
    s>>key;
    while (s>>t){
      v.push_back(t);
    }
    stat_map[key]=v;
  }
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids{};
  //DIR* directory = opendir(kProcDirectory.c_str());
  //struct dirent* file;
  
  for (auto file:fs::directory_iterator(kProcDirectory) ){
    // Is this a directory?

    auto pth = file.path();
    if (fs::is_directory(pth)) {
      // Is every character of the name a digit?
      string filename=pth.filename();
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization(bool u) {//this compicated method is used in case future functinality is ever added
  //for example a better method of calculating utilized memory
  if (mem_parsed &&!u){
    float MemTotal=mem_map["MemTotal"];
    float MemFree=mem_map["MemFree"];
    return (MemTotal-MemFree)/MemTotal;
  }
  std::ifstream f{kProcDirectory+kMeminfoFilename};
  string line;
  string key;
  int value;
  while (std::getline(f,line)){
    std::replace(line.begin(),line.end(),':',' ');
    std::istringstream ss(line);
    ss>>key>>value;
    mem_map[key]=value;
  }
  mem_parsed=true;
  return LinuxParser::MemoryUtilization(false);
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  std::ifstream f{kProcDirectory+kUptimeFilename};
  int up1;
  f>>up1;
  return up1;
}


// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(Process p[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
int LinuxParser::CpuUtilization() {
  parse_stat();
  int tt=0;
  for (auto& n : stat_map["cpu"])
    tt += n;
  return 1.0-(stat_map["cpu"][3]/tt);
}
long double LinuxParser::CpuUtilization(Process p) {
  std::ifstream f{kProcDirectory+to_string(p.Pid())+kStatFilename};
  string token;
  for (int i=0;i<14;i++){
    f>>token;
  }
  float utime,stime,tt,cutime,cstime,starttime=LinuxParser::UpTime(p),seconds,uptime=LinuxParser::UpTime();
  f>>utime>>stime>>cutime>>cstime;

  long hertz=sysconf(_SC_CLK_TCK);
  tt = utime + stime;
  tt = tt + cutime + cstime;
  seconds = uptime - (starttime / hertz);
  long double t=10.0*((tt / hertz) / seconds);
  return t;
}
// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  parse_stat();
  return stat_map["processes"][0];
}


// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  parse_stat();
  return stat_map["procs_running"][0];
}
std::unordered_map<string,string> LinuxParser::getStatus(Process p[[maybe_unused]]){
  std::unordered_map<string,string> ret;
  std::ifstream f{kProcDirectory+p.operator std::string()+kStatusFilename};
  string line;
  std::string key,value;
  while (std::getline(f,line)){
    std::stringstream ss{line};
    ss>>key;
    if (key.size()==0){
      continue;
    }
    getline(ss,value);
    ret[key]=value;
  }
  return ret;
}
// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(Process p) {
  std::ifstream f{kProcDirectory+to_string(p.Pid())+kCmdlineFilename};
  std::string line;
  if (getline(f,line)){
    return line;
  }
  return string();
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the functio

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
/*
string LinuxParser::Uid(Process p) {
  return p.status["Uid:"];
}
*/
// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
/*
string LinuxParser::User(Process p) {
  struct passwd *pswd;
  std::stringstream ss{p.status["Uid:"]};
  int uid;
  ss>>uid;
  pswd=getpwuid(uid);
  return pswd->pw_name;
}
*/
// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(Process p) {
  std::ifstream f{kProcDirectory+to_string(p.Pid())+kStatFilename};
  std::string val;
  long ret;
  for (int i=0;i<22;i++){
    f>>val;
    if (i==21){
      ret=std::stol(val);
    }
  }
  return ret;
}
