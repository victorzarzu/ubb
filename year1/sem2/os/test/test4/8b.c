#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "8_common.h"

int main(int argc, char** argv) {
  int fd1 = open(fifo1, O_RDONLY);
  int fd2 = open(fifo2, O_WRONLY);

  int n;

  if(read(fd1, &n, sizeof(int)) < 0) {
    printf("Eroare read!\n");
    exit(EXIT_SUCCESS);
  }
  printf("%d\n", n);

  int i, len;
  for(i = 1;i < n;++i) {
    if(read(fd1, &len, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_SUCCESS);
    }

    char *buff = (char*)malloc(sizeof(char) * len);
    if(buff == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_SUCCESS);
    }

    if(stubborn_read(fd1, buff, len, 100) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_SUCCESS);
    }

    int j;
    for(j = 0;j < len;++j) {
      if(buff[j] >= 'a' && buff[j] <= 'z') {
        buff[j] += 'A' - 'a';
      }
    }

    if(stubborn_write(fd2, buff, len, 100) < 0) {
      printf("Eroare writeee!\n");
      exit(EXIT_SUCCESS);
    }
    free(buff);
  }

  close(fd1);
  close(fd2);
  return 0;
}
