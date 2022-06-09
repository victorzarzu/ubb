#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MTX_SIZE 10

typedef struct {
  pthread_mutex_t *mtxs;
  char* numar;
  int* freq;
} data;

void *routine(void *arg) {
  data* info = (data *)arg;
  int len = strlen(info->numar), i;

  for(i = 0;i < len;++i) {
    int cifra = info->numar[i] - '0';
    pthread_mutex_lock(&info->mtxs[cifra]);
    info->freq[cifra]++;
    pthread_mutex_unlock(&info->mtxs[cifra]);
  }

  free(info);

  return NULL;
}

int main(int argc, char** argv) {
  if(argc == 1) {
    fprintf(stderr, "Numar incorect de argumente!\n");
    exit(EXIT_FAILURE);
  }
  else {
    int i, n;
    for(i = 1;i < argc;++i) {
      if(sscanf(argv[i], "%d", &n) <= 0) {
        fprintf(stderr, "Argumentele trebuie sa fie numere!\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  int *freq = (int *)malloc(sizeof(int) * MTX_SIZE);
  if(freq == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  memset(freq, 0, sizeof(int) * MTX_SIZE);

  int n = argc - 1;
  pthread_t *ths = (pthread_t *)malloc(sizeof(pthread_t) * n);
  if(ths == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  
  pthread_mutex_t *mtxs = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * MTX_SIZE);
  if(mtxs == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i = 0;i < MTX_SIZE;++i){
    if(pthread_mutex_init(&mtxs[i], NULL) != 0) {
      fprintf(stderr, "Eroare mutex init!\n");
      exit(EXIT_FAILURE);
    }
  }
  for(i = 0;i < n;++i) {
    data *info = (data *)malloc(sizeof(data));
    if(info == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    info->mtxs = mtxs;
    info->numar = argv[i + 1];
    info->freq = freq;

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

  for(i = 0;i < MTX_SIZE;++i){
    if(pthread_mutex_destroy(&mtxs[i]) != 0) {
      fprintf(stderr, "Eroare mutex destroy!\n");
      exit(EXIT_FAILURE);
    }
  }

  for(i = 0;i < MTX_SIZE;++i) {
    printf("%d ", freq[i]);
  }
  printf("\n");

  free(freq);
  free(ths);
  free(mtxs);


  return 0;
}
