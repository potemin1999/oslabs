#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 128

int main(){
 int fd[2];
 pipe(fd);
 int id = fork();
 int pid = getpid();
 if (id){
  char* str1 = "some text";
  printf("parent [%d] wrote str : %s\n",pid,str1);
  write(fd[1], str1, strlen(str1)+1);
  close(fd[1]);
  exit(0);
 }else{
  char* str2[BUFFER_SIZE];
  read(fd[0], str2, BUFFER_SIZE);
  printf("child [%d] read str : %s\n",pid,str2);
  close(fd[0]);
  exit(0);
 }
 return 0;
}

