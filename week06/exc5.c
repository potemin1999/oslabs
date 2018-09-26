#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define I_AM_ALIVE "i'm a bird\n"
#define SIGTERM_CAUGHT "noooooooooooooooo...\n"

void onTerminate(int sig){
 printf(SIGTERM_CAUGHT);
 exit(0);
}

void main(){
 int pid = fork();
 if (pid==0){
  signal(SIGTERM, onTerminate);
  for (int i = 0;i<20;i++){
   printf(I_AM_ALIVE);
   sleep(1);
  }
 }else{
  sleep(10);
  kill(pid,SIGTERM);
 }
}

