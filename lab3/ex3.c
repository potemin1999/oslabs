#include <stdio.h>
#include <stdlib.h>

// comment next line, if you'd like to see 3rd task
// leave it as is for the 5th one
// preprocessor will arr or replace some lines for chosen type
#define DOUBLE_LINKED_LIST

typedef struct LinkedListNode LinkedListNode;
typedef struct LinkedList LinkedList;

struct LinkedListNode{
 int value;
 LinkedListNode* next;
#ifdef DOUBLE_LINKED_LIST
 LinkedListNode* prev;
#endif
};

struct LinkedList{
 LinkedListNode* first;
 int length;
};

// prints list elements
void print_list(LinkedList* list);
// returns pointer to the new linked list with nulled pointers
LinkedList* create_linked_list();
// return pointer to the new list node with nulled pointers
LinkedListNode* create_linked_list_node();
// inserts node in the end of linked list
void insert_node(LinkedList* list, int value);
// removes node by it's value
void delete_node(LinkedList* list, int value);
// removes node by index
void delete_node_by_index(LinkedList* list, int index);

int main(void){
 LinkedList* list = create_linked_list();
 insert_node(list,987654321);
 insert_node(list,3735928559);
 insert_node(list,1029384756);
 insert_node(list,234234);
 insert_node(list,1111111);
 insert_node(list,5555555);
 printf("inserted 5 values\n");
 print_list(list);
 printf("delete 234234\n");
 delete_node(list,234234);
 print_list(list);
 printf("delete 987654321\n");
 delete_node(list,987654321);
 print_list(list);
 printf("delete second node\n");
 delete_node_by_index(list,1);
 print_list(list);
 return 0;
}


void print_list(LinkedList* list){
 LinkedListNode* node = list->first;
 for (int counter = 0 ; node ; node=node->next, ++counter){
  printf("[%d]: %d ", counter, node->value);
 }
 printf("\n");
}


void insert_node(LinkedList* list, int value){
 LinkedListNode* current_node = list->first;
 LinkedListNode* new_node = create_linked_list_node();
 new_node->value = value;
 if (!current_node){
  list->first = new_node;
 }else{
  for ( ; current_node->next ; current_node=current_node->next );
  current_node->next = new_node;
#ifdef DOUBLE_LINKED_LIST
  new_node->prev = current_node;
#endif
 }
 ++(list->length);
}


void delete_node(LinkedList* list,int value){
 LinkedListNode* current_node = list->first;
#ifndef DOUBLE_LINKED_LIST
 LinkedListNode* previous_node = 0;
 for ( ; current_node ; previous_node = current_node, current_node = current_node->next ){
#else
 for ( ; current_node ; current_node = current_node->next){
#endif
  if (current_node->value == value){
#ifndef DOUBLE_LINKED_LIST
   if (previous_node){
    previous_node->next = current_node->next;
   }else{
    list->first = current_node->next;
   }
#else
   if (current_node->prev){
    current_node->prev->next = current_node->next;
    current_node->next->prev = current_node->prev;
   }else{
    list->first = current_node->next;
    current_node->next->prev = 0;
   }
#endif
   --(list->length);
   free(current_node);
   break;
  }
 }
}

void delete_node_by_index(LinkedList* list,int index){
 LinkedListNode* current_node = list->first;
 if (index<0 || index>=list->length) return;
#ifndef DOUBLE_LINKED_LIST
 LinkedListNode* previous_node = 0;
 for ( int i = 0 ; i<index && current_node ; i++, previous_node = current_node, current_node = current_node->next );
#else
 for ( int i = 0 ; i<index && current_node ; i++, current_node = current_node->next);
#endif
#ifndef DOUBLE_LINKED_LIST
 if (previous_node){
  previous_node->next = current_node->next;
 }else{
  list->first = current_node->next;
 }
#else
 if (current_node->prev){
  current_node->prev->next = current_node->next;
  current_node->next->prev = current_node->prev;
 }else{
  list->first = current_node->next;
  current_node->next->prev = 0;
 }
#endif
 --(list->length);
 free(current_node); 
}


LinkedList* create_linked_list(){
 LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
 list->first = 0;
 list->length = 0;
 return list;
}


LinkedListNode* create_linked_list_node(){
 LinkedListNode* node = (LinkedListNode*) malloc(sizeof(LinkedListNode));
 node->next = 0;
 node->value = 0;
#ifdef DOUBLE_LINKED_LIST
 node->prev = 0;
#endif
 return node;
}
