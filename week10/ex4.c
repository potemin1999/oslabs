#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILE_PATH 128

struct dir_entry_node{
  struct dirent* entry;
  ino_t inode;
  struct dir_entry_node* next;
};

int sort_nodes(struct dir_entry_node* array,int n_size){
  for (int i = 0; i<n_size; i++){
    int j = 0;
    struct dir_entry_node k = array[i];
    for (j = i-1; j>=0 && array[j].inode > k.inode; j--){
      array[j+1] = array[j];
    }
    array[j+1] = k;
  }
  return 0;
}

int main(){
  DIR *dir = opendir("tmp");
  if (!dir){
    return -1;
  }
  struct dirent *entry = 0;
  struct dir_entry_node* first = 0;
  struct dir_entry_node* last = 0;
  //struct stat file_stat;
  int size = 0;
  int dir_entry_node_size = sizeof(struct dir_entry_node);
  char* file_name = (char*) malloc(sizeof(char)*MAX_FILE_PATH);
  strcpy(file_name,"tmp/");
  while (entry = readdir(dir)){
    if (entry->d_name[0]=='.'){
      continue;
    }
    printf("scanned %s , ",entry->d_name);
    struct dir_entry_node* node = (struct dir_entry_node*) malloc(dir_entry_node_size);
    struct stat file_stat;
    strcpy(file_name+4,entry->d_name);
    int res = stat(file_name,&file_stat);
    if (res==-1){
      break;
    }
    printf(" inode %i\n",file_stat.st_ino);
    if (file_stat.st_nlink < 2){
      continue;
    }
    node->inode = file_stat.st_ino;
    node->entry = entry;
    node->next = 0;
    if (first==0){
      first = node;
    }else {
      last->next = node;
    }
    last = node;
    size++;
    bzero(file_name+4,MAX_FILE_PATH);
  }
  struct dir_entry_node *node_array = (struct dir_entry_node* ) malloc(dir_entry_node_size*size);
  struct dir_entry_node *current = first;
  int position = 0;
  while (current){
    node_array[position] = *current;
    node_array[position].next = 0;
    position++;
    current = current->next;
  }
  sort_nodes(node_array,size);
  ino_t current_key = -1;
  for (int i = 0 ; i<size ; i++){
    current = node_array+i;
    if (current_key != current->inode){
     current_key = current->inode;
     printf("\ninode %lu : ",current_key);
    }
    printf("%s ",current->entry->d_name);
    //it's time to clean up
  }
  printf("\n");
  closedir(dir);
  free(node_array);
  free(file_name);
  return 0;
}
