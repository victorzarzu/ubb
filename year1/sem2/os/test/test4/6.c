#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_RAND 5000

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar argumente incorect\n");
    exit(EXIT_FAILURE);
  }

  int p2c[2], c2p[2];
  if(pipe(p2c) < 0) {
    printf("Eroare pipe\n");
    exit(EXIT_FAILURE);
  }

  if(pipe(c2p) < 0) {
    printf("Eroare pipe\n");
    exit(EXIT_FAILURE);
  }

  srand((unsigned int)getpid());

  int child_pid = fork();
  if(child_pid == -1) {
    printf("Eroare fork\n");
    exit(EXIT_FAILURE);
  }
  else if(child_pid == 0) {
    close(p2c[1]); close(c2p[0]);  

    int n, i;
    if(read(p2c[0], &n, sizeof(int)) < 0) {
        printf("Eroare write\n");
        exit(EXIT_FAILURE);
    }

    double average = 1;
    int x;
    for(i = 0;i < n;++i) {
      if(read(p2c[0], &x, sizeof(int)) < 0) {
              printf("Eroare write\n");
              exit(EXIT_FAILURE);
      }
      average += x;
    }
    close(p2c[0]);

    average /= n;
    if(write(c2p[1], &average, sizeof(double)) < 0) {
          printf("Eroare write\n");
          exit(EXIT_FAILURE);
    }
    close(c2p[1]);

    exit(EXIT_SUCCESS);
  }

  close(p2c[0]); close(c2p[1]);

  int n;
  if(sscanf(argv[1], "%d", &n) < 0) {
    printf("Argumentul trebuie sa fie un numar\n");
    exit(EXIT_FAILURE);
  } 

  if(n <= 0) {
    printf("Argumentul trebuie sa fie un numar strict pozitiv\n");
    exit(EXIT_FAILURE);
  }

  if(write(p2c[1], &n, sizeof(int)) < 0) {
      printf("Eroare write\n");
      exit(EXIT_FAILURE);
  }

  int i, number;

  for(i = 0;i < n;++i) {
    number = rand() % MAX_RAND;
    if(write(p2c[1], &number, sizeof(int)) < 0) {
      printf("Eroare write\n");
      exit(EXIT_FAILURE);
    }
  }
  close(p2c[1]);

  wait(0);

  double average;
  if(read(c2p[0], &average, sizeof(double)) < 0) {
      printf("Eroare write\n");
      exit(EXIT_FAILURE);
  }
  close(c2p[0]);

  printf("Medie: %.3lf\n", average);

  return 0;
}
