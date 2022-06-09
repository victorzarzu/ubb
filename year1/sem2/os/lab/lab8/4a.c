#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>

int main(int argc, char** argv){
  if(argc < 2){
    perror("prea putine argumente");
    exit(EXIT_FAILURE);
  }

  struct timeval t1, t2;

  gettimeofday(&t1, NULL);
  int status = fork();
  if(status == -1){
    perror("eroare fork");
    exit(EXIT_FAILURE);
  }
  else if(status == 0){
    execvp(argv[1], argv + 1); 
    exit(EXIT_FAILURE);
  }
  else{
    wait(0);
    gettimeofday(&t2, NULL);

    fflush(stdout);
    printf("Secunde: %lf\n", (double)(t2.tv_usec - t1.tv_usec) / 1000 + (double)(t2.tv_sec - t1.tv_sec));
  }
  
  return 0;
}
