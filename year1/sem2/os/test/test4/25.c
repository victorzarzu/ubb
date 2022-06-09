#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int random_number(int a, int b) {
  return rand() % (b - a) + a;
}

int main(int argc, char** argv) {
  int a2d[2], b2d[2], d2b[2], c2d[2], d2c[2];
  if(pipe(a2d) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }
  if(pipe(b2d) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }
  if(pipe(d2b) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }
  if(pipe(c2d) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }
  if(pipe(d2c) < 0) {
    printf("Eroare pipe!\n");
    exit(EXIT_FAILURE);
  }

  int child_b = fork();
  if(child_b < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child_b == 0) {
    close(a2d[0]); close(a2d[1]); close(b2d[0]);
    close(c2d[0]); close(c2d[1]); close(d2b[1]);
    close(d2c[0]); close(d2c[1]);
    srand((unsigned int)getpid());
  
    int flag = 1, n;
    while(1) {
      if(read(d2b[0], &flag, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_SUCCESS);
      }
      if(!flag) {
        break;
      }

      n = random_number(1, 200);

      if(write(b2d[1], &n, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_SUCCESS);
      }

    }
    close(b2d[1]); close(d2b[0]);
    exit(EXIT_SUCCESS);
  }
  
  int child_c = fork();
  if(child_c < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child_c == 0) {
    close(a2d[0]); close(a2d[1]); close(c2d[0]);
    close(b2d[0]); close(b2d[1]); close(d2c[1]);
    close(d2b[0]); close(d2b[1]);
    srand((unsigned int)getpid());
  
    int flag = 1, n;
    while(1) {
      if(read(d2c[0], &flag, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_SUCCESS);
      }
      if(!flag) {
        break;
      }

      n = random_number(1, 200);

      if(write(c2d[1], &n, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_SUCCESS);
      }
    }
    close(c2d[1]); close(d2c[0]);
    exit(EXIT_SUCCESS);
  }

  int child_d = fork();
  if(child_d < 0) {
    printf("Eroare fork!\n");
    exit(EXIT_FAILURE);
  }
  else if(child_d == 0) {
    close(a2d[1]); close(b2d[1]); close(c2d[1]);
    close(d2b[0]); close(d2c[0]);

    int number_a;
    if(read(a2d[0], &number_a, sizeof(int)) < 0) {
      printf("Eroare read!\n");
      exit(EXIT_SUCCESS);
    }
    close(a2d[0]);
    printf("Number from A: %d\n", number_a);

    int flag = 1;
    if(write(d2b[1], &flag, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_SUCCESS);
    }
    if(write(d2c[1], &flag, sizeof(int)) < 0) {
      printf("Eroare write!\n");
      exit(EXIT_SUCCESS);
    }
    
    int number_b, number_c;
    while(flag) {
      if(read(b2d[0], &number_b, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_SUCCESS);
      }
      printf("Number from B: %d\n", number_b);
      if(read(c2d[0], &number_c, sizeof(int)) < 0) {
        printf("Eroare read!\n");
        exit(EXIT_SUCCESS);
      }
      printf("Number from C: %d\n", number_c);

      if(abs(number_b - number_c) <= number_a) {
        flag = 0;
      }

      if(write(d2b[1], &flag, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_SUCCESS);
      }
      if(write(d2c[1], &flag, sizeof(int)) < 0) {
        printf("Eroare write!\n");
        exit(EXIT_SUCCESS);
      }
    }

    close(b2d[0]); close(c2d[0]); close(d2b[1]); close(d2c[1]);
    exit(EXIT_SUCCESS);
  }

  close(a2d[0]); close(b2d[0]); close(b2d[1]);
  close(c2d[0]); close(c2d[1]); close(d2b[0]);
  close(d2b[1]); close(c2d[1]); close(c2d[0]);
  srand((unsigned int)getpid());

  int n = random_number(10, 20);
  if(write(a2d[1], &n, sizeof(int)) < 0) {
    printf("Eroare write!\n");
    exit(EXIT_SUCCESS);
  }

  close(a2d[1]);
  wait(0);
  wait(0);
  wait(0);

  return 0;
}
