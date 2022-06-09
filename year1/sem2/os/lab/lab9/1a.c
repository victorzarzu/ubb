#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv) {
  srand((unsigned int)getpid());

  int result = mkfifo("1_fifo", 0600);
  if(result < 0 && errno != EEXIST){
    perror("eroare mkfifo");
    exit(EXIT_FAILURE);
  }

  result = mkfifo("2_fifo", 0600);
  if(result < 0 && errno != EEXIST){
    perror("eroare mkfifo");
    exit(EXIT_FAILURE);
  }

  int fd1 = open("1_fifo", O_WRONLY);
  int fd2 = open("2_fifo", O_RDONLY);

  int random;
  while(1) {
    random = rand() % 10 + 1;

    if(write(fd1, &random, sizeof(int)) < 0) {
      perror("eroare write");
      break;
    }

    if(random == 10){
      break;
    }

    if(read(fd2, &random, sizeof(int)) < 0) {
      perror("eroare read");
      break;
    }
    printf("Received in A: %d\n", random);

    if(random == 10) {
      break;
    }
  }

  close(fd1);
  close(fd2);
  if(0 > unlink("1_fifo")) {
    perror("eroare unlink");
  }

  if(0 > unlink("2_fifo")) {
    perror("eroare unlink");
  }
  return 0; 
}
