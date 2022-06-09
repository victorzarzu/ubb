#include <stdio.h>
#include <pthread.h>

struct args{
  int n;
  char* name;
};

int n = 1;

void* f(void* a){
  int i;

  struct args *p = (struct args*)a;
  for(i = 0;i < p->n;++i){
    printf("%s\n", p->name);
  }
  return NULL;
}

int main(int argc, char** argv){
  pthread_t ta, tb;
  int i, n = 1;
  struct args aa, ab;

  if(argc > 1){
    sscanf(argv[1], "%d", &n);
  }

  aa.n = n; aa.name = "fa";
  ab.n = n; ab.name = "fb";


  pthread_create(&ta, NULL, f, &aa);
  pthread_create(&tb, NULL, f, &ab);
  for(i = 0;i < n;++i){
    printf("main\n");
  }

  pthread_join(ta, NULL);
  pthread_join(tb, NULL);

  return 0;
}
