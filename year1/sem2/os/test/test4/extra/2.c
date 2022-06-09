#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include "2_common.h"

#define BUFFER_LEN 128

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar incorect de argumente!\n");
    exit(EXIT_FAILURE);
  }

  int a2b[2], b2a[2];
  if(pipe(a2b) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }
  if(pipe(b2a) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }

  int child = fork();
  if(child < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child == 0) {
    close(a2b[1]); close(b2a[0]);
    int len;
    if(read(a2b[0], &len, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }
    
    char* filename = (char*)malloc(sizeof(char) * (len + 1));
    if(filename == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    if(stubborn_read(a2b[0], filename, sizeof(char) * (len + 1), 100) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }
    close(a2b[0]);

    int fd = open(filename, O_RDONLY);
    if(fd < 0) {
      printf("Eroare open!\n");
      exit(EXIT_FAILURE);
    }

    free(filename);
    char* buf = (char*)malloc(sizeof(char) * BUFFER_LEN);
    if(buf == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    int k;
    while((k = stubborn_read(fd, buf, sizeof(char) * BUFFER_LEN, 100)) > 0) {
      int pct = 0, i;
      for(i = 0;i < k;++i) {
        if(buf[i] == '.') {
          pct = 1;
        }   
        else if(pct && buf[i] >= 'a' && buf[i] <= 'z') {
          buf[i] += 'A' - 'a';
        }
        else if(pct && !isspace(buf[i])) {
          pct = 0;
        }
      }
      if(stubborn_write(b2a[1], buf, k, 100) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_FAILURE);
      }
    }


    close(b2a[1]);
    exit(EXIT_SUCCESS);
  }
  
  close(a2b[0]); close(b2a[1]);
  int len = strlen(argv[1]);

  if(write(a2b[1], &len, sizeof(int)) < 0) {
    printf("Eroare read!\n");
    exit(EXIT_FAILURE);
  }

  if(stubborn_write(a2b[1], argv[1], sizeof(char) * (len + 1), 100) < 0) {
    printf("Eroare read!\n");
    exit(EXIT_FAILURE);
  }

  close(a2b[1]);

  wait(0);

  char* buf = (char*)malloc(sizeof(char) * BUFFER_LEN);
  if(buf == NULL) {
    printf("Eroare malloc!\n");
    exit(EXIT_FAILURE);
  }

  while(stubborn_read(b2a[0], buf, BUFFER_LEN, 100) > 0) {
    printf("%s", buf);
  }

  printf("da");

  close(b2a[0]);
  free(buf);


  return 0;
}
