#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  float totalJiffies, activeJiffies, idleJiffies;

  totalJiffies =  float(LinuxParser::Jiffies());
  activeJiffies = float(LinuxParser::ActiveJiffies());
  idleJiffies = float(LinuxParser::IdleJiffies());

  float totalDelta = totalJiffies - totalJIffies_;
  float idleDelta = idleJiffies - idleJiffies_;

  totalJIffies_ = totalJiffies;
  activeJiffies_ = activeJiffies;
  idleJiffies_ = idleJiffies;

  return (totalDelta - idleDelta) / totalDelta;
}