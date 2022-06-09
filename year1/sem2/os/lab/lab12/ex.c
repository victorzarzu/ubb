#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

typedef struct {
  pthread_barrier_t *b;
  int* flag;
  pthread_mutex_t* m;
} data;


void *f(void *arg) {
  data d = *((data *)arg);
  pthread_barrier_wait(d.b);

  while(1) {
    pthread_mutex_lock(d.m);
    if(*(d.flag)) {
      pthread_mutex_unlock(d.m);
      return NULL;
    }
    else{
      int random = rand() % 111111 + 1;
      printf("%d\n", random);
      if(!(random % 1001)) {
        *(d.flag) = 1;
      }
    }
    pthread_mutex_unlock(d.m);

  }

  return NULL;
}

int main(int argc, char** argv) {
  if(argc < 2) {
    fprintf(stderr, "Provide an argument!\n");
    exit(1);
  }

  srandom(time(NULL));
  int n = atoi(argv[1]);
  pthread_barrier_t *b = (pthread_barrier_t*)malloc(sizeof(pthread_barrier_t));
  pthread_barrier_init(b, NULL, n);

  pthread_mutex_t *m = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(m, NULL);

  int flag = 0;
  data d;
  d.b = b;
  d.m = m;
  d.flag = &flag;
  int i;
  pthread_t *th = (pthread_t*)malloc(sizeof(pthread_t) * n);

  for(i = 0;i < n;++i) {
    pthread_create(&th[i], NULL, f, &d);
  }

  for(i = 0;i < n;++i) {
    pthread_join(th[i], NULL);
  }

  free(th);
  pthread_barrier_destroy(b);
  free(b);
  free(m);


  return 0;
}
