#include <string>
#include <iomanip>

#include "format.h"

using std::string;
using std::stringstream;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int sec = seconds % 60;
  int min = seconds / 60 % 60;
  int hour = seconds / 60 / 60;

  stringstream ss;

  ss << std::setfill('0') << std::setw(2) << hour << ":";
  ss << std::setfill('0') << std::setw(2) << min << ":";
  ss << std::setfill('0') << std::setw(2) << sec;

  return ss.str();
}