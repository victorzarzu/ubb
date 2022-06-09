#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

int stubborn_read(int fd, void* buf, int count, int trials) {
  int k, total = 0, n = 0;

  while(total < count && n < trials && (k = read(fd, buf + total, count - total)) > 0) {
    total += k;
    n++;
  }

  return k < 0 ? k : total;
}

int stubborn_write(int fd, void* buf, int count, int trials) {
  int k, total = 0, n = 0;

  while(total < count && n < trials && (k = write(fd, buf + total, count - total)) > 0) {
    total += k;
    n++;
  }

  return k < 0 ? k : total;
}

int main(int argc, char** argv) {
  if(argc != 2) {
    fprintf(stderr, "%s\n", "eroare argumente");
    exit(EXIT_FAILURE);
  }

  int p2c[2], c2p[2]; 
  int result;

  result = pipe(p2c);
  if(result == -1){
    perror("eroare pipe");
    exit(EXIT_FAILURE);
  }
  result = pipe(c2p);
  if(result == -1){
    perror("eroare pipe");
    exit(EXIT_FAILURE);
  }

  
  result = fork();

  if(result == -1){
    perror("eroare fork");
    exit(EXIT_FAILURE);
  }
  else if(result == 0){
    close(p2c[1]); close(c2p[0]);

    char* buf = (char *)malloc(sizeof(char) * 101);
    if(buf == NULL) {
      perror("eroare malloc");
      exit(EXIT_FAILURE);
    }
  
    int len = stubborn_read(p2c[0], buf, 100, 3);
    close(p2c[0]);
    if(len < 0) {
      perror("eroare read");
      close(c2p[1]); close(p2c[0]);
      exit(EXIT_SUCCESS);
    } 
  
    buf[len] = 0;
    int fd = open(buf, O_RDONLY);
    if(fd < 0){
      perror("eroare open");
      exit(EXIT_FAILURE);
    }

    int length;
    while((length = stubborn_read(fd, buf, 100, 3)) > 0) {
      int punct = 0 ,i;
      for(i = 0;i < length;++i) {
        if(buf[i] == '.') {
          punct = 1;
        }
        else if(punct == 1 && buf[i] >= 'A' && buf[i] <= 'Z') {
          punct = 0;
          buf[i] += 'a' - 'A';
        }     
        else if(punct == 1 && !isspace(buf[i])){
           punct = 0; 
        }
      }

      if(stubborn_write(c2p[1], buf, 100, 3) < 0){
        perror("eroare write");
        exit(EXIT_FAILURE);
      }
    }


    close(c2p[1]);

    free(buf);
    close(fd);
    exit(EXIT_SUCCESS);
  }

  close(p2c[0]); close(c2p[1]);

  if(stubborn_write(p2c[1], argv[1], 100, 3) < 0) {
    perror("eroare write");
    exit(EXIT_FAILURE);
  }

  close(p2c[1]);
  
  int length;
  char* buf = (char *)malloc(sizeof(char) * 101);
    if(buf == NULL) {
      perror("eroare malloc");
      exit(EXIT_FAILURE);
    }
  while((length = stubborn_read(c2p[0], buf, 100, 3)) > 0) {
     buf[length] = 0;
     printf("%s", buf);
  }

  close(c2p[0]);
  wait(0);
  free(buf);

  return 0;
}
