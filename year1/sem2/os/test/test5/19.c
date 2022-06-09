#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


typedef struct {
  int *sir;
  int *index;
  int *group;
  int *step;
  pthread_barrier_t *in_barr, *up_barr;
} data;

int get_left_index_add(int *index, int *group, int* step) {
  return (*index - (1 << *group)) * (1 << *step);
}

int get_right_index_add(int *index, int *group, int *step) {
  return (*index - (1 << *group)) * (1 << *step) + ((1 << *step) - 1)  - ((1 << (*step - 1)) - 1);
}

void *routine(void *arg) {

  data* info = (data *)arg;
  if(info->in_barr != NULL) {
    pthread_barrier_wait(info->in_barr);
  }

  int left = get_left_index_add(info->index, info->group, info->step);
  int right = get_right_index_add(info->index, info->group, info->step);
  //printf("%d %d => %d %d => %d %d\n", *info->index, *info->group, left, right, info->sir[left], info->sir[right]);
  info->sir[left] += info->sir[right];
  //printf("%d %d => %d\n", left, right, info->sir[left]);

  free(info->group);
  free(info->step);

  if(*info->index != 1) {
    pthread_barrier_wait(info->up_barr);
  }

  free(info->index);
  free(info);
   
  return NULL;
}

int main(int argc, char** argv) {
  if(argc != 2) {
    fprintf(stderr, "Numar incorect de argumente!\n");
    exit(EXIT_FAILURE);
  }
  int n;
  if(sscanf(argv[1], "%d", &n) <= 0) {
    fprintf(stderr, "Arugmentul trebuie sa fie un numar!\n");
    exit(EXIT_FAILURE);
  }
  int m = 1, step = 0;
  while(m < n) {
    m <<= 1; 
    step++;
  }

  pthread_t *ths = (pthread_t *)malloc(sizeof(pthread_t) * m);
  if(ths == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  int *sir = (int *)malloc(sizeof(int) * 100);
  if(sir == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  memset(sir, 0, sizeof(int) * m);

  int i;
  for(i = 0;i < n;++i) {
    scanf("%d", &sir[i]);
  }

  pthread_barrier_t *barrs = (pthread_barrier_t *)malloc(sizeof(pthread_barrier_t) * (m >> 1));
  if(barrs == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  for(i = 1;i < m >> 1;++i) {
    if(pthread_barrier_init(&barrs[i], NULL, 3) != 0) {
      fprintf(stderr, "Eroare barrier init!\n");
      exit(EXIT_FAILURE);
    }
  }

  int cnt = 1, nr = 0, group = 0;
  for(i = 1;i < m;++i) {
    data* info = (data *)malloc(sizeof(data) * 1);
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

    int *group_th = (int *)malloc(sizeof(int));
    if(group_th == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    *group_th = group;
    info->group = group_th;

    int *step_th = (int *)malloc(sizeof(int));
    if(step_th == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    *step_th = step;
    info->step = step_th;

    info->sir = sir;

    if(i >= m >> 1) {
      info->in_barr = NULL;
    }
    else {
      info->in_barr = &barrs[i];
    }
    info->up_barr = &barrs[i / 2];


    if(pthread_create(&ths[i], NULL, routine, (void *)info) != 0) {
      fprintf(stderr, "Eroare pthread create!\n");
      exit(EXIT_FAILURE);
    }
    
    nr++;
    if(nr == cnt) {
      step--;
      group++;
      cnt <<= 1;
      nr = 0;
    }
  }


  for(i = 1;i < m;++i) {
    if(pthread_join(ths[i], NULL) != 0) {
      fprintf(stderr, "Eroare pthread join!\n");
      exit(EXIT_FAILURE);
    }
  }

  for(i = 1;i < m >> 1;++i) {
    if(pthread_barrier_destroy(&barrs[i]) != 0) {
      fprintf(stderr, "Eroare barrier destroy!\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("%d\n", sir[0]);

  free(ths);
  free(barrs);
  free(sir);

  return 0;
}
