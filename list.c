// list/list.c
// 
// Implementation for linked list.
//
// <Nubia Johnson>

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t *l = malloc(sizeof(list_t));
  l->head = malloc(sizeof(node_t));
  l->head->value = val;
  return l;
  }

void list_free(list_t *l) {
  node_t * t = l->head;
    while(t){
      node_t * temp = t;
      t = t ->next;
      free(temp);
    }
  free(t);
  return;
}

void list_print(list_t *l) {
  node_t * t = l->head;
  while (t){
    printf("%d \n", t->value)
    t = t->next;
  }
}

int list_length(list_t *l) { 
  if(!l->head || !l){
    return 0;
  }
  int length = 1;
  node_t * t = l->hea;
  
    while(t){
      length++;
      t = t->next;
    }
  printf("Length is %d values long \n", length);
  return length;
}

void list_add_to_back(list_t *l, elem value) {
  if(!l){
    printf("The list does not exist")
      return;
  }
  node_t * t = l->head;
  list_t * new_node = list_alloc(value);
  while(t->next != NULL){
    t = t->next;
  }
  t->next = new_node->head
}

void list_add_to_front(list_t *l, elem value) {
  if(!l){
    printf("The list does not exist")
      return;
  }
  list_t * new_node = list_alloc(value);
  node_t * t = l->head;
  new_node->head->next = t;
  l->head = new_node->head;
}

void list_add_at_index(list_t *l, elem value, int index) {
  if(!l){
    printf("The list does not exist");
    return;
    
  }
  list_t *new_node = list_alloc(value);
  int i = 0;
  node_t * t = l->head;
  while(t ->next != NULL && i < index){
    t = t->next;
    i++
  }
  new_node->head->next = t->next;
  t->next = new_node->head;
}

elem list_remove_from_back(list_t *l) { 
  if(!l){
    return;
  }
  node_t * t = l->head;
  while(t->next != NULL){
    t = t->next;
  }
  elem returnee = t->value;
  free(t);
  
  return returnee;
}

elem list_remove_from_front(list_t *l) { 
  if(!l){
    printf("The lise does not exist");
    return;
  }
  elem returnee = l->head->value;
  node_t *freer = l->head;
  l->head = l->head->next;
  free(freer);
  
  return returnee;
}

elem list_remove_at_index(list_t *l, int index) { 
  if(!l){
    printf("The list does not exist");
    return;
  }
  int i = 0;
  node_t * t = l ->head;
  while (t ->next != NULL&& i < index){
    t = t->next;
    i++
  }
  node_t * freer = t->next;
  elem val = t->next->value;
  t->next = t->next->next;
  free(freer);
  
  printf("%d has removed at index", val);
  return val;
}

bool list_is_in(list_t *l, elem value) { 
  if(!l){
    printf("The list does not exist");
    return;
  }
  node_t * t = l->head;
  while(t->next){
    t = t->next;
  }
  return t->value == value
}

elem list_get_elem_at(list_t *l, int index) { 
  if(!l){
    printf("The list does not exist")
      return;
  }
  int i = 0;
  node_t * t = l->head;
  while(t->next != NULL && i < index){
    t = t->next;
    i++;
  }
  return t->value;
}

int list_get_index_of(list_t *l, elem value) { 
  if(!l){
    printf("The list does not exist")
      return;
  }
  int i = 0;
  node_t * t = l->head;
  elem looking = t->value;
  while(looking != value && t->next){
    t = t->next;
    i++;
  }
  if(looking == value){
    printf("The index of %d is %d\n", value, i);
    return i;
  }
  printf("Value not found!");
  return 0;
}

