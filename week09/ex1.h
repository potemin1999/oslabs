#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long mem_page_counter;
#define MEM_PAGE_COUNTER_FORMAT "%llu"

typedef struct mem_page_frame{
  unsigned int exists: 1;
  unsigned int number: 31;
  mem_page_counter counter;
} mem_page;

typedef struct system_memory{
  //page capacity
  unsigned int capacity;
  //page frames, exists in RAM
  mem_page* pages;
} sys_mem;

sys_mem* create_memory(unsigned int capacity){
  sys_mem* memory = (sys_mem*) malloc(sizeof(sys_mem));
  memory->capacity = capacity;
  mem_page* pages = (mem_page*) calloc(capacity,sizeof(mem_page));
  memory->pages = pages;
  return memory;
}

int simulate_age_tick(sys_mem* memory){
  for ( unsigned int i = 0 ; i < memory->capacity; i++ ){
    memory->pages[i].counter = memory->pages[i].counter >> 1;
  }
  return 0;
}

mem_page* _try_to_hit_page(sys_mem* memory,unsigned int page_number){
  for ( unsigned int i = 0 ; i < memory->capacity ; i++){
    if (!memory->pages[i].exists){
      continue;
    }
    if (memory->pages[i].number == page_number){
      return (memory->pages) + i;
    }
  }
  return 0;
}

mem_page* _get_page_to_replace(sys_mem* memory){
  mem_page* candidate = memory->pages;
  if (!candidate->exists){
    return candidate;
  }
  for ( unsigned int i = 1 ; i < memory->capacity ; i++){
    if ( !memory->pages[i].exists ){
      return ((memory->pages)+i);
    }
    if ( candidate->counter > memory->pages[i].counter ){
      candidate = ((memory->pages)+i);
    }
  }
  return candidate;
}

int _access_page(sys_mem* memory,unsigned int page_number){
  int was_hit = 1;
  mem_page* page = _try_to_hit_page(memory,page_number);
  if (!page){
    was_hit = 0;
    page = _get_page_to_replace(memory);
    page->number = page_number;
    page->counter = 0;
    page->exists = 1;
  }
  page->counter = page->counter | ((mem_page_counter)1)<< (sizeof(mem_page_counter)*8-1) ;
  return was_hit;
}


/**
 * return 0 if was page hit, 1 if missed
 */
int simulate_page_reference(sys_mem* memory,unsigned int page_number){
  simulate_age_tick(memory);
  return 1 - _access_page(memory,page_number);
}

int dump_memory(sys_mem* memory){
  printf("\e[0;92mmemory dump: %u loaded page frames \e[0m \n",memory->capacity);
  for ( unsigned int i = 0 ; i< memory->capacity; i++){
    char exists = memory->pages[i].exists ? 't' : 'f';
    unsigned int number = memory->pages[i].number;
    mem_page_counter counter = memory->pages[i].counter;
    if (exists=='t'){
      printf("\e[0;97m page frame[%u] : number: %u, counter: ",i,number);
      printf(MEM_PAGE_COUNTER_FORMAT,counter);
      printf("\n");
    }else{
      printf("\e[0m page frame[%u] : never used\n",i);
    }
  }
}
