#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
  int i;
  printf("A\n");
  for(i = 0;i < 3;++i)
  {
    fork();
  }
  printf("B\n");
  return 0;
}
