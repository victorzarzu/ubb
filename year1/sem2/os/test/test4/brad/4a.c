#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar de argumente incorect!\n");
    exit(EXIT_FAILURE);
  }
  if(mkfifo("fifo4", 0600) < 0) {
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

    int fd, n;
    if((fd = open(argv[1], O_RDONLY)) < 0) {
      printf("Eroare open!\n");
      exit(EXIT_FAILURE);
    }

    printf("Numar: ");
    if(scanf("%d", &n) < 0) {
      printf("Eroare scanf!\n");
      exit(EXIT_FAILURE);
    }

    if(lseek(fd, n - 1, SEEK_SET) < 0) {
      printf("Eroare lseek!\n");
      exit(EXIT_FAILURE);
    } 

    char ch;
    if(read(fd, &ch, sizeof(char)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }
    if(ch == 0) {
      printf("Numarul dat este prea mare!\n");
      exit(EXIT_FAILURE);
    }

    if(write(a2b[1], &ch, sizeof(char)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_FAILURE);
    }
    
    close(a2b[1]);
    exit(EXIT_SUCCESS);
  }

  
  int child_2 = fork();
  if(child_2 < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child_2 == 0) {
    close(a2b[1]);
    
    char ch;
    if(read(a2b[0], &ch, sizeof(char)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }
    close(a2b[0]);

    if(ch >= '0' && ch <= '9') {
      printf("Caracterul este un numar!\n");
    }
    else if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
      printf("Caracterul este o litera!\n");
    }
    else {
      printf("Caracterul este ceva!\n");
    }

    int fd;
    if((fd = open("fifo4", O_WRONLY)) < 0) {
      printf("Eroare open!\n");
      exit(EXIT_FAILURE);
    }

    if(write(fd, &ch, sizeof(char)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }
    close(fd);
    
    exit(EXIT_SUCCESS);
  }
  
  wait(0); wait(0);

  if(unlink("fifo4") < 0) {
    printf("Eroare unlink!\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
