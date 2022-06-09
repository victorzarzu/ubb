#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
  int p2c[2], sum;
  
  pipe(p2c);

  if(fork() == 0){
    close(p2c[0]);

    int n, x, i, j;
    FILE* fisier;
    fisier = fopen(argv[1], "r");
    if(fisier == NULL){
      exit(1);
    }

    fscanf(fisier, "%d", &n);
    sum = 0;
    for(i = 0;i < n;++i){
      for(j = 0;j < n;++j){
        fscanf(fisier, "%d", &x);
        if(i == j){
          sum += x;
        }
      }
    }
    write(p2c[1], &sum, sizeof(int));

    fclose(fisier);
    exit(0);
  }

  close(p2c[1]);

  wait(0);

  read(p2c[0], &sum, sizeof(int));
  printf("Sum: %d", sum);
  close(p2c[0]);

  return 0;
}
