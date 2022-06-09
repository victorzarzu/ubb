#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


void create_process(int n){
  if(n){
    int pid = fork();
    if(pid == -1){
      perror("eroare fork");
      exit(EXIT_FAILURE);
    }
    else if(pid == 0){
      printf("Proces: PID - %d, PPID - %d\n", getpid(), getppid());
      create_process(n - 1);
    }
    wait(0);
   }
  exit(0);
}

int main(int argc, char** argv){
  
  create_process(5); 

  return 0;
}
