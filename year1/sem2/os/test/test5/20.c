#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
  int m;
  int curr_point;
  int index;
  pthread_mutex_t *mtxs;
  pthread_barrier_t *barr;
} data;

void *routine(void *arg) {
  data* info = (data *)arg;
  
  while(info->curr_point <= info->m) {
    pthread_mutex_lock(&(info->mtxs[info->curr_point]));

    printf("Thread-ul %d in punctul %d\n", info->index, info->curr_point);
    info->curr_point++;

    int random = rand() % 101 + 100;
    usleep(random * 1000);


    pthread_mutex_unlock(&(info->mtxs[info->curr_point - 1]));
  }
  
  free(info);

  return NULL;
}

int main(int argc, char **argv) {
  if(argc != 3) {
    fprintf(stderr, "Numar incorect de argumente!\n");
    exit(EXIT_FAILURE);
  }

  int n, m;
  if(sscanf(argv[1], "%d", &n) <= 0) {
    fprintf(stderr, "Primul argument trebuie sa fie un numar!\n");
    exit(EXIT_FAILURE);
  }
  if(sscanf(argv[2], "%d", &m) <= 0) {
    fprintf(stderr, "Al doilea argument trebuie sa fie un numar!\n");
    exit(EXIT_FAILURE);
  }
  
  pthread_mutex_t *mtxs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
  if(mtxs == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i = 0;i < n;++i) {
    if(pthread_mutex_init(&mtxs[i], NULL) != 0) {
      fprintf(stderr, "Eroare mutex init!\n");
      exit(EXIT_FAILURE);
    }
  }

  pthread_barrier_t *barr = (pthread_barrier_t *)malloc(sizeof(pthread_barrier_t));
  if(barr == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  if(pthread_barrier_init(barr, NULL, n) != 0) {
    fprintf(stderr, "Eroare barrier init!\n");
    exit(EXIT_FAILURE);
  }

  pthread_t *ths = (pthread_t *)malloc(sizeof(pthread_t) * n);
  if(ths == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < n;++i) {
    data *info = (data *)malloc(sizeof(data)); 
    if(info == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    info->mtxs = mtxs;
    info->barr = barr;
    info->index = i + 1;
    info->curr_point = 1;
    info->m = m;

    if(pthread_create(&ths[i], NULL, routine, (void *)info) != 0) {
      fprintf(stderr, "Eroare pthread create!\n");
      exit(EXIT_FAILURE);
    }
  }


  for(i = 0;i < n;++i) {
    if(pthread_join(ths[i], NULL) != 0) {
      fprintf(stderr, "Eroare pthread join!\n");
      exit(EXIT_FAILURE);
    }
  }
  for(i = 0;i < n;++i) {
    if(pthread_mutex_destroy(&mtxs[i]) != 0) {
      fprintf(stderr, "Eroare mutex init!\n");
      exit(EXIT_FAILURE);
    }
  }
  if(pthread_barrier_destroy(barr) != 0) {
    fprintf(stderr, "Eroare barrier destroy!\n");
    exit(EXIT_FAILURE);
  }

  free(mtxs);
  free(barr);
  free(ths);

  return 0;
}
