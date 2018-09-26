#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 128

int main(){
 int fd[2];
 pipe(fd);
 char* str1 = "some text";
 char* str2[BUFFER_SIZE];
 printf("written str : %s\n", str1);
 write(fd[1], str1, strlen(str1)+1);
 read(fd[0], str2, BUFFER_SIZE);
 printf("read str : %s\n",str2);
 close(fd[0]);
 close(fd[1]);
 return 0;
}
