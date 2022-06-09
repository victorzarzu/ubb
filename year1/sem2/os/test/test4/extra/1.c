#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define INITIAL_LEN 100
#define absolut(x) (x < 0 ? -x : x)

int cmmdc(int a, int b) {
  if(!a || !b) {
    return 0;
  }

  int r;
  while(b) {
    r = a % b;
    a = b;
    b = r;
  }

  return a;
}

int main(int argc, char** argv) {
  int n, a2b[2], b2a[2];

  if(pipe(a2b) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }

  if(pipe(b2a) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }

  int child = fork();
  if(child < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child == 0) {
    close(a2b[1]); close(b2a[0]);

    int len = 0;
    int* array = (int *)malloc(sizeof(int) * INITIAL_LEN);
    if(array == NULL) {
      printf("Eroare malloc!\n");
      exit(EXIT_FAILURE);
    }

    int result = 0;
    while(1) {
      if(read(a2b[0], &n, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_FAILURE);
      }

      if(n == 0) {
        break;
      }
      array[len++] = n;
      if(!result) {
        result = n;
      }
      else {
        result = cmmdc(absolut(n), absolut(result));
      }

      printf("GCD for numbers: ");
      int i;
      for(i = 0;i < len;++i) {
        printf("%d ", array[i]);
      }
      printf("is %d\n", result);
    }
    close(a2b[0]);
    free(array);

    if(write(b2a[1], &result, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_FAILURE);
    }
    close(b2a[1]);
    exit(EXIT_SUCCESS);
  }
  
  close(a2b[0]); close(b2a[1]);
  while(1) {
    scanf("%d", &n);

    if(write(a2b[1], &n, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_FAILURE);
    }
    if(!n) {
      break;
    }
  }
  close(a2b[1]);

  wait(0);
  if(read(b2a[0], &n, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_FAILURE);
  }
  close(b2a[0]);

  printf("GCD of all numbers is: %d\n", n);

  return 0;
}
