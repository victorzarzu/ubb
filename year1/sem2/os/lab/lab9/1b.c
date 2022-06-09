#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv) {
  srand((unsigned int)getpid());

  int result = mkfifo("1_fifo", 0600);
  /*if(result < 0) {
    perror("eroare mkfifo");
    exit(EXIT_FAILURE);
  }*/

  result = mkfifo("2_fifo", 0600);
  /*if(result < 0) {
    perror("eroare mkfifo");
    exit(EXIT_FAILURE);
  }*/

  int fd1 = open("1_fifo", O_RDONLY);
  int fd2 = open("2_fifo", O_WRONLY);

  int random;
  while(1) {
    if(read(fd1, &random, sizeof(int)) < 0) {
      perror("eroare read");
      exit(EXIT_FAILURE);
    }
    printf("Received in B: %d\n", random);

    if(random == 10) {
      break;
    }

    random = rand() % 10 + 1;

    if(write(fd2, &random, sizeof(int)) < 0) {
      perror("eroare write");
      exit(EXIT_FAILURE);
    }

    if(random == 10){
      break;
    }

  }

  close(fd1);
  close(fd2);

  return 0; 
}
