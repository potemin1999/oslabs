#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
  FILE* fd = fopen("ex1.txt","r");
  fseek(fd,0,SEEK_END);
  int size = ftell(fd);
  fclose(fd);
//  printf("%d\n",size);
  int fd_src = open("ex1.txt",O_RDWR,0600);
  lseek(fd_src,size,SEEK_SET);
  int src_size = size;
  int fd_dst = open("ex1.memcpy.txt",O_RDWR | O_CREAT | O_TRUNC ,0600);
  lseek(fd_dst,size,SEEK_SET);
  write(fd_dst," ",1);
  void *address_src = mmap(0, src_size, PROT_READ,  MAP_SHARED, fd_src, 0);
  void *address_dst = mmap(0, src_size, PROT_WRITE, MAP_SHARED, fd_dst, 0);
  memcpy(address_dst,address_src,src_size);
  munmap(address_dst,src_size);
  munmap(address_src,src_size);
  return 0;
}
