#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  float totalJIffies_;
  float idleJiffies_;
  float activeJiffies_;
};

#endif