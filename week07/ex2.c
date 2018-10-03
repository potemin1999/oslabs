#include <stdio.h>
#include <stdlib.h>

int main(){
  int size;
  printf("write the desired size of your array: ");
  scanf("%d",&size);
  int* array = (int*) malloc(size * sizeof(int));
  printf("array was allocated\n");
  for (int i = 0; i<size; i++){
    array[i] = i;
  }
  for (int i = 0; i<size; i++){
    printf("%d ",array[i]);
  }
  free(array);
  printf("\narray was deallocated, have a good day!\n");
  return 0;
}
