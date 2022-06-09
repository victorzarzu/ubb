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
  if(mkfifo(fifo1, 0600) < 0) {
    if(errno != EEXIST) {
      printf("Eroare mkfifo!\n");
      exit(EXIT_SUCCESS);
    }
  }

  int fd1 = open(fifo1, O_WRONLY);
  int fd2 = open(fifo2, O_RDONLY);

  if(write(fd1, &n, sizeof(int)) < 0) {
    printf("Eroare write!\n");
    exit(EXIT_SUCCESS);
  }

  int i, size = 0;
  for(i = 1;i < argc;++i) {
    if(stubborn_write(fd1, argv[i], strlen(argv[i]), 100) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_SUCCESS);
    }
    size += strlen(argv[i]) + 1;
  }

  char* result = (char *)malloc(sizeof(char) * size);
  if(result == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_SUCCESS);
  }
  
  size = 0;
  for(i = 1;i < argc;++i) { 
    if(stubborn_read(fd2, result + size, strlen(argv[i]), 100) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_SUCCESS);
    }
    result[size] = ' ';
    size++;
  }
  result[size] = '\0';

  printf("%s", result);

  free(result);

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
