#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024


int main(){
 printf("Write you word: ");
 char buffer[BUFFER_SIZE];
 fgets(buffer,BUFFER_SIZE,stdin);
 int len = strlen(buffer);
 printf("Reversed      : ");
 //last symbol is \n. we don't need it
 for (int i = len-2 ; i >= 0 ; --i ){
  printf("%c",buffer[i]);
 }
 //again, last symbol is invisible and
 //         doesn't belong to our word
 printf("\nLength        : %d\n",len-1);
 return 0;
}
