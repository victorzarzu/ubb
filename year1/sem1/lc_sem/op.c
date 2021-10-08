#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define oo 0x3f3f3f3f
#define char_int(n) (n == '.' ? oo : n <= '9' ? (n - '0') : (n - 'A' + 10))
#define int_char(n) (n == oo ? '.' : n <= 9 ? ('0' + n) : ('A' + n - 10))
#define max(a, b) (a > b ? a : b)

char oper[5], as[102], bs[101];
int b1, b2, n1, n2, t, n3, vir;
int a[101], b[101], c[205], d[205];

void conv();
void op();
void add();
void sub();
void mul();
void div();

void swap(int *a, int *b)
{
  int c = (*a);
  (*a) = (*b);
  (*b) = c;
}

void reset()
{
  for(int i = 0 ;i < 205;++i) c[i] = 0; 
}

void print(char s[])
{
  printf("%s", s);
}

void cit()
{
  repeat:

  printf("Operatia x pentru a inchide\n");
  printf("Baze : 2 - 36 \n");
  printf("%s \n%s\n", "conv => conversie (apoi baza numarului, numarul si baza dorita)", "semnul operatiei dorite (si apoi baza si cele doua numere)");
  
  scanf("%4s", oper);
  if(!strcmp(oper, "x")) return;

  if(!strcmp(oper, "conv")) conv();
  else op();
  
  
  printf("\n"); 
  goto repeat;
}

void string_int(char s[], int x[])
{
  for(int i = strlen(s) - 1;i >= 0;--i)
    x[strlen(s) - i - 1] = char_int(s[i]);
}

void int_string(char s[], int x[], int len)
{
  for(int i = 0;i < len;++i)
    s[len - i - 1] = int_char(x[i]);
  s[len] = 0;
}

bool verif_nr(int b, char s[])
{
  for(int i = 0;i < strlen(s);++i)
    if(char_int(s[i]) >= b && char_int(s[i]) != oo)
      return false;
  return true;
}

void cc()
{
  baza_cc:

  scanf("%d", &b1);

  if(b1 < 2 || b1 > 36)
    {printf("Baza gresita! \n"); goto baza_cc;}

  op_citire:

  scanf("%100s", as);
  scanf("%100s", bs);

  if(!verif_nr(b1, as) || !verif_nr(b1, bs))
    {
      printf("Numarele oferite nu sunt in baza %d \n", b1);
      goto op_citire;
    }
  if(strlen(bs) > strlen(as) || ((strlen(bs) == strlen(as) && strcmp(as, bs) < 0)))
   {string_int(as, b), string_int(bs, a); n2 = strlen(as); n1 = strlen(bs);}
  else {string_int(as, a), string_int(bs, b); n1 = strlen(as); n2 = strlen(bs);};

  switch(oper[0])
  {
    case '+':
      add(a, b);
      break;
    case '-':
      sub(a, b);
      break;
    case '*':
      mul(a, b);
      break;
    case '/':
      div(a, b);
      break;
    default:
      break;
  }
}

void sep()
{
  n1 = strlen(as);
  string_int(as, a);  
  int vir = 0;

  for(int i = 0;i < n1;++i)
    if(a[i] == oo)
      {vir = i; break;}
    else b[i] = a[i];

  n2 = vir;
  for(int i = vir + 1;i < n1;++i)
    a[i - vir - 1] = a[i]; 
  n1 = n1 - vir - 1 * (vir > 0);
}

void conv_int(int *len)
{
  long long nr_10 = 0;
  long long baz = 1;
  for(int i = 0;i < n1;++i)
    {
      nr_10 += baz * a[i];
      baz *= b1;
    }
  
  while(nr_10)
  {
    c[(*len)] = nr_10 % b2;
    nr_10 /= b2;
    (*len) += 1;
  }
}

void conv_frac(int *len)
{
  double nr_10 = 0, bd1 = b1, bd2 = b2;
  double baz = 1 / bd1, d;
  for(int i = n2 - 1;i >= 0;--i)
  {
    d = b[i];
    nr_10 += d * baz;
    baz /= bd1;
  }

  (*len) = 0; double nr_101 = nr_10;
  while((*len) < 50 && nr_101 > 0)
    {
      ++(*len);
      nr_101 = (nr_101 * bd2 - ((long)nr_101 * bd2));
    }
  
  c[(*len)] = oo;
  for(int i = 0;i < (*len);++i)
    {
      nr_10 *= bd2;
      c[(*len) - 1 - i] = (long)nr_10;
      nr_10 = (double)(nr_10 - (long)nr_10);
    }
  (*len)++;
}

void ccc()
{
  baze_ccc:

  scanf("%d", &b1);

  conv_citire:

  scanf("%100s", as);

  if(!verif_nr(b1, as))
    {
      printf("Numarul oferit nu este in baza %d \n", b1);
      goto conv_citire;
    }

  scanf("%d", &b2);

  if(b1 < 2 || b2 < 2 || b1 > 26 || b2 > 26)
    {printf("Baze gresite! \n"); goto baze_ccc;}

  sep();
  if(n2)
    conv_frac(&vir);
  conv_int(&vir);
}

void conv()
{
  ccc();   
  int_string(as, c, vir);
  print(as);
}

void op()
{
  cc();  
  int_string(as, c, n1);
  print(as);
}

int main()
{
  cit();
  return 0;
}

void mov(int s[])
{
  for(int i = 100;i >= 1;--i)
    s[i] = s[i - 1];
}

void add(int a[], int b[])
{
  reset();
  t = 0;  
  for(int i = 0;i <= max(n1, n2);++i)  
    {
      c[i] = a[i] + b[i] + t;
      t = c[i] / b1;
      c[i] %= b1;
    }
  if(c[n1]) n1++;
}

void sub(int a[], int b[])
{
  reset();
  t = 0;
  for(int i = 0;i < n1;++i)
    {
      c[i] = a[i] - t - b[i]; t = 0;
      if(c[i] < 0) {c[i] += b1; t = 1;}
    }
  for(int i = n1 - 1;i >= 0;--i)
    if(!c[i]) --n1;
  if(!n1) n1++;
}

void mul(int a[], int b[])
{
  int n11 = n1, n22 = n2;
  reset();
  for(int j = 0;j < n22;++j)
  {
    t = 0;
    for(int i = 0;i < 205;++i) d[i] = 0; 
    for(int i = 0;i <= n11;++i)
      {
        d[i + j] = b[j] * a[i] + t;
        t = d[i + j] / b1;
        d[i + j] %= b1;
      }
    t = 0;
    for(int i = 0;i <= max(n1, n2);++i)
    {
      c[i] = c[i] + d[i] + t;
      t = c[i] / b1;
      c[i] %= b1;
    }
    if(c[max(n1, n2)]) ++n1;
    ++n2;
  }
  n1 = max(n1, n2);
}

void div(int a[], int b[])
{
  reset();
  t = 0;
  for(int i = n1 - 1;i >= 0;--i)
  {
    c[i] = t * b1 + a[i];
    t = c[i] % b[0];
    c[i] /= b[0];
  }
  printf("Rest %c ", int_char(t));
}
