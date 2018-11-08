#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

#define LATE_OPTION_ERROR 1
#define FILE_OPEN_ERROR 2
#define STDOUT_OPEN_ERROR 3

int file_write(int* fds,int count,char* buffer,int size){
  for (int i = 0 ; i<count; i++){
    write(fds[i],buffer,size);
  }
  return 0;
}

int tee(const char** file_name, int file_count, unsigned short do_append){
  int* file_fds = (int*) malloc((file_count+1)*sizeof(int));
  for (int i = 0; i<file_count; i++){
    file_fds[i] = open(file_name[i], O_CREAT | O_WRONLY | (do_append ? O_APPEND : O_TRUNC) );
    if (file_fds[i] < 0){
      printf("unable to open file %s\n",file_name[i]);
      return FILE_OPEN_ERROR;
    }
    else{
      //printf("opened %s\n",file_name[i]);
    }
  }
  file_fds[file_count] = open("/dev/stdout",O_WRONLY);
  if (file_fds[file_count] < 0){
    printf("unable to open stdout\n");
    return STDOUT_OPEN_ERROR;
  }
  char* buffer = (char*) malloc(BUFFER_SIZE*sizeof(char));
  int read_size = 0;
  while ( (read_size = read(STDIN_FILENO,buffer,BUFFER_SIZE)) > 0){
    file_write(file_fds,file_count+1,buffer,read_size);
  }
  buffer[0] = '\0';
  file_write(file_fds,file_count+1,buffer,1);
  return 0;
}

int main(int argc,const char** argv){
  unsigned short do_append = 0;
  const char** file_name = 0;
  int file_count = 0;
  int arr_pointer = 0;
  for ( int i = 1 ; i<argc ; i++ ){
    if (*(argv[i]) == '-'){
      if (i!=1){
        printf("-a option must be before file names\n");
        return LATE_OPTION_ERROR;
      }
      do_append = *(argv[i]+1)=='a' ? 1 : 0;
    }else{
      if (file_count==0){
        file_count = argc-i;
        file_name = (const char**) malloc(file_count*sizeof(char));
      }
      file_name[arr_pointer++] = argv[i];
    }
  }
  return tee(file_name,file_count,do_append);
}
