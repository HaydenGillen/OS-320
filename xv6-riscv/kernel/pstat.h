#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
  int inuse[NPROC];   // whether this slot of the process table is in use (1 or 0)
  int pid[NPROC];     // the PID of each process 
  int runtime[NPROC]; // the number of ticks each process has accumulated 
  int pass[NPROC];    // the number of strides each process has accumulated
  int stride[NPROC];  // stride length of each process   
  int syspasses;      // total system passes
};

#endif // _PSTAT_H_