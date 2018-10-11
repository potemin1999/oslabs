#include "ex2.h"

#define ALLOCATION_SIZE (30*1024*1024)
#define ALLOCATION_COUNT 0
#define SLEEP_SIZE 1
#define NO_FUNCTION 0

int main(){
  loop_allocate(ALLOCATION_SIZE,ALLOCATION_COUNT,SLEEP_SIZE,NO_FUNCTION);
  return 0;
}
