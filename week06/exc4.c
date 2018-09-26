#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int i = 10;

void onInterrupt(int sig){
 printf("i've got a signal : %d\n",sig);
}

void main(){    
 signal(SIGKILL, onInterrupt);
 signal(SIGSTOP, onInterrupt);
 signal(SIGUSR1, onInterrupt);
 int pid = getpid();
 printf("my pid is %d\n",pid);
 for (;i>0;i--){
  pause();
 }
 printf("it's time to close\n");
}

