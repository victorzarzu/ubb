#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char** argv) {
  int fd;
  char ch;
  if((fd = open("fifo4", O_RDONLY)) < 0) {
    printf("Eroare open!\n");
    exit(EXIT_FAILURE);
  }

  if(read(fd, &ch, sizeof(char)) < 0) {
    printf("Eroare read!\n");
    exit(EXIT_FAILURE);
  }
  close(fd);
  printf("Codul ASCII: %hhd\n", ch);

  return 0;
}
