#include <string>
#include <iomanip>
#include <sstream>
#include "format.h"

using std::string;
const int sim {60};
const int mih {60};
const int sih {sim*mih};
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    long hours, minutes;
    hours = seconds/sih;
    seconds = seconds%sih;
    minutes = seconds/sim;
    seconds = seconds%sim;
    std::ostringstream stream;
  stream << std::setw(2) << std::setfill('0') << hours << ":" 
     << std::setw(2) << std::setfill('0') << minutes << ":"
     << std::setw(2) << std::setfill('0') << seconds;
  return stream.str();
}