#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

int cmmmc(int a, int b) {
  if(!a || !b) {
    return 0;
  }

  int r, prod = a * b;
  while(b) {
    r = a % b;
    a = b;
    b = r;
  }

  return prod / a;
}

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar de argumente incorect!\n");
    exit(EXIT_FAILURE);
  }

  if(mkfifo(argv[1], 0600) < 0) {
    if(errno != EEXIST) {
      printf("Eroare mkfifo!\n");
      exit(EXIT_FAILURE);
    }
  }

  int fd = open(argv[1], O_WRONLY);
  if(fd < 0) {
      printf("Eroare open!\n");
      exit(EXIT_FAILURE);
  }

  int x, y;
  printf("Numare: ");
  scanf("%d %d", &x, &y);
  x = cmmmc(x, y);
  printf("%d\n", x);

  if(write(fd, &x, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_FAILURE);
  }

  close(fd);

  return 0;
}
