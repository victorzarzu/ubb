#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define TEAM_SIZE 4

typedef struct {
  pthread_mutex_t *mtx;
  pthread_barrier_t *barr;
  pthread_cond_t* cond;
  int team_id;
  int id_in_team;
  int *team_len;
  int *status;
} data;

void* routine(void *arg) {
  data* info = (data *)arg;

  if(info->id_in_team == 0) {
    pthread_barrier_wait(info->barr);
  }

  pthread_mutex_lock(info->mtx);

  while(*info->team_len != info->id_in_team) {
    pthread_cond_wait(info->cond, info->mtx);
  }

  printf("Echipa %d - Thread: %d -> %d\n", info->team_id, *info->team_len, *info->team_len + 1);
  *info->team_len = *info->team_len + 1;

  if(*info->status == 0 && info->id_in_team == TEAM_SIZE - 1) {
    *info->status = 1;
    printf("Echipa %d a castigat!\n", info->team_id);
  }

  pthread_mutex_unlock(info->mtx);

  pthread_cond_broadcast(info->cond);

  int random = rand() % 101 + 100;
  usleep(random * 1000);

  if(info->id_in_team == TEAM_SIZE - 1) {
    free(info->team_len);
  }

  free(info); 
  return NULL;
}

int main(int argc, char **argv) {
  int n;
  printf("Numar: ");
  if(scanf("%d", &n) <= 0) {
    fprintf(stderr, "Un numar!\n");
    exit(EXIT_FAILURE);
  }
  srand(time(NULL));

  pthread_t **ths = (pthread_t **)malloc(sizeof(pthread_t *) * n);
  if(ths == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i = 0;i < n;++i) {
    ths[i] = (pthread_t *)malloc(sizeof(pthread_t) * TEAM_SIZE);
    if(ths[i] == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
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

  pthread_mutex_t *mtxs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n);
  if(mtxs == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < n;++i) {
    if(pthread_mutex_init(&mtxs[i], NULL) != 0) {
      fprintf(stderr, "Eroare mutex init!\n");
      exit(EXIT_FAILURE);
    }
  }

  pthread_cond_t *conds = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * n);
  if(conds == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < n;++i) {
    if(pthread_cond_init(&conds[i], NULL) != 0) {
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

  int j;
  for(i = 0;i < n;++i) {
    int *team_len = (int *)malloc(sizeof(int));
    if(team_len == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    *team_len = 0;

    for(j = 0;j < TEAM_SIZE;++j) {
      data* info = (data *)malloc(sizeof(data));
      if(info == NULL) {
        fprintf(stderr, "Eroare malloc!\n");
        exit(EXIT_FAILURE);
      }
      info->barr = barr;
      info->mtx = &mtxs[i];
      info->cond = &conds[i];
      info->id_in_team = j;
      info->team_id = i;
      info->team_len = team_len;
      info->status = status;

      if(pthread_create(&ths[i][j], NULL, routine, (void *)info) != 0) {
        fprintf(stderr, "Eroare pthread_create!\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  for(i = 0;i < n;++i) {
    for(j = 0;j < TEAM_SIZE;++j) {
      if(pthread_join(ths[i][j], NULL) != 0) {
        fprintf(stderr, "Eroare pthread_join!\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  for(i = 0;i < n;++i) {
    if(pthread_mutex_destroy(&mtxs[i]) != 0) {
      fprintf(stderr, "Eroare mutex destroy!\n");
      exit(EXIT_FAILURE);
    }
  }
  if(pthread_barrier_destroy(barr) != 0) {
    fprintf(stderr, "Eroare barrier destroy!\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < n;++i) {
    if(pthread_cond_destroy(&conds[i]) != 0) {
      fprintf(stderr, "Eroare cond destroy!\n");
      exit(EXIT_FAILURE);
    }
  }

  free(barr);
  free(mtxs);

  for(i = 0;i < n;++i) {
    free(ths[i]);
  }
  free(ths);
  free(conds);
  free(status);

  return 0;
}
