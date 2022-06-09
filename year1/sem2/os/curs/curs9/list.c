#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct node {
    int value;
    struct node* next;
} node_t;

typedef struct list {
  node_t* head;
  pthread_rwlock_t rwl;
} list_l;

void init(list_l* l) {
  l->head = NULL; 
  pthread_rwlock_init(&l->rwl, NULL);
}

void append(list_l* l, int v) {
  node_t* p; 
  node_t* n = (node_t *)malloc(sizeof(node_t));
  n->value = v;
  n->next = NULL;

  pthread_rwlock_wrlock(&l->rwl);
  if(l->head == NULL) {
    l->head = n;
  }
  else {
    p = l->head;
    while(p->next != NULL){
      p = p->next; 
    }
    p->next = n;
  }
  pthread_rwlock_unlock(&l->rwl);
}

int contains(list_l* l, int v) {
  pthread_rwlock_rdlock(&l->rwl);
  node_t* p = l->head; 

  while(p != NULL){
    if(p -> value == v){
      pthread_rwlock_rdlock(&l->rwl);
      return 1;
    }
    p = p->next;
  }
  pthread_rwlock_unlock(&l->rwl);

  return 0;
}

void delete(list_l* l, int v) {
  node_t* b = NULL; 

  pthread_rwlock_wrlock(&l->rwl);
  node_t* p = l->head;

  while(p != NULL){
    if(p->value == v) {
      if(b == NULL){
        l->head = l->head->next;
      }
      else{
        b->next = p->next;
      }
      free(p);
      break;
    }
    b = p;
    p = p->next;
  }
  pthread_rwlock_unlock(&l->rwl);
}

void destroy(list_l* l) {
  node_t* b; 

  pthread_rwlock_wrlock(&l->rwl);
  node_t* p = l->head;

  while(p != NULL){
    b = p;
    p = p->next;
    free(b);
  }
  pthread_rwlock_unlock(&l->rwl);
  pthread_rwlock_destroy(&l->rwl);
}

int main(int argc, char** argv){
  list_l l;
  
  init(&l);
  append(&l, 1);
  append(&l, 2);
  append(&l, 3);

  if(contains(&l, 4)){
    printf("Hmm,,,\n");
  }

  if(contains(&l, 1)){
    printf("OK!\n");
  }

  delete(&l, 3);
  destroy(&l);


  return 0;
}
