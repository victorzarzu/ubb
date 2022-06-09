#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv){
  if(argc < 2){
    perror("numar argumente invalid\n");
    exit(EXIT_FAILURE);
  }
  srand((unsigned int)getpid());
  int n, i;
  sscanf(argv[1], "%d", &n);
  
  int p2c[2], c2p[2], result;
  double medie;

  result = pipe(p2c); 
  if(result == -1){
    perror("eroare pipe\n");
    exit(EXIT_FAILURE);
  }

  result = pipe(c2p); 
  if(result == -1){
    perror("eroare pipe\n");
    exit(EXIT_FAILURE);
  }

  result = fork(); 
  if(result == -1){
    perror("eroare fork\n");
    exit(EXIT_FAILURE);
  }
  else if(result == 0){
    close(p2c[1]); close(c2p[0]);
    int x;
    medie = 0;

    for(i = 0;i < n;++i){
      read(p2c[0], &x, sizeof(int));
      medie = medie + x;
    }
    close(p2c[0]);
    
    medie /= n;
    write(c2p[1], &medie, sizeof(double)); 
    
    close(c2p[1]);
    exit(0);
  }

  close(p2c[0]); close(c2p[1]);

  int* arr = (int *)malloc(n * sizeof(int));

  for(i = 0;i < n;++i){
    arr[i] = rand() % 10000000;
  }

  for(i = 0;i < n;++i){
    write(p2c[1], &arr[i], sizeof(int)); 
  }
  close(p2c[1]);

  wait(0);
  read(c2p[0], &medie, sizeof(double));

  close(c2p[0]);

  printf("Medie: %.3lf\n", medie);

  return 0;
}
