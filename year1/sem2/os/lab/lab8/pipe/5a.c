#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv){
  int a2b, b2a, x;
  FILE *fisier;

  a2b = open("a2b", O_WRONLY);
  if(a2b == -1){
    perror("eroare open");
    exit(EXIT_FAILURE);
  }

  b2a = open("b2a", O_RDONLY);
  if(b2a == -1){
    perror("eroare open");
    exit(EXIT_FAILURE);
  }

  fisier = fopen("in.txt", "r");
  if(fisier == NULL){
    perror("eroare fopen");
    exit(EXIT_FAILURE);

  }

  fscanf(fisier, "%d", &x);
  write(a2b, &x, sizeof(int));
  fscanf(fisier, "%d", &x);
  write(a2b, &x, sizeof(int));

  close(a2b);
  fclose(fisier);

  read(b2a, &x, sizeof(int));
  close(b2a);

  printf("Suma: %d\n", x);
  
  return 0;
}
