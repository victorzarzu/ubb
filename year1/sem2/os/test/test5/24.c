#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct {
  int fd;
  int id;
} data;

void *routine(void *arg) {
  data* info = (data *)arg;

  int x = rand() % 100 + 1;
  if(write(info->fd, &x, sizeof(int)) < 0) {
    fprintf(stderr, "Eroare write!\n");
    exit(EXIT_FAILURE);
  }
  int y = rand() % 100 + 1;
  if(write(info->fd, &y, sizeof(int)) < 0) {
    fprintf(stderr, "Eroare write!\n");
    exit(EXIT_FAILURE);
  }

  if(write(info->fd, &(info->id), sizeof(int)) < 0) {
    fprintf(stderr, "Eroare write!\n");
    exit(EXIT_FAILURE);
  }
  printf("Id: %d - %d + %d\n", info->id, x, y);

  free(info);

  return NULL;
}

int main(int argc, char **argv) {
  if(argc != 2) {
    fprintf(stderr, "Numar incorect de argumente!\n");
    exit(EXIT_FAILURE);
  }

  int n;
  if(sscanf(argv[1], "%d", &n) <= 0) {
    fprintf(stderr, "Argumentul trebuie sa fie un numar!\n");
    exit(EXIT_FAILURE);
  }

  pthread_t* ths = (pthread_t *)malloc(sizeof(pthread_t) * n);
  if(ths == NULL) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  int t2p[2];
  if(pipe(t2p) < 0) {
    fprintf(stderr, "Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }

  int child = fork();
  if(child < 0) {
    fprintf(stderr, "Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }
  else if(child == 0) {
    close(t2p[1]);
  
    int x, y, id, i;
    for(i = 0;i < n;++i) {
      if(read(t2p[0], &x, sizeof(int)) < 0) {
        fprintf(stderr, "Eroare read!\n");
        exit(EXIT_FAILURE);
      }
      if(read(t2p[0], &y, sizeof(int)) < 0) {
        fprintf(stderr, "Eroare read!\n");
        exit(EXIT_FAILURE);
      }
      if(read(t2p[0], &id, sizeof(int)) < 0) {
        fprintf(stderr, "Eroare read!\n");
        exit(EXIT_FAILURE);
      }

      double medie = (double)(x + y) / 2;
      printf("Id: %d - Medie : %lf\n", id, medie);
    }

    close(t2p[0]);
    exit(EXIT_SUCCESS);
  }

  close(t2p[0]);

  int i;
  for(i = 0;i < n;++i) {
    data* info = (data *)malloc(sizeof(data));
    if(info == NULL) {
      fprintf(stderr, "Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    info->fd = t2p[1];
    info->id = i;

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

  close(t2p[1]);

  wait(0);
  free(ths);

  return 0;
}
