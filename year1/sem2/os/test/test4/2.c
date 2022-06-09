#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void create(int n) {
  if(n) {
    int result = fork();
    if(result < 0) {
      perror("Eroare fork\n");
      exit(EXIT_FAILURE);
    }
    else if(result == 0) {
      printf("Copil - PID: %d\n", getpid());
      create(n - 1);
    }
    wait(0);
  }
}

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar de argumente incorect\n");
    exit(EXIT_FAILURE);
  }
  int n;
  sscanf(argv[1], "%d", &n);
  if(n <= 0) {
    printf("Numar incorect\n");
    exit(EXIT_FAILURE);
  }

  create(n);

  return 0;
}
