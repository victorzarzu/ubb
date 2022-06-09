#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv){
  int a2b, b2a, n = 10;

  a2b = open("a2b", O_WRONLY);
  b2a = open("b2a", O_RDONLY);

  write(a2b, &n, sizeof(int));

  while(1){
    if(read(b2a, &n, sizeof(int)) <= 0){
      break;
    }

    if(n <= 0){
      break;
    }

    printf("a: %d -> %d\n", n, n - 1);
    n--;
    write(a2b, &n, sizeof(int));
  }
  printf("a second\n");
  close(a2b); close(b2a);
  

  return 0;
}
