#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int is_prime(int x){
  if(x < 2){
    return 0;
  }
  if(x == 2){
    return 1;
  }
  if(!(x % 2)){
    return 0;
  }
  int d = 3;
  while(d * d <= x){
    if(!(x % d)){
      return 0;
    }
    d += 2;
  }
  return 1;
}

int main(int argc, char** argv){
  int p2c[2], n, result;
  
  result = pipe(p2c);
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
    if(is_prime(n)){
      printf("e prim\n");
    }
    else{
      printf("nu e prim\n");
    }

    close(p2c[0]);
    exit(EXIT_SUCCESS);
  }

  close(p2c[0]);

  scanf("%d", &n);
  write(p2c[1], &n, sizeof(int));

  close(p2c[1]);

  return 0;
}
