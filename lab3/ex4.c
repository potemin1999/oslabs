#include <stdio.h>
#include <stdlib.h>

// quicksort wrap function
void quicksort(int* array,int length);
// quicksort main sort function
void quicksort_sort(int* array,int l,int h);
// quicksort partitioning function
int  quicksort_partition(int* array,int l,int h);

int main(void){
 int size = 0;
 printf("write array size: \n");
 scanf("%d",&size);
 if (size<0){
  printf("invalid array size, exiting\n");
  return -1;
 }
 int array[size];
 printf("write array elements: \n");
 for ( int i = 0,temp = 0; i<size ; ++i){
  scanf("%d",&temp);
  *(array+i) = temp;
 }
 printf("sorting...");
 quicksort(array,size);
 for (int i = 0 ; i<size ; ++i){
  printf("%d ",*(array+i));
 }
 printf("\n");
 return 0;
}

void quicksort(int* array,int length){
 quicksort_sort(array,0,length-1);
}

void quicksort_sort(int* array,int l,int h){
 if ( l >= h ) return;
 int p = quicksort_partition(array,l,h);
 quicksort_sort(array,l,p-1);
 quicksort_sort(array,p+1,h);
}

int quicksort_partition(int* array,int l,int h){
 int pivot = array[(l+h)>>1];
 int i = l;
 int j = h;
 for( ;; ){
  for( ; *(array+i)<pivot ; ++i );
  for( ; *(array+j)>pivot ; --j );
  if ( i>=j ) return j;
   int temp = *(array+i);
   *(array+i) = *(array+j);
   *(array+j) = temp;
   i++;
   j--;
 }
}
