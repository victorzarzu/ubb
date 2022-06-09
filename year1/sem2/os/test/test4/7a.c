#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "7_fifo.h"

int main(int argc, char** argv) {
  if(mkfifo(fifo1, 0600) < 0) {
    if(errno != EEXIST) {
      printf("Eroare mkfifo\n");
      exit(EXIT_FAILURE);
    }
  }
  if(mkfifo(fifo2, 0600) < 0) {
    if(errno != EEXIST) {
      printf("Eroare mkfifo\n");
      exit(EXIT_FAILURE);
    }
  }
  srand((unsigned int)getpid());

  int f1 = open(fifo1, O_WRONLY);
  int f2 = open(fifo2, O_RDONLY);

  int number;
  while(1) {
    number = rand() % 10 + 1;
    if(write(f1, &number, sizeof(int)) < 0) {
      printf("Eroare write\n");
      exit(EXIT_FAILURE);
    }

    if(number == 10) {
      break;
    }

    if(read(f2, &number, sizeof(int)) < 0) {
      printf("Eroare read\n");
      exit(EXIT_FAILURE);
    }
    printf("A: %d\n", number);

    if(number == 10) {
      break;
    }
  }

  close(f1);
  close(f2);
  unlink(fifo1);
  unlink(fifo2);

  return 0;
}
