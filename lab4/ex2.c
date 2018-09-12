#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define RUN_COUNT 5
#define SLEEP_TIME 5

int main(){
 for (int i = 0; i<RUN_COUNT; i++){
  fork();
 }
 sleep(SLEEP_TIME);
 exit(0);
}
