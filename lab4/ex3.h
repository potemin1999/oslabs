#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TO_STR_0(x) #x
#define TO_STR(x) TO_STR_0(x)

#define DEBUG
//comment next line, if you want 3rd exercise
#define ADVANCED_SHELL

#ifdef ADVANCED_SHELL
#pragma message "Advanced options from 4th task were enabled"
#define READ_ALL_LINE "[^\n]"
#else
#define READ_ALL_LINE ""
#endif

#define MAX_READ_SIZE 1024
#pragma message "Read buffer size is" TO_STR(MAX_READ_SIZE)
#define SCANF_PARAMETER "%" READ_ALL_LINE TO_STR(MAX_READ_SIZE) "s"

char* get_command(char* input,int max_length,int* length);
char** get_args(char* input,int max_length,int* length);
int main();

int copy(char** src,int srcOffset,char** dst,int dstOffset,int length){
 for (int i = 0;i<length;i++){
  *( (*dst) + dstOffset + i) = *( (*src) + srcOffset + i) ;
 }
 return 0;
}

