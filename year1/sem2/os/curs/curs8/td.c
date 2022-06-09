#include <stdio.h>
#include <pthread.h>

void* f(void* a){
  printf("%d\n",(int)(long) a);
  //free(a);


  return NULL;
}

int main(int argc, char** argv){
  pthread_t t[10];
  int i; 
  //int a[10];
  //int *a;

  for(i = 0;i < 10;++i){
    //a[i] = i;
    
    //a = (int*)malloc(sizeof(int));
    //*a = i;
    pthread_create(&t[i], NULL, f, (void *)(long)i);
  }

  for(i = 0;i < 10;++i){
    pthread_join(t[i], NULL);
  }
  return 0;
}
