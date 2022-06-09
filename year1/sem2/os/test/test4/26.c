#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include "26_common.h"

#define SIZE 256 

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar incorect de argumente!\n");
    exit(EXIT_FAILURE);
  }

  int a2b[2], b2a[2];
  if(pipe(a2b) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_SUCCESS);
  }
  if(pipe(b2a) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_SUCCESS);
  }

  int child = fork();
  if(child < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_SUCCESS);
  }
  else if(child == 0) {
    close(a2b[1]); close(b2a[0]);
    
    int len;
    if(read(a2b[0], &len, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }

    char* filename = (char *)malloc((len + 1) * sizeof(char));
    if(filename == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }
    if(stubborn_read(a2b[0], filename, len, 100) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }
    filename[len] = '\0';
    close(a2b[0]);

    int fd = open(filename, O_RDONLY);
    if(fd < 0) {
      printf("Eroare open!\n");
      exit(EXIT_FAILURE);
    }
    free(filename);

    char* buff = (char *)malloc(sizeof(char) * SIZE);
    if(buff == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    while((len = stubborn_read(fd, buff, SIZE, 100)) > 0) {
      int i, pnct = 0;
      for(i = 0;i < len;++i) {
        if(buff[i] == '.') {
          pnct = 1;
        }
        else if(pnct == 1 && buff[i] >= 'a' && buff[i] <= 'z') {
          buff[i] += 'A' - 'a';
          pnct = 0;
        }
        else if(!isspace(buff[i])) {
          pnct = 0;
        }
      }

      if(stubborn_write(b2a[1], buff, len, 100) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_FAILURE);
      }
    }

    free(buff);
    close(b2a[1]);
    exit(EXIT_SUCCESS);
  }

  close(a2b[0]); close(b2a[1]);
  int len = strlen(argv[1]);
  if(write(a2b[1], &len, sizeof(int)) < 0) {
    printf("Eroare write!\n");
    exit(EXIT_FAILURE);
  }
  if(stubborn_write(a2b[1], argv[1], len, 100) < 0) {
    printf("Eroare write!\n");
    exit(EXIT_FAILURE);
  }
  close(a2b[1]);

  char* buff = (char *)malloc(sizeof(char) * (SIZE + 1));
  if(buff == NULL) {
    printf("Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  while((len = stubborn_read(b2a[0], buff, SIZE, 100)) > 0) {
    buff[len] = '\0'; 
    printf("%s", buff);
  }

  free(buff);
  close(b2a[0]);
  wait(0);

  return 0;
}
