#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct linie {
  int m;
  int* l;
};

void* routine(void* arg) {
  struct linie* lin = (struct linie*)arg; 

  int *sum = (int*)malloc(sizeof(int));
  if(sum == NULL) {
    printf("Eroare malloc\n");  
    return (void *)sum;
  }
  *sum = 0;
  int i;

  for(i = 0;i < lin->m;++i) {
    *sum += lin->l[i]; 
  }
  free(lin);

  return (void *)sum;
}

int main(int argc, char** argv) {
  int n, m;
  FILE* file = fopen("bigmat", "r");
  if(file == NULL) {
    printf("Eroare fopen\n");
    exit(EXIT_FAILURE);
  }

  fscanf(file, "%d %d", &n, &m);
  int** mat = (int **)malloc(sizeof(int *) * n);
  if(mat == NULL) {
    printf("Eroare malloc\n");
    exit(EXIT_FAILURE);
  }

  int i, j;
  for(i = 0;i < n;++i) {
    mat[i] = (int *)malloc(sizeof(int) * m);  
    if(mat[i] == NULL) {
      printf("Eroare malloc\n");
      exit(EXIT_FAILURE);
    }
  }
  
  for(i = 0;i < n;++i) {
    for(j = 0;j < m;++j) {
      fscanf(file, "%d", &mat[i][j]);
    }
  }
  fclose(file);
  
  pthread_t* tr = (pthread_t *)malloc(sizeof(pthread_t) * n);
  if(tr == NULL) {
    printf("Eroare malloc\n");
    exit(EXIT_FAILURE);
  }

  for(i = 0;i < n;++i) {
    struct linie* lin = (struct linie*)malloc(sizeof(struct linie));
    lin->m = m;
    lin->l = mat[i];
    if(pthread_create(&tr[i], NULL, routine, (void *)lin) != 0) {
      printf("Eroare create!\n");
      exit(EXIT_FAILURE);
    }
  }

  int sum = 0;
  void *s;
  for(i = 0;i < n;+++i) {
    if(pthread_join(tr[i], &s) != 0) {
      printf("Eroare join!\n");
      exit(EXIT_FAILURE);
    }
    sum += *(int *)s;
    free(s);
  }

  printf("Suma: %d\n", sum);

  free(tr);
  for(i = 0;i < n;++i) {
    free(mat[i]);
  }

  free(mat);

  return 0;
}
