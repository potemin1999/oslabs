#include <sys/resource.h>
#include <stdio.h>
#include "ex2.h"

#define ALLOCATION_SIZE (30*1024*1024)
#define ALLOCATION_COUNT 0
#define SLEEP_SIZE 1

void on_memory_allocated(){
  struct rusage usage;
  getrusage(RUSAGE_SELF,&usage);
  printf("process size in real RAM: %d\n",usage.ru_maxrss);
  printf("soft page fault amount  : %d\n",usage.ru_minflt);
  printf("hard page fault amount  : %d\n",usage.ru_majflt);
}

int main(){
  loop_allocate(ALLOCATION_SIZE,ALLOCATION_COUNT,SLEEP_SIZE,on_memory_allocated);
  return 0;
}
