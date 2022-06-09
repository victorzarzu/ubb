#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  if(fork() == 0) {
    execlp("grep", "grep", "-E", "1918", "/etc/passwd", NULL);
    exit(1);
  }

  printf("****************************************************\n");
  wait(0);
  return 0;
}
