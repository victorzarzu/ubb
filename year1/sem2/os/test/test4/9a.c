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
int fd;

void stop() {
  close(fd);
  if(unlink(fifo) < 0) {
     printf("Eroare mkfifo!\n");
     exit(EXIT_FAILURE);
  }
  int len = -1;
  if(write(fd, &len, sizeof(int)) < 0) {
     printf("Eroare write!\n");
     exit(EXIT_FAILURE);
  }
}

int main(int argc, char** argv) {
  if(mkfifo(fifo, 0600) < 0) {
    if(errno != EEXIST) {
      printf("Eroare mkfifo!\n");
      exit(EXIT_FAILURE);
    }
  }

  signal(SIGINT, stop);

  fd = open(fifo, O_WRONLY);
  char* cmd = (char *)malloc(sizeof(char) * OUTPUT_SIZE);
  if(cmd == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
  
  while(1) {
    int len;
    if((len = read(0, cmd, (OUTPUT_SIZE - 1) * sizeof(char))) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }
    cmd[len - 1] = 0;

    if(strcmp(cmd, "stop") == 0) {
      len = -1;
      if(write(fd, &len, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_FAILURE);
      }
      break;
    }

    FILE* f_cmd = popen(cmd, "r");
    if(f_cmd == NULL) {
      printf("Eroare popen!\n");
      exit(EXIT_FAILURE);
    }

    char* buff = (char *)malloc(sizeof(char) * OUTPUT_SIZE);
    if(buff == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    while(fread(buff, 1, OUTPUT_SIZE - 1, f_cmd) > 0) {
      len = strlen(buff);
      if(write(fd, &len, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_FAILURE);
      }

      if(stubborn_write(fd, buff, len, 100) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_FAILURE);
      }
    }
    
    pclose(f_cmd);
    free(buff);
    memset(cmd, 0, OUTPUT_SIZE * sizeof(char));
  }

  free(cmd);
  close(fd);
  if(unlink(fifo) < 0) {
     printf("Eroare mkfifo!\n");
     exit(EXIT_FAILURE);
  }

  return 0;
}
