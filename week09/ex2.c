#include "ex1.h"

#define PAGES_COUNT 1000
#define PAGE_MAX_INDEX 1000
#define MEMORY_CAPACITY 10
//0 if you want min hit
#define MAX_HIT_REQUIRED 0

//if you want maximum hit rate, just make every page uploaded to RAM once
int sort_pages_max(unsigned int* array,int count){
  int i = 1;
  while(i < count){
    int x = array[i];
    int j = i - 1;
    while (j >= 0 & array[j] > x){
        array[j+1] = array[j];
        j--;
    }
    array[j+1] = x;
    i++;
  }
}

//access page, when it was replaced by some other page
//uses counting sort
//it doesn't work well, so at least I've tried
int sort_pages_min(unsigned int* array,int count){
  unsigned short* count_array = (unsigned short*) calloc(PAGE_MAX_INDEX,sizeof(unsigned short));
  for (int i = 0 ; i < count ; i++){
    count_array[array[i]] += 1;
  }
  int exit_i = 0;
  for (int i = 0,j=0 ; i<count ; i++,j++){
    int start_j = j;
    while (count_array[j % PAGE_MAX_INDEX] <= 1){
      j++;
      if (j - start_j > PAGE_MAX_INDEX){
        exit_i = i;
        i = count;
        break;
      }
    }
    if (i == count) break;
    array[i] = j % PAGE_MAX_INDEX;
    count_array[j % PAGE_MAX_INDEX] -= 1;
  }
  for (int i = exit_i, j=0; i<count; i++){
    while (count_array[j] == 0){ j++; }
    array[i] = j;
    count_array[j] = 0;
  }
}

int sort_pages(unsigned int* array,int count,int max_hit){
  if (max_hit){
    sort_pages_max(array,count);
  }else{
    sort_pages_min(array,count);
  }
}
int main(){
  sys_mem* memory = create_memory(MEMORY_CAPACITY);
  FILE* file = fopen("./ex1-input.txt","r");
  unsigned int* pages_array = (unsigned int*) malloc(sizeof(unsigned int)*PAGES_COUNT);
  int read = 0;
  int counter = 0;
  int miss_counter = 0;
  while (counter<PAGES_COUNT && fscanf(file,"%d",&read)!=EOF){
    pages_array[counter] = read;
    ++counter;
  }
  sort_pages(pages_array,PAGES_COUNT,MAX_HIT_REQUIRED);
  for (int i = 0; i < PAGES_COUNT; i++){
    int res = simulate_page_reference(memory,pages_array[i]);
    if (!MAX_HIT_REQUIRED && !res){
      printf("hit! : page %u\n",pages_array[i]);
    }
    miss_counter += res;
  }
  dump_memory(memory);
  printf("hit/miss ratio : %u/%u\n",counter-miss_counter,miss_counter);
  return 0;
}
