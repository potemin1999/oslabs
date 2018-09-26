#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int i = 5;
void onInterrupt(int sig){
 printf("ctrl-c was pressed, but i won't close\n");
}

void main(){
 signal(SIGINT, onInterrupt);
 for (;i>0;i--){
  pause();
 }
 printf("ok, closing\n");
}
