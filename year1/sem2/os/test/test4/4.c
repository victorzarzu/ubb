#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("Argumente insuficiente\n");
    exit(EXIT_FAILURE);
  }

  struct timeval before;
  gettimeofday(&before, NULL);

  int result = fork();
  if(result < 0) {
    printf("Eroare fork\n");
    exit(EXIT_FAILURE);
  }
  else if(result == 0) {
    execvp(argv[1], argv + 1);
    printf("Eroare comanda\n");
    exit(EXIT_FAILURE);
  }
  wait(0);

  struct timeval after;
  gettimeofday(&after, NULL);
  printf("Duration: %d\n", (int)(after.tv_usec - before.tv_usec));
  
  return 0;


  return 0;
}
