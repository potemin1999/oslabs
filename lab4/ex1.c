#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
 int pid = fork();
 if (pid==-1){
  printf("Something went wrong, fork failed\n");
  exit(0);
 }
 if (pid){
  int pid = getpid();
  printf("Hello from child process %d!\n",pid);
  exit(0);
 }else{
  int status = 0;
  int pid = getpid();
  printf("Hello from parent process %d!\n",pid);
  int cpid = wait(&status);
  printf("My child exited with code %d\n",status);
  exit(0);
 }
 return 0;
}
