#include "ex1.h"
#include <stdlib.h>
#include <stdio.h>

unsigned int get_uint_from_arg(char* start){
  unsigned int result = 0;
  sscanf(start,"%u",&result);
  return result;
}

int main(int argc,char** argv){
  unsigned int memory_capacity = argc > 1 ? get_uint_from_arg(argv[1]) : 30;
  char* file_name = 0;
  if (argc>2){
    file_name = (char*) malloc(64);
    sscanf(argv[2],"%s",file_name);
  }
  sys_mem* memory = create_memory(memory_capacity);
  FILE* file = fopen(file_name ? file_name : "./ex1-input.txt","r");
  if (!file){
    printf("invalid file, exiting\n");
    exit(1);
  }
  unsigned int read = 0;
  int counter = 0;
  int miss_counter = 0;
  while (fscanf(file,"%u",&read)!=EOF){
    miss_counter += simulate_page_reference(memory,read);
    ++counter;
  }
  dump_memory(memory);
  printf("hit/miss ratio : %u/%u\n",counter-miss_counter,miss_counter);
  return 0;
}
