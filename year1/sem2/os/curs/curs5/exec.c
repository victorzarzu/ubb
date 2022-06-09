#include <stdio.h>

int main(int argc, char** argv) {
  execlp("grep", "grep", "-E", "1918", "/etc/passwd", NULL);

  return 0;
}
