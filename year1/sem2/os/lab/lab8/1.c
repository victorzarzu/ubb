#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
  if(argc < 2){
    perror("prea putine argumente");
    exit(1);
  }
  int n, i;
  sscanf(argv[1], "%d", &n);
  if(n <= 0){
    perror("argument invalid");
    exit(1);
  }

  for(i = 0;i < n;++i){
    int pid = fork();
    if(pid == -1){
      perror("eroare fork");
      exit(EXIT_FAILURE);
    }
    else if(pid == 0){
      printf("Fiu: PID - %d, PPID - %d\n", getpid(), getppid());
      exit(EXIT_SUCCESS);
    }

    printf("Parinte: PID - %d, PID copil - %d\n", getpid(), pid);
  }

  for(i = 0;i < n;++i){
    wait(0);
  }

  return 0;
}
