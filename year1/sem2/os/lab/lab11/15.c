#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

struct info {
  int *cifre, *litere, *speciale;
  pthread_mutex_t* ms;
  char* line;
};

void* routine(void* arg) {
  int i;
  int cif = 0, lit = 0, sp = 0;
  struct info* inf = (struct info*)arg;
  for(i = 0;inf->line[i] != 0;++i) {
    if(islower(inf->line[i]) || isupper(inf->line[i])) {
      ++lit; 
    }
    else if(isdigit(inf->line[i])) {
      ++cif;
    }
    else {
      ++sp;
    }
  }
  pthread_mutex_lock(&inf->ms[0]);
  *(inf->cifre) += cif;
  pthread_mutex_unlock(&inf->ms[0]);

  pthread_mutex_lock(&inf->ms[1]);
  *(inf->litere) += lit;
  pthread_mutex_unlock(&inf->ms[1]);

  pthread_mutex_lock(&inf->ms[2]);
  *(inf->speciale) += sp;
  pthread_mutex_unlock(&inf->ms[2]);

  free(inf);

  return NULL;
}

int main(int argc, char** argv) {
  if(argc == 1) {
    printf("Numar insuficient de argumente!\n");
    exit(EXIT_FAILURE);
  }
  
  int *const cifre = (int *)malloc(sizeof(int));
  if(cifre == NULL) {
    printf("Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  int *const litere = (int *)malloc(sizeof(int));
  if(litere == NULL) {
    printf("Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  int *const speciale = (int *)malloc(sizeof(int));
  if(speciale == NULL) {
    printf("Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  pthread_mutex_t* ms = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * 3);
  if(ms == NULL) {
    printf("Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  int i;
  for(i = 0;i < 3;++i){ 
    if(pthread_mutex_init(&ms[i], NULL) != 0) {
      printf("Eroare mutex init!\n");
      exit(EXIT_FAILURE);
    }
  }

  pthread_t* threads = (pthread_t *)malloc(sizeof(pthread_t) * (argc - 1));
  if(threads == NULL) {
    printf("Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }


  for(i = 1;i < argc;++i) {
    struct info* inf = (struct info*)malloc(sizeof(struct info));
    if(inf == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    inf->cifre = cifre;
    inf->litere = litere;
    inf->speciale = speciale;
    inf->ms = ms;
    inf->line = argv[i];
    
    if(pthread_create(&threads[i - 1], NULL, routine, inf) != 0) {
      printf("Eroare thread create!\n");
      exit(EXIT_FAILURE);
    }
  }

  for(i = 1;i < argc;++i) {
    if(pthread_join(threads[i - 1], NULL) != 0) {
      printf("Eroare thread join!\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("Cifre: %d\nLitere: %d\nSpeciale: %d\n", *cifre, *litere, *speciale);

  free(threads);
  free(cifre);
  free(litere);
  free(speciale);
  for(i = 0;i < 3;++i){ 
    pthread_mutex_destroy(&ms[i]);
  }
  free(ms);

  return 0;
}
