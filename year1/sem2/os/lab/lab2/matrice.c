/*
 Sa se citeasca o matrice de numere intregi dintr-un fisier si sa se stocheze intr-un al fisier. Matricea va fi stocata in memorie. Ambele nume de fisiere vor fi date ca argumente la linia de comanda
 * Pe prima linie a fisierului se vor afla numarul de linii si coloane ale matricii
 * */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
  if(argc < 3)
  {
    printf("Dati doua fisiere\n");
    exit(1);
  }

  FILE *f_in = fopen(argv[1], "r");
  if(f_in == NULL)
  {
    perror("Eroare la deschidere fisier in"); //Da append la mesajul de eroare - pe canalul 2
    exit(1);
  }

  int n, m, i, j;
  fscanf(f_in, "%d %d", &n, &m);

  int **matrice = (int**)malloc(n * sizeof(int*));

  for(i = 0;i < n;++i)
    matrice[i] = (int *)malloc(m * sizeof(int));

  for(i = 0;i < n;++i)
    for(j = 0;j < m;++j)
      fscanf(f_in, "%d", &matrice[i][j]);

  fclose(f_in);

  FILE *f_out = fopen(argv[2], "w");
  if(f_out == NULL)
  {
    perror("Eroare la deschidere fisier out");
    exit(1);
  }

  for(i = 0;i < n;++i, fprintf(f_out, "\n"))
    for(j = 0;j < m;++j)
      fprintf(f_out, "%4d", matrice[i][j]);

  for(i = 0;i < n;++i)
    free(matrice[i]);
  free(matrice);

  fclose(f_out);
  return 0;
}
