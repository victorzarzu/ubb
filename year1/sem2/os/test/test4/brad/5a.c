#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar incorect de argumente!\n");
    exit(EXIT_FAILURE);
  } 

  if(mkfifo(argv[1], 0600) < 0) {
    if(errno != EEXIST) {
      printf("Eroare mkfifo!\n");
      exit(EXIT_FAILURE);
    }
  }

  int n;
  printf("Numar: ");
  scanf("%d", &n);

  int fd = open(argv[1], O_WRONLY);
  if(fd < 0) {
    printf("Eroare open!\n");
    exit(EXIT_FAILURE);
  }

  int d;
  for(d = 1;d / 2 <= n;++d) {
    if(!(n % d)) {
      if(write(fd, &d, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  close(fd);
  
  return 0;
}
