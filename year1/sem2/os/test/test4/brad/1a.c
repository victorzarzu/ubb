#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define SIZE 100

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar de argumente incorect!\n");
    exit(EXIT_FAILURE);
  }
  if(mkfifo(argv[1], 0600) < 0) {
    if(errno == EEXIST) {
      printf("Eroare mkfifo!\n");
      exit(EXIT_FAILURE);
    }
  }

  char* filename = (char *)malloc(sizeof(char) * SIZE);
  if(scanf("%s", filename) < 0) {
    printf("Eroare scanf!\n");
    exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_WRONLY);
  if(fd < 0) {
    printf("Eroare open!\n");
    exit(EXIT_FAILURE);
  }

  FILE* file = fopen(filename, "r");
  if(file == NULL) {
    printf("Eroare fopen!\n");
    exit(EXIT_FAILURE);
  }
  free(filename);

  char ch;
  while(fread(&ch, 1, 1, file) > 0) {
    if(ch >= '0' && ch <= '9') {
      if(write(fd, &ch, sizeof(char)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  fclose(file);
  close(fd);

  return 0;
}
