#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv){
  int a2b, b2a, sum, x;

  a2b = open("a2b", O_RDONLY);
  if(a2b == -1){
    perror("eroare open");
    exit(EXIT_FAILURE);
  }

  b2a = open("b2a", O_WRONLY);
  if(b2a == -1){
    perror("eroare open");
    exit(EXIT_FAILURE);
  }

  read(a2b, &sum, sizeof(int));
  read(a2b, &x, sizeof(int));
  close(a2b);

  sum += x;
  write(b2a, &sum, sizeof(int));
  close(b2a);

  return 0;

}
