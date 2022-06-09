#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char** argv) {
  int sum;
  int fd = open("fifo3", O_RDONLY);
  if(fd < 0) { 
    printf("Eroare open!\n");
    exit(EXIT_FAILURE);
  }

  if(read(fd, &sum, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_FAILURE);
  }

  printf("Sum: %d\n", sum);
  close(fd);

  return 0;
}
