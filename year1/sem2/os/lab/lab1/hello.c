#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if(argc < 2) {
    printf("Please provide at least one argument\n");
    exit(1);
  }
  printf("Hello %s\n", argv[1]);

  return 0;
}
