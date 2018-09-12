#include "ex3.h"


int main(){
 char* buffer = malloc(sizeof(char)*(MAX_READ_SIZE+1));
 int status = 0;
 //sorry, no time
 printf("use ctrl+c to exit\n");
 while (1){
  //save buffer
  fgets(buffer,MAX_READ_SIZE,stdin);
#ifdef DEBUG
  printf("read : %s\n",buffer);
#endif
#ifndef ADVANCED_SHELL
  system(buffer);
#else
  int pid = fork();
  if (pid==0){
   //i'm a parent, do something
   int command_length = 0;
   int args_length = 0;
   char* command = get_command(buffer,MAX_READ_SIZE+1,&command_length);
   char** args = get_args(buffer,MAX_READ_SIZE+1,&args_length);
   char** env = {0};
#ifdef DEBUG
   for (int i = 0;i<args_length;i++){
    printf("get argument %i : %s\n",i,args[i]);
   }
#endif
   execvpe(command,args,env);
   exit(0);
   return 0;
  }else{
   free(buffer);
   buffer = malloc(sizeof(char)*(MAX_READ_SIZE+1));
   //uncomment, if you want to disable background
   //wait(&status);
  }
#endif
 }
}

#ifdef ADVANCED_SHELL
char* get_command(char* input,int max_length,int* length){
 int i = 0;
 for ( ; i<max_length && *(input+i)!=' ' ; i++);
 char* command = malloc(sizeof(char)*(i+1));
 copy(&input,0,&command,0,i);
 *(command+i) = '\0';
 *length = i;
 return command;
}

char** get_args(char* input,int max_length,int* _args_count){
 int i = 0;
 int command_passed = 0;
 int args_count = 0;
 int args_start = 0;
 int end_index = 0;
 for (; i<max_length;i++){
  if (*(input+i)=='\0'){
   end_index = i;
   break;
  }
  if (*(input+i)==' '){
   if (!command_passed){
    command_passed = 1;
    args_start = i+1;
   }
   args_count++;
  }
 }

#ifdef DEBUG
 printf("args size : %d\n",args_count);
 printf("args starts at : %d\n",args_start);
#endif
 int* args_size = malloc(sizeof(int)*args_count);
 for (int current_arg=0, i = args_start; i<max_length && *(input+i)!='\0'; i++){
  if (*(input+i)==' '){
   current_arg++;
  }else{
   *(args_size+current_arg) += 1;
  }
 }
 *_args_count = args_count+1;
/* if (args_count==0){
  char** args = malloc(sizeof(char)*2);
  args[0] = malloc()
  args[0] = 0;
 }*/
#ifdef DEBUG
 for (int j = 0; j<args_count;j++){
  printf("arg %d size : %d\n",j,args_size[j]);
 }
#endif
 char** args = malloc(sizeof(char)*(args_count+2));
 //add program name
 if (args_start==0){
  args_start = end_index;
 }
 args[0] = malloc(sizeof(char)*(args_start));
 for (int i = 0; i<(args_start-1); i++){
  args[0][i] = input[i];
 }
 //finish program name
 args[0][args_start-1] = '\0';
 i = args_start;
 args[1] = malloc(sizeof(char)*(args_size[0]+1));
 //by convention, last one is null
 args[args_count+1] = 0;
 if (!command_passed){
  return args;
 }
 //start filling array from 1 to args_count arguments
 for (int current_arg=1,arg_pointer=0; i<max_length; i++){
  if (*(input+i)==' '){
   //end current arg record
   args[current_arg][arg_pointer+1] = '\0';
   //null and move to the next one
   arg_pointer = 0;
   current_arg++;
#ifdef DEBUG
   printf("creating array for arg %d with size %d\n",current_arg,args_size[current_arg]);
#endif
   args[current_arg] = malloc(sizeof(char)*(args_size[current_arg]+1));
  }else{
   //just copy char to the right place
   *( (*(args+current_arg)) + arg_pointer) = input[i];
   arg_pointer++;
  }
 }
 free(args_size);
 return args;
//return 0;
}
#endif

