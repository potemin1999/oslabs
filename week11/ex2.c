#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 5

int printw(char* str){
  printf(str);
  sleep(1);
}

int main(){
  char* buffer = (char*) malloc(sizeof(char)*SIZE);
  setvbuf(stdout,0,_IOLBF,0);
  printw("H");
  printw("e");
  printw("l");
  printw("l");
  printw("o");
  return 0;
}
