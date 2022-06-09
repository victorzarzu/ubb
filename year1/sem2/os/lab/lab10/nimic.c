#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int n = 0;
pthread_mutex_t m;

void* routine_t(void* arg) {
  while(1) {
    pthread_mutex_lock(&m);

    if(n < 0 || n > 1000) {
      pthread_mutex_unlock(&m);
      break;
    }

    n += rand() % 1001 - 500; 
    pthread_mutex_unlock(&m);
    printf("%d\n", n);
  }
  return NULL;
}

int main(int argc, char** argv) {
  pthread_t t1, t2;
  
  srand((unsigned int)getpid());

  pthread_mutex_init(&m, NULL);

  pthread_create(&t1, NULL, routine_t, NULL);
  pthread_create(&t2, NULL, routine_t, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_mutex_destroy(&m);

  return 0;
}
