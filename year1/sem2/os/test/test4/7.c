#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  srand((unsigned int)getpid());
  int p2c[2], c2p[2], number;

  if(pipe(p2c) < 0) {
    printf("Eroare pipe\n");
    exit(EXIT_FAILURE);
  }

  if(pipe(c2p) < 0) {
    printf("Eroare pipe\n");
    exit(EXIT_FAILURE);
  }

  int child_pid = fork();
  if(child_pid < 0) {
    printf("Eroare pipe\n");
    exit(EXIT_FAILURE);
  }
  else if(child_pid == 0) {
    close(p2c[1]); close(c2p[0]);

    while(1) {
      if(read(p2c[0], &number, sizeof(int)) < 0) {
          printf("Eroare read\n");
          exit(EXIT_FAILURE);
      }
      
      printf("B: %d\n", number);
      if(number == 10) {
        break;
      }

      number = rand() % 10 + 1;
      if(write(c2p[1], &number, sizeof(int)) < 0) {
        printf("Eroare write\n");
        exit(EXIT_FAILURE);
      }

      if(number == 10) {
        break;
      }
    }
    close(p2c[0]); close(c2p[1]);
    exit(EXIT_SUCCESS);
  }

  child_pid = fork();
  if(child_pid < 0) {
    printf("Eroare pipe\n");
    exit(EXIT_FAILURE);
  }
  else if(child_pid == 0) {
    close(p2c[0]); close(c2p[1]);

    while(1) {
      number = rand() % 10 + 1;
      if(write(p2c[1], &number, sizeof(int)) < 0) {
        printf("Eroare write\n");
        exit(EXIT_FAILURE);
      }

      if(number == 10) {
        break;
      }

      if(read(c2p[0], &number, sizeof(int)) < 0) {
        printf("Eroare read\n");
        exit(EXIT_FAILURE);
      }

      printf("A: %d\n", number);
      
      if(number == 10) {
        break;
      }
    }

    close(p2c[1]); close(c2p[0]);

  }
    wait(0); wait(0);

  return 0;
}
