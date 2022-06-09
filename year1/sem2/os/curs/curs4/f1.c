#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
  printf("A\n");
  sleep(3);
  fork();
  printf("B\n");
  sleep(5);
  return 0;
}
