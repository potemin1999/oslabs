#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#define WAITTIME 3
int p_c1_pipe[2];

int child1(){
 int pid = getpid();
 printf("child1: child 1 pid %d\n",pid);
 int child2_pid = 0;
 read(p_c1_pipe[0],&child2_pid,sizeof(int));
 close(p_c1_pipe[0]);
 sleep(WAITTIME);
 printf("child1: stopping child 2 by pid %d\n",child2_pid);
 kill(child2_pid,SIGSTOP);
 printf("child1: kill signal sent, exiting\n");	
 exit(0);
}

int child2(){
 int pid = getpid();
 printf("child2: child 2 pid %d\n",pid);
 for (int i = 0;i<5;i++){
  printf("child2: i'm child\n");
  sleep(1);
 }
 printf("child2: child 2 timeout exit\n");
 exit(110);
}

int parent(int child2_pid){
 int pid = getpid();
 printf("parent: parent pid %d\n",pid);
 write(p_c1_pipe[1], &child2_pid, sizeof(int));
 close(p_c1_pipe[1]);
 int status = 0;
 waitpid(child2_pid,&status,WUNTRACED);
 printf("parent: get status %d from second child\n",status);
 exit(0);
}

int main(){
 pipe(p_c1_pipe);
 int fork1 = fork();
 if (fork1){
  int fork2 = fork();
  if (fork2){
   parent(fork2);
  }else{
   child2();
  }
 }else{
  child1();
 }
}
