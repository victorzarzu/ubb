#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  srand((unsigned int)getpid());

  int a2b[2], b2a[2];
  pipe(a2b); pipe(b2a);

  int result = fork();
  if(result == -1) {
    perror("eroare fork");
    exit(EXIT_FAILURE);
  }
  else if(result == 0) {
    close(a2b[0]); close(b2a[1]);
    
    while(1) {
      int random = rand() % 10 + 1; 
      write(a2b[1], &random, sizeof(int));
      
      if(random == 10) {
        break;
      }

      read(b2a[0], &random, sizeof(int));
      printf("Received in A: %d\n", random);
    
      if(random == 10) {
        break;
      }
    }
  
    close(a2b[1]); close(b2a[0]);
    exit(0); 
  }

  result = fork();
  if(result == -1) {
    perror("eroare fork");
    exit(EXIT_FAILURE);
  }
  else if(result == 0) {
    close(a2b[1]); close(b2a[0]); 
    while(1) {
      int random;
      read(a2b[0], &random, sizeof(int));
      
      printf("Received in B: %d\n", random);

      if(random == 10) {
        break;
      }

      random = rand() % 10 + 1;

      write(b2a[1], &random, sizeof(int));

      if(random == 10) {
        break;
      }
    }

    close(a2b[0]); close(b2a[1]);
    exit(0);
  }

  wait(0); wait(0);

  return 0;
}
