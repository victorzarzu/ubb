#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  int a2b[2], b2a[2], n;

  if(pipe(a2b) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_SUCCESS);
  }

  if(pipe(b2a) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_SUCCESS);
  }

  int child_pid = fork();
  if(child_pid < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_SUCCESS);
  }
  else if(child_pid == 0) {
    close(a2b[1]); close(b2a[0]);
    srand((unsigned int)getpid());
    
    while(1) {
      if(read(a2b[0], &n, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_FAILURE);
      } 

      n /= 2;
      if(write(b2a[1], &n, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_FAILURE);
      }

      if(n < 5) {
        break;
      }
    }
    
    close(a2b[0]); close(b2a[0]);
    exit(EXIT_SUCCESS);
  }

  close(a2b[0]); close(b2a[1]);
  srand((unsigned int)getpid());


  n = rand() % 150 + 50;
  while(1) {
    if(n % 2) {
      n++;
    }

    printf("Send: %d\n", n);
    if(write(a2b[1], &n, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_FAILURE);
    }

    if(read(b2a[0], &n, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_FAILURE);
    }
    printf("Receive: %d\n", n);

    if(n < 5) {
      break;
    }
  }

  close(a2b[1]); close(b2a[0]);
  wait(0);

  return 0;
}
