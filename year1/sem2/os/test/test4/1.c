#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar incorect de argumente\n");
    exit(EXIT_FAILURE);
  }

  int n, i;
  sscanf(argv[1], "%d", &n);
  
  for(i = 0;i < n;++i) {
    int result = fork();
    if(result < 0) {
      printf("Eroare fork");
      exit(EXIT_FAILURE);
    }
    else if(result == 0) {
      printf("Copil: PID - %d | PPID - %d\n", getpid(), getppid());
      exit(0);
    }
    else {
      printf("Parinte: PID - %d | PID fiu  - %d\n", getpid(), result);
    }
  }

  for(i = 0;i < n;++i) {
    wait(0);
  }

  return 0;
}
