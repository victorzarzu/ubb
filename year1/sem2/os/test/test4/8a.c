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
  if(argc == 1) {
    printf("Cel putin un argument!\n");
    exit(EXIT_SUCCESS);
  }

  if(mkfifo(fifo1, 0600) < 0) {
    if(errno != EEXIST) {
      printf("Eroare mkfifo!\n");
      exit(EXIT_SUCCESS);
    }
  }
  if(mkfifo(fifo2, 0600) < 0) {
    if(errno != EEXIST) {
      printf("Eroare mkfifo!\n");
      exit(EXIT_SUCCESS);
    }
  }

  int fd1 = open(fifo1, O_WRONLY);
  int fd2 = open(fifo2, O_RDONLY);

  if(write(fd1, &argc, sizeof(int)) < 0) {
    printf("Eroare write!\n");
    exit(EXIT_SUCCESS);
  }

  int i, size = 0, len;
  for(i = 1;i < argc;++i) {
    size += strlen(argv[i]) + 1;
  }
  char* result = (char *)malloc(sizeof(char) * (size + 1));
  if(result == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_SUCCESS);
  }

  for(i = 1;i < argc;++i) {
    len = strlen(argv[i]); 
    if(write(fd1, &len, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_SUCCESS);
    }
    
    if(stubborn_write(fd1, argv[i], strlen(argv[i]), 100) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_SUCCESS);
    }
    char* buff = (char*)malloc(sizeof(char) * len);
    if(buff == NULL) {
        printf("Eroare malloc!\n");
        exit(EXIT_SUCCESS);
    }

    if(stubborn_read(fd2, buff, len, 100) < 0) {
      printf("Eroare readddd!\n");
      exit(EXIT_SUCCESS);
    }

    strcat(result, buff);
    strcat(result, " ");
    free(buff);
  }

  result[size] = '\0';

  printf("%s", result);

  free(result);

  close(fd1);
  close(fd2);
  if(unlink(fifo1) < 0) {
      printf("Eroare unlink!\n");
      exit(EXIT_SUCCESS);
  }
  if(unlink(fifo2) < 0) {
      printf("Eroare unlink!\n");
      exit(EXIT_SUCCESS);
  }
  return 0;
}
