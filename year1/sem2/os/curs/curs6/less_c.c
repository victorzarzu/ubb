#include <stdio.h>

int main(int argc, char** argv){
  
  int i;
  FILE* desc;
  desc = popen("less", "w");
  for(i = 0;i < 50;++i){
    fprintf(desc, "Eu sunt Victor\n");
    fprintf(desc, "Zarzu Victor\n");
    fprintf(desc, "Zarzu\n\n");
  }
  pclose(desc);

  return 0;
}
