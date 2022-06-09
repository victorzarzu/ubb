#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char** argv) {
  int a2b[2], b2c[2], c2a[2], result;

  result = pipe(a2b);
  if(result < 0) {
    perror("eroare pipe");
    exit(EXIT_FAILURE);
  }

  result = pipe(b2c);
  if(result < 0) {
    perror("eroare pipe");
    exit(EXIT_FAILURE);
  }
  
  result = pipe(c2a);
  if(result < 0) {
    perror("eroare pipe");
    exit(EXIT_FAILURE);
  }
  
  srand((unsigned int)getpid());

  result = fork();
  if(result == -1) {
    perror("eroare fork");
    exit(EXIT_FAILURE);
  }
  else if(result == 0) {
    close(a2b[1]); close(b2c[0]); close(c2a[0]); close(c2a[1]); 

    int n;
    if(read(a2b[0], &n, sizeof(int)) < 0) {
      perror("eroare read");
      exit(EXIT_FAILURE);
    }

    int* array = (int *)malloc(n * sizeof(int));
    if(array == NULL) {
      perror("eroare malloc");
      exit(EXIT_FAILURE);
    }

    int i;
    for(i = 0;i < n;++i) {
      if(read(a2b[0], &n, sizeof(int)) < 0) {
        perror("eroare read");
        exit(EXIT_FAILURE);
      }
    }
  }

  result = fork();
  if(result == -1) {
    perror("eroare fork");
    exit(EXIT_FAILURE);
  }
  else if(result == 0) {
      
  }

  close(a2b[0]); close(b2c[0]); close(b2c[1]); close(c2a[1]);

  int n;
  scanf("%d", &n);
  if(n <= 0) {
    perror("numar prea mic");
    exit(EXIT_FAILURE);
  }

  if(write(a2b[1], &n, sizeof(int)) < 0) {
    perror("eroare write");
    exit(EXIT_FAILURE);
  }

  int* array = (int *)malloc(n * sizeof(int));
  if(array == NULL) {
    perror("eroare malloc");
    exit(EXIT_FAILURE);
  }

  int i;
  for(i = 0;i < n;++i) {
    scanf("%d", &array[i]);  
  }

  for(i = 0;i < n;++i) {
    if(write(a2b[1], &n, sizeof(int)) < 0) {
      perror("eroare write");
      exit(EXIT_FAILURE);
    } 
  }
  close(a2b[1]);
  free(array);

  wait(0);
  if(read(c2a[0], &n, sizeof(int)) < 0) {
      perror("eroare read");
      exit(EXIT_FAILURE);
  }

  close(c2a[0]);

  return 0;
}
