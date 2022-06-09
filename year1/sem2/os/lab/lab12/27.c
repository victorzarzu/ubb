#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  char* sir;
  int* curr_len;
  int* curr_number;
  pthread_mutex_t *mut;
  pthread_cond_t *c_main;
  pthread_cond_t *c_write;
} data;

void *main_routine(void *arg) {
  data* info = (data*)arg;

  while(1) {
    pthread_mutex_lock(info->mut);

    while(*info->curr_len == 128) {
      pthread_cond_signal(info->c_write);
      pthread_cond_wait(info->c_main, info->mut);
    }
    if(*info->curr_number == 0) {
      break;
    }

    char random = 'a' + rand() % ('z' - 'a' + 1);
    info->sir[(*info->curr_len)++] = random;
    pthread_mutex_unlock(info->mut);
  }
  
  pthread_mutex_unlock(info->mut);

  return NULL;
}

void *write_routine(void *arg) {
  data* info = (data*)arg;

  while(1) {
    pthread_mutex_lock(info->mut);

    while(*info->curr_len != 128) {
      pthread_cond_wait(info->c_write, info->mut);
    }
    
    printf("%s\n", info->sir);
    *info->curr_number = *info->curr_number - 1;
    int i;
    for(i = 0;i < 128;++i) {
      info->sir[i] = '\0';
    }
    *info->curr_len = 0;
    if(*info->curr_number == 0) {
      break;
    }
    pthread_cond_broadcast(info->c_main);
    pthread_mutex_unlock(info->mut);
  }

  pthread_cond_broadcast(info->c_main);
  pthread_mutex_unlock(info->mut);

  return NULL;
}

int main(int argc, char** argv) {
  if(argc != 3) {
    fprintf(stderr, "Numar incorect de arguemente!\n");
    exit(EXIT_FAILURE);
  }

  char* sir = (char *)malloc(sizeof(char) * 129);
  if(sir == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  sir[128] = '\0';

  int* curr_len = (int *)malloc(sizeof(int));
  if(curr_len == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  *curr_len = 0;

  int* n = (int *)malloc(sizeof(int));
  if(n == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  int* m = (int *)malloc(sizeof(int));
  if(m == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  if(sscanf(argv[1], "%d", n) < 0) {
    fprintf(stderr, "Eroare sscanf!\n");
    exit(EXIT_FAILURE);
  }
  if(sscanf(argv[2], "%d", m) < 0) {
    fprintf(stderr, "Eroare sscanf!\n");
    exit(EXIT_FAILURE);
  }

  pthread_mutex_t* mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
  if(mut == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  if(pthread_mutex_init(mut, NULL) != 0) {
    fprintf(stderr, "Eroare mutex_init!\n");
    exit(EXIT_FAILURE);
  }

  pthread_t *ths = (pthread_t *)malloc(sizeof(pthread_t) * (*n));
  if(m == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  pthread_cond_t *c_main = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * (*n));
  if(c_main == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  if(pthread_cond_init(c_main, NULL) != 0) {
    fprintf(stderr, "Eroare cond init!\n");
    exit(EXIT_FAILURE);
  }

  pthread_cond_t *c_write = (pthread_cond_t *)malloc(sizeof(pthread_cond_t) * (*n));
  if(c_main == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  if(pthread_cond_init(c_write, NULL) != 0) {
    fprintf(stderr, "Eroare cond init!\n");
    exit(EXIT_FAILURE);
  }

  data* info = (data *)malloc(sizeof(data));
  info->sir = sir;
  info->curr_len = curr_len;
  info->curr_number = m;
  info->mut = mut;
  info->c_main = c_main;
  info->c_write = c_write;

  pthread_t th;

  int i;
  for(i = 0;i < *n;++i) {
    if(pthread_create(&ths[i], NULL, main_routine, info) != 0) {
      fprintf(stderr, "Eroare pthread_init!\n");
      exit(EXIT_FAILURE);
    }

  }
  if(pthread_create(&th, NULL, write_routine, info) != 0) {
      fprintf(stderr, "Eroare pthread_init!\n");
      exit(EXIT_FAILURE);
  }

  for(i = 0;i < *n;++i) {
    if(pthread_join(ths[i], NULL) != 0) {
      fprintf(stderr, "Eroare pthread_join!\n");
      exit(EXIT_FAILURE);
    }
  }
  if(pthread_join(th, NULL) != 0) {
      fprintf(stderr, "Eroare pthread_join!\n");
      exit(EXIT_FAILURE);
  }
  
  pthread_cond_destroy(c_write);
  pthread_cond_destroy(c_main);
  pthread_mutex_destroy(mut);
  free(info);
  free(ths);
  free(n);
  free(c_write);
  free(c_main);
  free(curr_len);
  free(m);
  free(sir);

  return 0;
}
