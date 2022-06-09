#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int child;

void child_handler(int sig) {
  printf("Child stops...\n");
  exit(0);
}

void parent_handler(int sig) {
  kill(child, SIGUSR1);
  wait(0);
  printf("Parent stops...\n");
  exit(0);
}

void zombie_handler(int sig) {
  printf("Child is zombie\n");
  wait(0);
}

int main(int argc, char** argv) {
  
  child = fork();
  if(child == -1) {
    printf("Eroare fork\n");
    exit(EXIT_FAILURE);
  }
  else if(child == 0) {
    signal(SIGUSR1, child_handler);
    while(1) {
      printf("Child works...\n");
      sleep(2);
    }
  }
  else {
    signal(SIGUSR1, parent_handler);
    signal(SIGCHLD, zombie_handler);
    while(1) {
      printf("Parent works...\n");
      sleep(2);
    }
  }
  
  return 0;
}
