#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int pid;

void child_handler(int sgn){
  printf("Child stops...\n");
  exit(0);
}

void parent_handler(int sgn){
  printf("Parent stops...\n");
  kill(pid, SIGUSR1);
  wait(0);
  exit(0);
}

void zombie_handler(int sgn){
  wait(0);
}

int main(int argc, char** argv){

  pid = fork();
  if(pid == -1){
    perror("eroare fork");
    exit(EXIT_FAILURE);
  }
  else if(pid == 0){
    signal(SIGUSR1, child_handler);
    while(1){
      printf("Children working...\n");
      sleep(3);
    }
    exit(0);
  }
  else{
    signal(SIGUSR1, parent_handler);
    signal(SIGCHLD, zombie_handler);

    while(1){
      printf("Parent working...\n");
      sleep(2);
    }
  }

  return 0;
}
