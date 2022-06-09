#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "6_common.h"


int main(int argc, char** argv) {
  
  int fd = open(fifo, O_RDONLY);
  if(fd < 0) {
    printf("Eroare open!\n");
    exit(EXIT_FAILURE);
  }

  int* freq = (int *)malloc(sizeof(int) * 5);
  if(freq == NULL) {
    printf("Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  if(stubborn_read(fd, freq, sizeof(int) * 5, 100) < 0) {
    printf("Eroare read!\n");
    free(freq);
    close(fd);
    exit(EXIT_FAILURE);
  }
  close(fd);

  int i;
  for(i = 0;i < 5;++i) {
    printf("%d ", freq[i]);
  }

  free(freq);

  return 0;
}
