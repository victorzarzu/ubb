#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
  int *n;
  int *sir;
  int *index;
  pthread_mutex_t* mtxs;
  pthread_barrier_t *barr;
} data;

void* routine(void *arg) {
  data *info = (data *)arg;

  int random = rand() % 11 + 10;
  info->sir[*info->index] = random;

  pthread_barrier_wait(info->barr);

  while(1) {
    if(!info->sir[*info->index]) {
      break;
    }

    int i, flag = 1;
    for(i = 0;i < *info->n;++i) {
      pthread_mutex_lock(&info->mtxs[i]);
      info->sir[*info->index]--;
      if(info->sir[*info->index] < 0) {
        flag = 0;
      }
      pthread_mutex_unlock(&info->mtxs[i]);
    }

    if(!flag) {
      break;
    }
  }

  free(info->index);
  free(info);
  
  return NULL;
}

int main(int argc, char** argv) {
  int *n = (int *)malloc(sizeof(int));
  if(n == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  srand(time(NULL));
  printf("Numar: ");
  if(scanf("%d", n) <= 0) {
    fprintf(stderr, "Un numar!\n");
    exit(EXIT_FAILURE);
  }

  int *sir = (int *)malloc(sizeof(int) * (*n));
  if(sir == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  pthread_mutex_t *mtxs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (*n));
  if(mtxs == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i = 0;i < *n;++i) {
    if(pthread_mutex_init(&mtxs[i], NULL) != 0) {
      fprintf(stderr, "Eroare mutex init!\n");
      exit(EXIT_FAILURE);
    }
  }

  pthread_t *ths = (pthread_t *)malloc(sizeof(pthread_t) * (*n));
  if(ths == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  pthread_barrier_t *barr = (pthread_barrier_t *)malloc(sizeof(pthread_barrier_t));
  if(barr == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  if(pthread_barrier_init(barr, NULL, *n) != 0) {
    fprintf(stderr, "Eroare barrier init!\n");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < *n;++i) {
    data *info = (data *)malloc(sizeof(data));

    if(info == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    int *index = (int *)malloc(sizeof(int));
    if(index == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    *index = i;

    info->index = index;
    info->sir = sir;
    info->barr = barr;
    info->mtxs = mtxs;
    info->n = n;

    if(pthread_create(&ths[i], NULL, routine, (void *)info) != 0) {
      fprintf(stderr, "Eroare pthread create!\n");
      exit(EXIT_FAILURE);
    }
 }

  for(i = 0;i < *n;++i) {
    if(pthread_join(ths[i], NULL) != 0) {
      fprintf(stderr, "Eroare pthread join!\n");
      exit(EXIT_FAILURE);
    }
  }

  for(i = 0;i < *n;++i) {
    if(pthread_mutex_destroy(&mtxs[i]) != 0) {
      fprintf(stderr, "Eroare barrier destroy!\n");
      exit(EXIT_FAILURE);
    }
  }

  if(pthread_barrier_destroy(barr) != 0) {
     fprintf(stderr, "Eroare barrier destroy!\n");
     exit(EXIT_FAILURE);
  }

  for(i = 0;i < *n;++i) {
    printf("%d ", sir[i]);
  }
  printf("\n");

  free(sir);
  free(mtxs);
  free(ths);
  free(n);
  free(barr);
  
  return 0;
}
