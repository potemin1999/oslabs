#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUMBER 5
#define FIX 1

void* thread_void(void* args){
 printf("hello! I'm the thread #%d\n",*((int*)args));
 free(args);
 return 0;
}

int main(){
 for (int i = 0; i<THREAD_NUMBER; i++){
  pthread_t thread;
  int* number = malloc(sizeof(int));
  *number = i;
  printf("creating thread number #%d\n",i);
  int result = pthread_create(&thread,0,thread_void,number);
  if (result){
   printf("thread cretion failed : %d",result);
   return result;
  }
#ifdef FIX
  pthread_join(thread,0);
  if (i<THREAD_NUMBER-1){
   printf("thread #%d is dead by now, moving on\n",i);
  }else{
   printf("thread #%d is dead by now, last thread\n",i);
  }
#endif
 }
 return 0;
}
