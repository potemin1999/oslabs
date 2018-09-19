#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 1000
#define SIGSLEEP SIGCHLD

static int count = 0;
static sigset_t sigset;
static pthread_t producer_thread;
static pthread_t consumer_thread;
static int producer_awake;
static int consumer_awake;

void producer_wake(){
 producer_awake = 1;
}

void producer_wait(){
 producer_awake = 0;
 while (!producer_awake);
}

void consumer_wake(){
 consumer_awake = 1;
}

void consumer_wait(){
 consumer_awake = 0;
 while (!consumer_awake);
}

void* producer(void* buffer){
 producer_awake = 1;
 int* int_buffer = (int*) buffer;
 for (long i = 0;i>-1; i++) {
  if (count>=BUFFER_SIZE){
   producer_wait();
  }
  if (i%100==0){
   printf("producer: %ld\n",i);
  }
  *(int_buffer+(count++)) = (int) i;
  if (count==1){
   consumer_wake();
  }
 }
}

void* consumer(void* buffer){
 consumer_awake = 1;
 int* int_buffer = (int*) buffer;
 for (long i = 0;i>-1;i++){
  if (count<=0){
   consumer_wait();
  }
  if (i%100==0){ 
   printf("consumer: %ld\n",i);
  }

  int read = *(int_buffer+(count--));
  if (count==BUFFER_SIZE-1){
   producer_wake();
  }
 }
}

int main(){
 int* buffer = malloc(sizeof(int)*BUFFER_SIZE);
 pthread_create(&producer_thread,0,producer,buffer);
 pthread_create(&consumer_thread,0,consumer,buffer);
 pthread_join(producer_thread,0);
 return 0;
}
