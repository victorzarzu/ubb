#include <stdio.h>
#include <signal.h>

void f(int sgn) {
  if(sgn == SIGINT) {
    printf("Nu ma opreste pe mine un Ctrl-C!\n");
  }
  else {
    printf("Nu ma opreste pe mine un Ctrl-Z!\n");
  }
}

int main(int argc, char** argv) { //sa nu se opreasca cu Ctrl-C
  signal(SIGINT, f);
  signal(SIGTSTP, f);
  while(1);
  return 0;
}
