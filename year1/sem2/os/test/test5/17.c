#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_RND 10000

typedef struct {
  int *sir;
  int *curr_len;
  int n;
  pthread_mutex_t *mtxs;
} data;

void *routine1(void *arg) {
  data *info = (data *)arg;

  while(1) { 
    pthread_mutex_lock(&(info->mtxs[0]));
    
    if(*(info->curr_len) == info->n) {
      break;
    }

    int numar = rand() % MAX_RND;
    if(numar % 2) {
      numar++;
    }

    info->sir[*info->curr_len] = numar;
    *info->curr_len = *info->curr_len + 1;

    pthread_mutex_unlock(&(info->mtxs[1])); 
  }

  pthread_mutex_unlock(&(info->mtxs[0]));
  pthread_mutex_unlock(&(info->mtxs[1]));

  return NULL;
}

void *routine2(void *arg) {
  data *info = (data *)arg;

  while(1) {
    pthread_mutex_lock(&(info->mtxs[1]));

    if(*(info->curr_len) == info->n) {
      break;
    }
    int numar = rand() % MAX_RND;
    if(!(numar % 2)) {
      numar++;
    }

    info->sir[*info->curr_len] = numar;
    *info->curr_len = *info->curr_len + 1;

    pthread_mutex_unlock(&(info->mtxs[0]));
  }

  pthread_mutex_unlock(&(info->mtxs[0]));
  pthread_mutex_unlock(&(info->mtxs[1]));

  return NULL;
}

int main(int argc, char** argv) {
  int n;
  if(scanf("%d", &n) <= 0) {
    fprintf(stderr, "Un numar este necesar!\n");
    exit(EXIT_FAILURE);
  }

  int *curr_len = (int *)malloc(sizeof(int)); 
  if(curr_len == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  *curr_len = 0;

  int *sir = (int *)malloc(sizeof(int) * n); 
  if(sir == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  pthread_t *ths = (pthread_t *)malloc(sizeof(pthread_t) * 2);
  if(ths == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  pthread_mutex_t *mtxs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 2);
  if(mtxs == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i = 0;i < 2;++i) {
    if(pthread_mutex_init(&mtxs[i], NULL) != 0) {
      fprintf(stderr, "Eroare mutex init!\n");
      exit(EXIT_FAILURE);
    }
  }
  data* info = (data *)malloc(sizeof(data));
  if(info == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  info->n = n;
  info->curr_len = curr_len;
  info->sir = sir;
  info->mtxs = mtxs;

  pthread_mutex_lock(&mtxs[1]);

  if(pthread_create(&ths[0], NULL, routine1, (void *)info) != 0) {
    fprintf(stderr, "Eroare pthread create!\n");
    exit(EXIT_FAILURE);
  }

  if(pthread_create(&ths[1], NULL, routine2, (void *)info) != 0) {
    fprintf(stderr, "Eroare pthread create!\n");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < 2;++i) {
    if(pthread_join(ths[i], NULL) != 0) {
      fprintf(stderr, "Eroare pthread join!\n");
      exit(EXIT_FAILURE);
    }
  }

  for(i = 0;i < 2;++i) {
    if(pthread_mutex_destroy(&mtxs[i]) != 0) {
      fprintf(stderr, "Eroare mutex destroy!\n");
      exit(EXIT_FAILURE);
    }
  }

  for(i = 0;i < n;++i) {
    printf("%d ", sir[i]);
  }
  printf("\n");

  free(curr_len);
  free(sir);
  free(mtxs);
  free(ths);

  return 0;
}
