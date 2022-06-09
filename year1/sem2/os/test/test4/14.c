#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int rando(int a, int b) {
  return rand() % (b - a) + a;
}

int main(int argc, char** argv) {
  int a2b[2], b2a[2];
  if(pipe(a2b) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }
  if(pipe(b2a) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }

  int child = fork();
  if(child < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child == 0) {
    close(a2b[1]); close(b2a[0]); 
    srand((unsigned int)getpid());
    int n, m, flag = 1;

    while(flag) {
      if(read(a2b[0], &n, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_FAILURE);
      }

      m = rando(100, 1000);
      printf("Numbers in B: %d %d\n", n, m);
      if(abs(n - m) < 50) {
        flag = 0; 
      }

      if(write(b2a[1], &flag, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_SUCCESS);
      }
    }

    close(a2b[0]); close(b2a[1]);
    exit(EXIT_SUCCESS);
  }

  close(a2b[0]); close(b2a[1]);

  srand((unsigned int)getpid());
  int n, flag = 1;
  while(flag) {
    n = rando(50, 1050);
    if(write(a2b[1], &n, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_SUCCESS);
    }
    printf("Number in A: %d\n", n);

    if(read(b2a[0], &flag, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_SUCCESS);
    }
  }
  
  close(a2b[1]); close(b2a[0]);
  wait(0);

  return 0;
}
