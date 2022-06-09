#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define TEAM_SIZE 4

typedef struct data{
  int *status;
  int *curr_here;
  int *team;
  int *index;
  pthread_cond_t *cond;
  pthread_mutex_t* mtx;
  pthread_barrier_t* barr;
} data;

void *routine(void* arg) {
  data* info = (data *)arg;

  if(*info->curr_here == 0) {
    pthread_barrier_wait(info->barr);
  }

  pthread_mutex_lock(info->mtx);

  while(*info->index != *info->curr_here) {
    pthread_cond_wait(info->cond, info->mtx);
  }

  printf("th %d echipa %d => %d\n", *info->index, *info->team, *info->index + 1);
  (*info->index) = *info->index + 1;

  if(*info->index == TEAM_SIZE && *info->status == 0) {
    *info->status = 1;
    printf("Echipa %d a castigat!\n", *info->team);
  }

  pthread_mutex_unlock(info->mtx);

  int rnd = rand() % 100 + 100;
  usleep(rnd * 1000);

  pthread_cond_broadcast(info->cond);
  
  if(*info->curr_here == TEAM_SIZE - 1) { 
    free(info->index);
    free(info->team);
  }

  free(info->curr_here);
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

  int i;
  pthread_t **ths = (pthread_t **)malloc(sizeof(pthread_t *) * (*n));
  if(ths == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < *n;++i) {
    ths[i] = (pthread_t *)malloc(sizeof(pthread_t) * TEAM_SIZE);
    if(ths[i] == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
  }

  pthread_cond_t *conds = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * (*n));
  if(conds == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < *n;++i) {
    if(pthread_cond_init(&conds[i], NULL) != 0) {
      fprintf(stderr, "Eroare cond init!\n");
      exit(EXIT_FAILURE);
    }
  }

  pthread_mutex_t *mtxs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (*n));
  if(mtxs == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < *n;++i) {
    if(pthread_mutex_init(&mtxs[i], NULL) != 0) {
      fprintf(stderr, "Eroare cond init!\n");
      exit(EXIT_FAILURE);
    }
  }

  int *status = (int *)malloc(sizeof(int));
  if(status == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  *status = 0;

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
    int j;
    int *index = (int *)malloc(sizeof(int));
    if(index == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    *index = 0;

    int *team = (int *)malloc(sizeof(int));
    if(team == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    *team = i;

    for(j = 0;j < TEAM_SIZE;++j) {
      data *info = (data *)malloc(sizeof(data));
      if(info == NULL) {
        fprintf(stderr, "Eroare malloc!\n");
        exit(EXIT_FAILURE);
      }

      int *curr_here = (int *)malloc(sizeof(int));
      if(curr_here == NULL) {
        fprintf(stderr, "Eroare malloc!\n");
        exit(EXIT_FAILURE);
      }
      *curr_here = j;

      info->curr_here = curr_here;
      info->index = index;
      info->mtx = &mtxs[i];
      info->status = status;
      info->cond = &conds[i];
      info->team = team;
      info->barr = barr;

      if(pthread_create(&ths[i][j], NULL, routine, (void *)info) != 0) {
        fprintf(stderr, "Eroare pthread create!\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  for(i = 0;i < *n;++i) {
    int j;
    for(j = 0;j < TEAM_SIZE;++j) {
      if(pthread_join(ths[i][j], NULL) != 0) {
        fprintf(stderr, "Eroare pthread join!\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  for(i = 0;i < *n;++i) {
    if(pthread_mutex_destroy(&mtxs[i]) != 0) {
        fprintf(stderr, "Eroare mutex destroy!\n");
        exit(EXIT_FAILURE);
    }

    if(pthread_cond_destroy(&conds[i]) != 0) {
        fprintf(stderr, "Eroare mutex destroy!\n");
        exit(EXIT_FAILURE);
    }
  }

  for(i = 0;i < *n;++i) {
    free(ths[i]);
  }

  free(n);
  free(conds);
  free(ths);
  free(barr);
  free(status);
  free(mtxs);

  return 0;
}
