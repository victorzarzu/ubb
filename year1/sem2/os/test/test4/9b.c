#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "9_common.h"

#define OUTPUT_SIZE 1000

int main(int argc, char** argv) {
  
  int fd = open(fifo, O_RDONLY);
  int len;
  
  while(1) {
    if(read(fd, &len, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_SUCCESS);
    }

    if(len < 0) {
      break;
    }
    printf("%d\n", len);

    char* buff = (char *)malloc(sizeof(char) * (len + 1));
    if(buff == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_SUCCESS);
    }

    if(stubborn_read(fd, buff, len, 100) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_SUCCESS);
    }
    printf("%s", buff);
    free(buff);
    fflush(stdout);
  }

  close(fd);

  return 0;
}
