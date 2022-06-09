#include <stdio.h>
#include <string.h>
#include <unistd.h>

void with_lib()
{
  char s[64];
  char *p;
  int i;

  while(1)
  {
    p = fgets(s, 64, stdin);
    if (p == NULL)
      break;
    for(i = 0;i < strlen(s);++i)
      {
        if(s[i] != '\n')
          s[i] = '*';
      }
    fputs(s, stdout);

  }
}

void with_syscall()
{
  char s[64];
  int i, k;

  while(1)
  {
    k = read(0, s, 64);
    if(k <= 0)
      break;

    for(i = 0;i < k;++i)
      {
        if(s[i] != '\n')
          s[i] = '*';
      }
    
    write(1, s, k);
  }
}


int main(int argc, char** argv)
{
  with_syscall();
  return 0;
}
