#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
  int n;
  int index;
  pthread_barrier_t* barr;
  sem_t* sems;
} data;

void *routine(void *arg) {
  data* info = (data *)arg;

  pthread_barrier_wait(info->barr);

  int i;
  for(i = 0;i < info->n;++i) {
    sem_wait(&info->sems[i]);

    usleep(100);
    printf("Thread: %d - Checkpoint %d\n", info->index, i);

    sem_post(&info->sems[i]);
  }

  free(info);

  return NULL;
}

int main(int argc, char **argv) {
  if(argc != 2) {
    fprintf(stderr, "Numar incorect de argumente!\n");
    exit(EXIT_FAILURE);
  }

  int n, i;
  if(sscanf(argv[1], "%d", &n) <= 0) {
    fprintf(stderr, "Argumentul trebuie sa fie un numar!\n");
    exit(EXIT_FAILURE);
  }

  pthread_barrier_t *barr = (pthread_barrier_t *)malloc(sizeof(pthread_barrier_t) * (1 << n));
  if(barr == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  if(pthread_barrier_init(barr, NULL, (1 << n)) != 0) {
    fprintf(stderr, "Eroare barrier init!\n");
    exit(EXIT_FAILURE);
  }

  sem_t *sems = (sem_t *)malloc(sizeof(sem_t) * (n + 1));
  if(sems == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  int curr = (1 << (n - 1));
  for(i = 0;i < n;++i) {
    if(sem_init(&sems[i], 0, curr) != 0) {
      fprintf(stderr, "Eroare sem init!\n");
      exit(EXIT_FAILURE);
    }
    curr >>= 1;
  }


  pthread_t *ths = (pthread_t *)malloc(sizeof(pthread_t) * (1 << n));
  if(ths == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }


  for(i = 0;i < (1 << n);++i) {
    data* info = (data *)malloc(sizeof(data));
    if(info == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    info->n = n;
    info->index = i;
    info->barr = barr;
    info->sems = sems;

    if(pthread_create(&ths[i], NULL, routine, (void *)info) != 0) {
      fprintf(stderr, "Eroare pthread create!\n");
      exit(EXIT_FAILURE);
    }
  }
  
  for(i = 0;i < (1 << n);++i) {
    if(pthread_join(ths[i], NULL) != 0) {
      fprintf(stderr, "Eroare pthread join!\n");
      exit(EXIT_FAILURE);
    }
  }

  if(pthread_barrier_destroy(barr) != 0) {
    fprintf(stderr, "Eroare barrier destroy!\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < n;++i) {
    if(sem_destroy(&sems[i]) != 0) {
      fprintf(stderr, "Eroare sem destroy!\n");
      exit(EXIT_FAILURE);
    }
  }

  free(barr);
  free(sems);
  free(ths);

  return 0;
}
