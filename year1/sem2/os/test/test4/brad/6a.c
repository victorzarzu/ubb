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

#define SIZE 100

int main(int argc, char** argv) {
  int a2b[2];

  if(mkfifo(fifo, 0600) < 0) {
    if(errno != EEXIST) {
      printf("Eroare mkfifo!\n");
      exit(EXIT_FAILURE);
    }
  }

  if(pipe(a2b) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }

  int child_1 = fork();
  if(child_1 < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child_1 == 0) {
    close(a2b[0]);

    char* filename = (char*)malloc(sizeof(char) * SIZE);
    if(filename == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    printf("Fisier: ");
    scanf("%s", filename);

    int len = 0;
    while(filename[len] != '\0') {
      len++;
    } 

    if(write(a2b[1], &len, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      free(filename);
      exit(EXIT_FAILURE);
    }

    if(stubborn_write(a2b[1], filename, len, 100) < 0) {
      printf("Eroare write!\n");
      free(filename);
      exit(EXIT_FAILURE);
    }

    close(a2b[1]);

    free(filename);
    exit(EXIT_SUCCESS);
  }

  int child_2 = fork();
  if(child_2 < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child_2 == 0) {
    close(a2b[1]);

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

    if(stubborn_read(a2b[0], filename, len, 100) < 0) {
      printf("Eroare read!\n");
      free(filename);
      exit(EXIT_FAILURE);
    }
    close(a2b[0]);

    int fd = open(filename, O_RDONLY);
    if(fd < 0) {
      printf("Eroare open!\n");
      free(filename);
      exit(EXIT_FAILURE);
    }
    free(filename);

    int* freq = (int *)malloc(5 * sizeof(int));
    if(freq == NULL) {
      printf("Eroare malloc!\n");
      close(fd);
      free(filename);
      exit(EXIT_FAILURE);
    }
    memset(freq, 0, sizeof(int) * 5);

    char ch, *vocale = "AEIOU";
    while(read(fd, &ch, sizeof(char)) > 0) {
      char* position = strchr(vocale, ch);
      if(position != NULL) {
        freq[position - vocale]++;
      }
    }
    close(fd);

    fd = open(fifo, O_WRONLY);
    if(fd < 0) {
      printf("Eroare open!\n");
      free(freq);
      exit(EXIT_FAILURE);
    }
    
    if(stubborn_write(fd, freq, sizeof(int) * 5, 100) < 0) {
      printf("Eroare write!\n");
      free(freq);
      exit(EXIT_FAILURE);
    }
    free(freq);

    exit(EXIT_SUCCESS);
  }

  wait(0); wait(0);

  if(unlink(fifo) < 0) {
    printf("Eroare unlink!\n");
    exit(EXIT_FAILURE);
  }

  return 0;
} 
