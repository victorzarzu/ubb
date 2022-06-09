#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

typedef struct {
  int n;
  int *sir;
  pthread_mutex_t *mtx;
  pthread_cond_t *cond;
  int *sorted;
} data;

int is_sorted(int *sir, int n) {
  int i = 0;
  for(i = 0;i < n - 1;++i) {
    if(sir[i] > sir[i + 1]) {
      return 0;
    }
  }

  return 1;
}

void *work(void *arg) {
  data *info = (data *)arg;

  while(1) {
    int i = rand() % info->n;
    int j = i;
    while(j == i) {
      j = rand() % info->n;
    }

    pthread_mutex_lock(info->mtx);

    if(*info->sorted) {
      break;
    }

    if((i - j) * (info->sir[i] - info->sir[j]) < 0) {
      info->sir[i] ^= info->sir[j];
      info->sir[j] ^= info->sir[i];
      info->sir[i] ^= info->sir[j];
    }

    *info->sorted = is_sorted(info->sir, info->n);

    if(*info->sorted) {
      break;
    }

    pthread_mutex_unlock(info->mtx);
  }

  pthread_mutex_unlock(info->mtx);
  pthread_cond_signal(info->cond);

  return NULL;
}


void *print(void *arg) {
  data *info = (data *)arg;

  pthread_mutex_lock(info->mtx);

  while(info->sorted == 0) {
    pthread_cond_wait(info->cond, info->mtx);
  }

  int i;
  for(i = 0;i < info->n;++i) {
    printf("%d ", info->sir[i]);
  }
  printf("\n");

  pthread_mutex_unlock(info->mtx);

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

  int *sir = (int *)malloc(sizeof(int) * n);
  if(sir == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i = 0;i < n;++i) {
    sir[i] = rand() % 1001;
  }

  pthread_mutex_t *mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
  if(mtx == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  if(pthread_mutex_init(mtx, NULL) != 0) {
    fprintf(stderr, "Eroare mutex init!\n");
    exit(EXIT_FAILURE);
  }

  pthread_cond_t *cond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
  if(cond == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  if(pthread_cond_init(cond, NULL) != 0) {
    fprintf(stderr, "Eroare cond init!\n");
    exit(EXIT_FAILURE);
  }
  
  int *sorted = (int *)malloc(sizeof(int));
  if(sorted == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  *sorted = 0;

  data *info = (data *)malloc(sizeof(data));
  if(info == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  info->n = n;
  info->sorted = sorted;
  info->mtx = mtx;
  info->sir = sir;
  info->cond = cond;

  pthread_t *ths = (pthread_t *)malloc(sizeof(pthread_t) * (n + 1));
  if(ths == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }


  for(i = 0;i < n;++i) {
    if(pthread_create(&ths[i], NULL, work, (void *)info) != 0) {
      fprintf(stderr, "Eroare pthread create!\n");
      exit(EXIT_FAILURE);
    }
  }

  if(pthread_create(&ths[n], NULL, print, (void *)info) != 0) {
    fprintf(stderr, "Eroare pthread create!\n");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i <= n;++i) {
    if(pthread_join(ths[i], NULL) != 0) {
      fprintf(stderr, "Eroare pthread join!\n");
      exit(EXIT_FAILURE);
    }
  }

  if(pthread_mutex_destroy(mtx) != 0) {
    fprintf(stderr, "Eroare mutex destroy!\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_cond_destroy(cond) != 0) {
    fprintf(stderr, "Eroare cond destroy!\n");
    exit(EXIT_FAILURE);
  }

  free(ths);
  free(mtx);
  free(cond);
  free(sir);
  free(sorted);
  
  return 0;
}
