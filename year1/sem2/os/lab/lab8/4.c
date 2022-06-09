#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>

int main(int argc, char** argv){
  if(argc < 2){
    perror("cel putin un argument");
    exit(EXIT_FAILURE);
  }

  int len = 0, i;
  for(i = 1;i < argc;++i){
    len += (int)strlen(argv[i]) + 1;
  }

  char* cmd = (char *)malloc(len * sizeof(char));
  cmd[0] = '\0';
  for(i = 1;i < argc;++i){
    strcat(cmd, argv[i]);
    strcat(cmd, " ");
  }
  cmd[len - 1] = '\0';
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);
  system(cmd);
  gettimeofday(&t2, NULL);
  free(cmd);

  printf("Durata: %lf\n", (double)(t2.tv_sec - t1.tv_sec));

  return 0;
}
