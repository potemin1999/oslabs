#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void loop_allocate(int size,int count,
                   unsigned s_sleep,
                   void (*on_allocated_callback)()){
 //with i_step==0 we will never exit loop
 int i_step = count==0 ? 0 : 1;
 int i_final = count==0 ? 1 : count;
 for ( int i = 0 ; i<i_final ; i+=i_step ){
  char* array = (char*) malloc(size);
  memset(array,0,size);
  //call function, if it's needed
  if (on_allocated_callback){
    on_allocated_callback();
  }
  sleep(s_sleep);
 }
}

