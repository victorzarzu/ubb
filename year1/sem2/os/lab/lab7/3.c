#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int gcd(int a, int b){
  int r;
  while(b){
    r = a % b;
    a = b;
    b = r;
  }

  return a;
}

int main(int argc, char** argv){
  int p2c[2], c2p[2], n, gc;

  pipe(p2c); pipe(c2p);

  if(fork() == 0){
    close(p2c[1]); close(c2p[0]);

    int cp = 2, size = 0;
    int* nms = malloc(sizeof(int) * cp);

    int i;
    gc = 0;
    while(1){
      if(read(p2c[0], &n, sizeof(int)) > 0){
        if(n == 0){
          break;
        }

        if(size == cp){
          int *newNms = malloc(sizeof(int) * cp * 2);
          for(i = 0;i < size;++i){
            newNms[i] = nms[i];
          }
          free(nms);
          nms = newNms;
        }
        nms[size] = n;
        size++;

        if(gc == 0){
          gc = n;
        }
        else{
          if(n < 0){
            n = abs(n);
          }
          gc = gcd(gc, n);
        }

        printf("GCD for numbers: ");
        for(i = 0;i < size;++i)
          printf("%d ", nms[i]);
        printf("is ");
        printf("%d\n", gc);
      }
      else{
        exit(1);
      }
    }

    write(c2p[1], &gc, sizeof(int));
    free(nms);

    close(p2c[0]); close(c2p[1]);
    exit(0);
  }

  close(p2c[0]); close(c2p[1]);
  scanf("%d", &n);

  while(1){
    write(p2c[1], &n, sizeof(int));
    
    if(n == 0){
      break;
    }
    
    scanf("%d", &n);
  }

  wait(0);
  read(c2p[0], &gc, sizeof(int));
  printf("GCD of all numbers is: %d\n", gc);

  close(p2c[1]); close(c2p[0]);


  return 0;
}
