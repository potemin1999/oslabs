#include <stdio.h>
#include <stdlib.h>

//  swap pointed data with size
void swapv(void **p1,void **p2,int size);
//  swap integers
void swapi(int **i1,int **i2);
//  copy object data byte by byte
void copy(void** from,void** to,int size);
//  reads number and returns it;
int get_number(const char* title);

// entry point
int main(){
 int *p_number1 = malloc(sizeof(int*));
 int *p_number2 = malloc(sizeof(int*));
 *p_number1 = get_number("Write first number:");
 *p_number2 = get_number("Write second number:");
 swapi(&p_number1,&p_number2);
 printf("Swap!\n");
 printf("First number: %d \n",*p_number1);
 printf("Second number: %d \n",*p_number2);
 return 0;
}

int get_number(const char* title){
 int temp = 0;
 printf(" %s",title);
 scanf("%d",&temp);
 return temp;
}

void swapi(int **i1,int **i2){
 swapv((void**)i1,(void**)i2,sizeof(int));
}

// simple copy function :)
void copy(void** p_from,void** p_to,int size){
 char **c_from,**c_to;
 c_from = (char**) p_from;
 c_to = (char**) p_to;
 for ( int i = 0 ; i<size ; ++i ){
  *(*c_to+i) = *(*c_from+i);
 }
}

void swapv(void **p1,void **p2,int size){
 void* temp = malloc(size);
 copy(p1,&temp,size);
 copy(p2,p1,size);
 copy(&temp,p2,size);
}
