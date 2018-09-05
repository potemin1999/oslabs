#include <stdio.h>

void bubble_sort(int* array,int length);
void print_array(int* array,int length);

int main(void){
 int random_array[10];
 random_array[0] = 4;
 random_array[1] = 7;
 random_array[2] = 3;
 random_array[3] = 1;
 random_array[4] = 9;
 random_array[5] = 8;
 random_array[6] = 0;
 random_array[7] = 2;
 random_array[8] = 5;
 random_array[9] = 6;
 print_array(random_array,10);
 printf("add some sort magic...\n");
 bubble_sort(random_array,10);
 print_array(random_array,10);
 return 0;
}

void bubble_sort(int *array,int length){
 int n = length;
 int swapped = 0;
 do{
  swapped = 0;
  for (int i = 1; i<n; i++){
   if (*(array+i-1) > *(array+i)){
    int temp = *(array+i-1);
    *(array+i-1) = *(array+i);
    *(array+i) = temp;
    swapped = 1;
   }
  }
  --n;
 }while (swapped);
}

void print_array(int *array,int length){
 printf("array at address %d with length %d\n[ ",array,length);
 for(int i = 0; i<length; i++){
  printf("%d ",*(array+i));
 }
 printf("]\n");
}
