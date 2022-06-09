#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define myAbs(x) (x < 0) ? -x : x

int myRandom(int min, int max){
  return rand() % (max - min) + min;
}

int main(int argc, char** argv){
  int a2b[2], b2a[2], n, flag;

  pipe(a2b); pipe(b2a);

  if(fork() == 0){
    close(a2b[1]); close(b2a[0]); 
    srand((unsigned int)getpid());
    
    flag = 0;
    while(!flag){
      int m = myRandom(100, 1000);
      read(a2b[0], &n, sizeof(int));          
      printf("%d - %d - %d\n", m, n, abs(m - n));

      if(abs(m - n) <= 50){
        flag = 1;
      }
      write(b2a[1], &flag, sizeof(int));
    }

    close(a2b[0]); close(b2a[1]);
    exit(0);
  }
  srand((unsigned int)getpid());

  close(a2b[0]); close(b2a[1]);
  
  n = myRandom(50, 1050);
  write(a2b[1], &n, sizeof(int));

  flag = 0;
  while(!flag){
    read(b2a[0], &flag, sizeof(int));
    if(flag){
      flag = 1;
    }
    else{
      n = myRandom(50, 1050);
      write(a2b[1], &n, sizeof(int));
   
    
  }

  wait(0);
  close(a2b[1]); close(b2a[0]);

  return 0;
}
