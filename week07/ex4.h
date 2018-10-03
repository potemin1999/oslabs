#include <stdlib.h>

/**  main idea - use int to save size
 *   allocate n + sizeof(int) bytes
 *   return to the client it's pointer
 *   but you know, what is stored before it
 *
 *   mem_record_size[4 bytes] <- exists, but somehow hidden
 *   required_space [n bytes] <- return pointer to this
 */
typedef int mem_record_size;

void* my_malloc(int size){
  mem_record_size* record = malloc(sizeof(mem_record_size) + size);
  *record = size;
  return (void*)( ((char*)record) + sizeof(mem_record_size) );
}

void my_free(void* ptr){
  void* real_ptr = ((char*)ptr)-sizeof(mem_record_size);
  //remove data and our record
  free(real_ptr);
}

void copy(char* dst,char* src,int size){
  for (register int i = 0; i<size; ++i){
   dst[i] = src[i];
  }
}

void* my_realloc(void* array,int new_size){
  if (array==0){
    return my_malloc(new_size);
  }
  //get current size in bytes
  mem_record_size* record = (mem_record_size*)( ((char*)array)-sizeof(mem_record_size) );
  int current_size = *record;
  if (new_size <= 0){
    //behave as a free()
    my_free(array);
    return 0;
  }
  if (new_size==current_size){
    //return same array
    return array;
  }
  void* new_array_and_record = malloc(new_size + sizeof(mem_record_size));
  char* new_array = ((char*) new_array_and_record) + sizeof(mem_record_size);
  mem_record_size* new_record = (mem_record_size*) new_array_and_record;

  if (new_size>current_size){
    copy(new_array,array,current_size);
  }else{
    copy(new_array,array,new_size);
  }

  //clean up previous storage
  *new_record = new_size;
  free(record);
  return new_array;
}
