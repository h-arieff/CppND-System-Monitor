#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
class Process;
namespace LinuxParser {

// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};
// System
float MemoryUtilization(bool u=false);
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
int CpuUtilization();
float Pcpuutil();
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(Process p);
long IdleJiffies();

// Processes
std::unordered_map<std::string,std::string> getStatus(Process p);
std::string Command(Process p);
std::string Ram(Process p);
std::string Uid(Process p);
std::string User(Process p);
long int UpTime(Process p);
};  // namespace LinuxParser

#endif