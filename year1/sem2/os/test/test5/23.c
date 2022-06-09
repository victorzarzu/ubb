#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_SIZE 100

typedef struct {
  pthread_mutex_t* mtx;
  int* curr_poz;
  int* curr_size;
  char* argument;
  char* sir;
} data_vocale;

typedef struct {
  pthread_mutex_t* mtx;
  int* sum;
  char* argument;
} data_cifre;


void redim(char* sir, int *curr_size) { 
  *curr_size *= 2;
  sir = (char *)realloc(sir, *curr_size);
}

void *vocale(void* arg) {
  data_vocale* info = (data_vocale *)arg;
  int len = strlen(info->argument), i;

  for(i = 0;i < len;++i) {
    if(strchr("aeiou", info->argument[i]) != NULL) {
      pthread_mutex_lock(info->mtx);
      
      if(*info->curr_size - 1 == *info->curr_poz) {
        redim(info->sir, info->curr_size);
      }
      info->sir[*info->curr_poz] = info->argument[i];
      *info->curr_poz = *info->curr_poz + 1;

      pthread_mutex_unlock(info->mtx);
    }
  }

  free(info);

  return NULL;
}

void *cifre(void* arg) {
  data_cifre* info = (data_cifre *)arg;
  int len = strlen(info->argument), i;

  for(i = 0;i < len;++i) {
    if(isdigit(info->argument[i])) {
      pthread_mutex_lock(info->mtx);
      
      *info->sum = *info->sum + (info->argument[i] - '0');

      pthread_mutex_unlock(info->mtx);
    }
  }

  free(info);

  return NULL;
}
int main(int argc, char **argv) {
  if(argc == 1) {
    fprintf(stderr, "Numar de argumente incorect!\n");
    exit(EXIT_FAILURE);
  }

  int child_1, child_2;

  child_1 = fork();
  if(child_1 == -1) {
    fprintf(stderr, "Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child_1 == 0) {
    char* sir = (char *)malloc(sizeof(char) * INITIAL_SIZE); 
    if(sir == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    pthread_mutex_t* mtx = (pthread_mutex_t * )malloc(sizeof(pthread_mutex_t));
    if(mtx == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    if(pthread_mutex_init(mtx, NULL) != 0) {
      fprintf(stderr, "Eroare mutex init!\n");
      exit(EXIT_FAILURE);
    }

    pthread_t* ths = (pthread_t *)malloc(sizeof(pthread_t) * argc);
    if(ths == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    int *size = (int *)malloc(sizeof(int));
    if(size == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    *size = 0;

    int *poz = (int *)malloc(sizeof(int));
    if(poz == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    *poz = 0;

    int i;
    for(i = 1;i < argc;++i) {
      data_vocale* info = (data_vocale *)malloc(sizeof(data_vocale));
      if(info == NULL) {
        fprintf(stderr, "Eroare malloc!\n");
        exit(EXIT_FAILURE);
      }

      info->sir = sir;
      info->curr_poz = poz;
      info->curr_size = size;
      info->mtx = mtx;
      info->argument = argv[i];
      
      if(pthread_create(&ths[i], NULL, vocale, (void *)info) != 0) {
        fprintf(stderr, "Eroare pthread_create!\n");
        exit(EXIT_FAILURE);
      }
    }

    for(i = 1;i < argc;++i) {
      if(pthread_join(ths[i], NULL) != 0) {
        fprintf(stderr, "Eroare pthread_join!\n");
        exit(EXIT_FAILURE);
      }
    }

    printf("Sir vocale: %s\n", sir);

    if(pthread_mutex_destroy(mtx) != 0) {
      fprintf(stderr, "Eroare mutex init!\n");
      exit(EXIT_FAILURE);
    }

    free(mtx);
    free(ths);
    free(size);
    free(sir);
    free(poz);

    exit(EXIT_SUCCESS);
  }

  child_2 = fork();
  if(child_2 == -1) {
    fprintf(stderr, "Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child_2 == 0) {
    int *sum = (int *)malloc(sizeof(int));
    if(sum == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    *sum = 0;

    pthread_mutex_t* mtx = (pthread_mutex_t * )malloc(sizeof(pthread_mutex_t));
    if(mtx == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    if(pthread_mutex_init(mtx, NULL) != 0) {
      fprintf(stderr, "Eroare mutex init!\n");
      exit(EXIT_FAILURE);
    }

    pthread_t* ths = (pthread_t *)malloc(sizeof(pthread_t) * argc);
    if(ths == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    int i;
    for(i = 1;i < argc;++i) {
      data_cifre* info = (data_cifre *)malloc(sizeof(data_cifre));
      if(info == NULL) {
        fprintf(stderr, "Eroare malloc!\n");
        exit(EXIT_FAILURE);
      }

      info->sum = sum;
      info->mtx = mtx;
      info->argument = argv[i];
      
      if(pthread_create(&ths[i], NULL, cifre, (void *)info) != 0) {
        fprintf(stderr, "Eroare pthread_create!\n");
        exit(EXIT_FAILURE);
      }
    }

    for(i = 1;i < argc;++i) {
      if(pthread_join(ths[i], NULL) != 0) {
        fprintf(stderr, "Eroare pthread_join!\n");
        exit(EXIT_FAILURE);
      }
    }

    printf("Suma cifre: %d\n", *sum);

    free(sum);
    free(mtx);
    free(ths);

    exit(EXIT_SUCCESS);
  }

  wait(0); wait(0);

  return 0;
}
