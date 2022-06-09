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
  srand((unsigned int)getpid());
  int f1 = open(fifo1, O_RDONLY);
  int f2 = open(fifo2, O_WRONLY);

  int number;
  while(1) {
    if(read(f1, &number, sizeof(int)) < 0) {
      printf("Eroare read\n");
      exit(EXIT_FAILURE);
    }
    printf("B: %d\n", number);

    if(number == 10) {
      break;
    }

    number = rand() % 10 + 1;
    if(write(f2, &number, sizeof(int)) < 0) {
      printf("Eroare write\n");
      exit(EXIT_FAILURE);
    }

    if(number == 10) {
      break;
    }

    
  }

  close(f1);
  close(f2);
  return 0;
}
