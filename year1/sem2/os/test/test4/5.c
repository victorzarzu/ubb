#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

int n;

int contains_7(int x) {
  if(!(x % 7)) {
    return 1;
  }
  while(x) {
    int cif = x % 10;
    if(cif == 7) {
      return 1;
    }
    x /= 10;
  }
  return 0;
}

void create(int number, int p[][2]) {
  if(number < n - 1) {
    int result = fork();
    if(result < 0) {
      printf("Eroare fork\n");
      return;
    }
    else if(result == 0) {
      create(number + 1, p);
      return;
    }
  }
  
  int read_index = number % n;
  int write_index = (number + 1) % n;

  int i;
  for(i = 0;i < n;++i) {
    if(i == read_index) {
      close(p[i][1]);
    }
    else if(i == write_index) {
      close(p[i][0]);
    }
    else {
      close(p[i][0]); close(p[i][1]);
    }
  }

  int nr = 1;
  if(number == 0) {
    if(write(p[write_index][1], &nr, sizeof(int)) < 0) {
      printf("Eroare write\n");
      exit(EXIT_FAILURE);
    }
  }

  while(nr >= 1) {
    if(read(p[read_index][0], &nr, sizeof(int)) < 0) {
      printf("Eroare read\n");
      break;
    } 

    if(nr == 0) {
      if(write(p[write_index][1], &nr, sizeof(int)) < 0) {
        printf("Eroare write\n");
      }
      break;
    } 

    nr++;
    if(contains_7(nr)) {
      int rnd = rand() % 3;

      if(rnd == 0) {
        nr = 0;    
      }
      else {
        printf("boltz\n");
      }
    }
    else {
      printf("%d\n", nr);
    }
    
    if(write(p[write_index][1], &nr, sizeof(int)) < 0) {
        printf("Eroare write\n");
        exit(EXIT_FAILURE);
    }
  }

  wait(0);
  close(p[read_index][0]); close(p[write_index][1]);
}

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("Numar de argumente incorect\n");
    exit(EXIT_FAILURE);
  }

  if(sscanf(argv[1], "%d", &n) == EOF) {
    printf("Argumentul trebuie sa fie un numar\n");
    exit(EXIT_FAILURE);
  }
  if(n <= 1) {
    printf("Argumentul trebuie sa fie un numar cel putin egal cu 2\n");
    exit(EXIT_FAILURE);
  }
  int p[n][2], i;
  for(i = 0;i < n;++i) {
    if(pipe(p[i]) < 0) {
      printf("Eroare pipe\n");
      exit(EXIT_FAILURE);
    }
  }

 // srand((unsigned int)time(NULL));
  create(0, p);

  return 0;
}
