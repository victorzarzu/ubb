#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar incorect de argumente!\n");
    exit(EXIT_FAILURE);
  }
  int a2b[2], b2c[2], c2a[2];
  if(pipe(a2b)) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }
  if(pipe(b2c)) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }
  if(pipe(c2a)) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }
  
  int child1 = fork();
  if(child1 < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child1 == 0) {
    close(a2b[1]); close(b2c[0]); close(c2a[0]); close(c2a[1]);
    srand((unsigned int)getpid());
    int n, i, x;
    if(read(a2b[0], &n, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_SUCCESS);
    }
    if(write(b2c[1], &n, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_SUCCESS);
    }

    for(i = 0;i < n;++i) {
      if(read(a2b[0], &x, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_SUCCESS);
      }  
      printf("Received by B: %d\n", x);
      x += rand() % 4 + 2;

      if(write(b2c[1], &x, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_SUCCESS);
      }
      printf("Sent by B: %d\n", x);
    }

    close(a2b[0]); close(b2c[1]);
    exit(EXIT_SUCCESS);
  }

  int child2 = fork();
  if(child2 < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child2 == 0) {
    close(b2c[1]); close(c2a[0]); close(a2b[1]); close(a2b[1]);

    int n, i, x, sum = 0;
    if(read(b2c[0], &n, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_SUCCESS);
    }

    for(i = 0;i < n;++i) {
      if(read(b2c[0], &x, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_SUCCESS);
      }  
      printf("Received by C: %d\n", x);
      sum += x;
    }

    if(write(c2a[1], &sum, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_FAILURE);
    }
    printf("Send by C: %d\n", sum);

    close(b2c[0]); close(c2a[1]);
    exit(EXIT_SUCCESS);
  }

  close(a2b[0]); close(c2a[1]); close(b2c[0]); close(b2c[1]);

  int n;
  if(sscanf(argv[1], "%d", &n) <= 0) {
    printf("Argumentul trebuie sa fie un numar!\n");
    exit(EXIT_FAILURE);
  }
  if(n <= 0) {
    printf("Argumentul trebuie sa fie un numar strict pozitiv!\n");
    exit(EXIT_FAILURE);
  }
  if(write(a2b[1], &n, sizeof(int)) < 0) {
    printf("Eroare write!\n");
    exit(EXIT_FAILURE);
  }

  int i, x;
  for(i = 0;i < n;++i) {
    if(scanf("%d", &x) <= 0) {
      printf("Eroare scanf!\n");
      exit(EXIT_FAILURE);
    }
    
    if(write(a2b[1], &x, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_FAILURE);
    }
    printf("Sent by A: %d\n", x);
  }

  close(a2b[1]); 

  if(read(c2a[0], &x, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
  }
  close(c2a[0]);

  printf("Suma: %d\n", x);

  wait(0); wait(0);
  return 0;
}
