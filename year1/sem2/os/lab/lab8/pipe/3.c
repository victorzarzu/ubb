#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
  int p2c[2], result;
  char c;

  result = pipe(p2c);
  if(result == -1){
    perror("eroare pipe");
    exit(EXIT_FAILURE);
  }

  result = fork();
  if(result == -1){
    perror("eroare pipe");
    exit(EXIT_FAILURE);
  }
  else if(result == 0){
    close(p2c[1]);

    read(p2c[0], &c, sizeof(char));
    char a = c;
    int number = 0;

    while(a != '\n'){
      read(p2c[0], &a, sizeof(char));
      if(a == c){
        ++number;
      }
    }
    printf("Numar aparitii: %d\n", number);

    close(p2c[0]);
    exit(EXIT_SUCCESS);
  }

  close(p2c[0]);
  
  scanf("%c\n", &c);
  write(p2c[1], &c, sizeof(char));

  while(c != '\n'){
    scanf("%c", &c);
    write(p2c[1], &c, sizeof(char));
  }
  write(p2c[1], &c, sizeof(char));

  close(p2c[1]);
  wait(0);

  return 0;
}
