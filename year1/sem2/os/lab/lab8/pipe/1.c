#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
  int p2c[2], n;
  int result = pipe(p2c);
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
    close(p2c[1]);
  
    read(p2c[0], &n, sizeof(int));
    if(n % 2 == 1){
      printf("Numar impar\n");
    }else{
      printf("Numar par\n");
    }

    close(p2c[0]);
    exit(0);
  }

  close(p2c[0]);

  scanf("%d", &n);
  write(p2c[1], &n, sizeof(int));

  close(p2c[1]);
  wait(0);

  return 0;
}
