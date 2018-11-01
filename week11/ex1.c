#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 23

int main(){
  int size = SIZE;
  char* str = "This is a wonderful day!";
  int fd = open("ex1.txt",O_RDWR | O_TRUNC ,0600);
  lseek(fd,size,SEEK_SET);
  write(fd," ",1);
  void *address = mmap(0, size, PROT_WRITE, MAP_SHARED, fd, 0);
  bzero((char*)address,size);
  strcpy((char*)address,str);
  munmap(address, size);
  return 0;
}
