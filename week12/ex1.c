#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define STRING_SIZE 20
#define ASCII_LOW 'A'
#define ASCII_HIGH 'z'

int main(){
  int rand_file = open("/dev/random",O_RDONLY);
  char* buffer = (char*) malloc((STRING_SIZE+1)*sizeof(char));
  read(rand_file,buffer,STRING_SIZE);
  for (int i = 0;i<STRING_SIZE;i++){
    buffer[i] = (ASCII_LOW + ((unsigned short)buffer[i])%(ASCII_HIGH-ASCII_LOW));
  }
  buffer[STRING_SIZE] = '\0';
  printf("%s",buffer);
  return 0;
}
