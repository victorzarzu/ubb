#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
  int p2c[2], c2p[2], x, result;
  FILE* fisier;

  result = pipe(p2c);
  if(result == -1){
    perror("eroare pipe");
    exit(EXIT_FAILURE);
  }

  result = pipe(c2p);
  if(result == -1){
    perror("eroare pipe");
    exit(EXIT_FAILURE);
  }

  result = fork();
  if(result == -1){
    perror("eroare pipe");
    exit(EXIT_FAILURE);
  }
  else if(result == 0){
    close(p2c[1]); close(c2p[0]);

    int sum;
    read(p2c[0], &sum, sizeof(int));
    read(p2c[0], &x, sizeof(int));

    sum += x;

    write(c2p[1], &sum, sizeof(int));
    
    close(p2c[0]); close(c2p[1]);
    exit(EXIT_SUCCESS);
  }

  close(p2c[0]); close(c2p[1]);
  fisier = fopen("in.txt", "r");
  if(fisier == NULL){
    perror("eroare fopen");
    exit(EXIT_FAILURE);
  }

  fscanf(fisier, "%d", &x);
  write(p2c[1], &x, sizeof(int));

  fscanf(fisier, "%d", &x);
  write(p2c[1], &x, sizeof(int));
  close(p2c[1]); 

  wait(0);

  read(c2p[0], &x, sizeof(int));
  close(c2p[0]);

  printf("Suma: %d\n", x);
  
  return 0;
}
