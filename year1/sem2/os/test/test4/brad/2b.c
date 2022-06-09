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

  int fd = open(argv[1], O_RDONLY);
  if(fd < 0) {
    printf("Eroare open!\n");
    exit(EXIT_FAILURE);
  }

  int a2b[2];
  if(pipe(a2b) < 0){
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

    int cmmmc;
    if(read(fd, &cmmmc, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }

    int nr = 0;
    int d = 1;
    for(d = 1;d / 2 <= cmmmc;++d) {
      if(!(cmmmc % d)) {
        ++nr;
      }
    }

    if(write(a2b[1], &nr, sizeof(int)) < 0){
       printf("Eroare write!\n");
       exit(EXIT_FAILURE);
    }

    for(d = 1;d / 2 <= cmmmc;++d) {
      if(!(cmmmc % d)) {
        if(write(a2b[1], &d, sizeof(int)) < 0){
          printf("Eroare write!\n");
          exit(EXIT_FAILURE);
        }
      }
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

    int nr;
    if(read(a2b[0], &nr, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
    }

    int div, i;
    printf("Divizori: ");
    for(i = 0;i < nr;++i) {
      if(read(a2b[0], &div, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_FAILURE);
      }
      printf("%d ", div);
    }

    close(a2b[0]);
    exit(EXIT_SUCCESS);
  }

  wait(0); wait(0);
  close(fd);

  if(unlink(argv[1]) < 0) {
    printf("Eroare unlink!\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
