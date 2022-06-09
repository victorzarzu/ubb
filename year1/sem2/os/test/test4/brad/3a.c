#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char** argv) {
  if(argc != 2) { 
    printf("Numar incorect de argumente!\n");
    exit(EXIT_FAILURE);
  }
  
  if(mkfifo("fifo3", 0600) < 0) {
    if(errno != EEXIST) {
      printf("Eroare mkfifo!\n");
      exit(EXIT_FAILURE);
    }
  }

  int a2b[2];
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

    int n, i, x;
    printf("Numar: ");
    scanf("%d", &n);

    if(n <= 0) {
      printf("Numarul trebuie sa fie pozitiv!\n");
      close(a2b[1]);
      exit(EXIT_FAILURE);
    }

    if(write(a2b[1], &n, sizeof(int)) < 0) {
      printf("Eroare write!\n"); 
      close(a2b[1]);
      exit(EXIT_SUCCESS);
    }

    FILE* file = fopen(argv[1], "r");
    if(file == NULL) {
      printf("Eroare fopen!\n");
      close(a2b[1]);
      exit(EXIT_FAILURE);
    }

    for(i = 0;i < n;++i) {
      if(fscanf(file, "%d" , &x) < 0) {
        printf("Eroare fscanf!\n"); 
        close(a2b[1]);
        exit(EXIT_SUCCESS);
      }
      if(write(a2b[1], &x, sizeof(int)) < 0) {
        printf("Eroare write!\n"); 
        close(a2b[1]);
        exit(EXIT_SUCCESS);
      }
    }
    close(a2b[1]);

    fclose(file);
    exit(EXIT_SUCCESS);
  }

  int child_2 = fork();
  if(child_2 < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child_2 == 0) {
    close(a2b[1]);
    
    int n, x, sum = 0, i;
    if(read(a2b[0], &n, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }

    for(i = 0;i < n;++i) {
      if(read(a2b[0], &x, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_FAILURE);
      }
      if(x % 2) {
        sum += x;
      }
    }

    close(a2b[0]);

    int fd = open("fifo3", O_WRONLY);
    if(fd < 0) { 
      printf("Eroare open!\n");
      exit(EXIT_FAILURE);
    }

    if(write(fd, &sum, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_FAILURE);
    }

    close(fd);

    exit(EXIT_SUCCESS);
  }
  wait(0); wait(0);

  if(unlink("fifo3") < 0){
    printf("Eroare unlink!\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
