#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define oo 0x3f3f3f3f
#define char_int(n) (n == '.' ? oo : n <= '9' ? (n - '0') : (n - 'A' + 10))
#define int_char(n) (n == oo ? '.' : n <= 9 ? ('0' + n) : ('A' + n - 10))
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

char oper[5], as[102], bs[101];
int b1, b2, n1, n2, t, n3, vir;
int a[101], b[101], c[205], d[205];

void conv();
void run_all_tests();
void ui_convert();
void ui_operatii();
int convert();
int convert_power_2();
void op();
void add();
int add1();
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
  printf("Baze : 2 - 26 \n");
  printf("%s \n%s\n", "conv => conversie (apoi baza numarului, numarul si baza dorita)", "semnul operatiei dorite (si apoi baza si cele doua numere)");
  
  //scanf("%4s", oper);
  if(!strcmp(oper, "x")) return;

  if(!strcmp(oper, "conv")) ui_convert();
  else ui_operatii();
  
  printf("\n"); 
  goto repeat;
}

void string_int(char s[], int x[])
{
  for(int i = strlen(s) - 1;i >= 0;--i)
    x[strlen(s) - i - 1] = char_int(s[i]);
}

void string_to_int(char numar[], int *result)
{
  for(int i = strlen(numar) - 1;i >= 0;--i)
    result[strlen(numar) - i - 1] = char_int(numar[i]);
} 

void int_to_string(char *numar_string, int *numar_int, int len)
{
  for(int i = 0;i < len;++i)
    numar_string[len - i - 1] = int_char(numar_int[i]);
  numar_string[len] = 0;
}

void convert_fractionara(int *fractionara, int len_fractionara, int *len, int *result, int baza_sursa, int baza_destinatie)
{
  double nr_10 = 0, bd1 = baza_sursa, bd2 = baza_destinatie;
  double baz = 1 / bd1, d;
  for(int i = len_fractionara - 1;i >= 0;--i)
  {
    d = fractionara[i];
    nr_10 += d * baz;
    baz /= bd1;
  }

  double nr_101 = nr_10;
  while((*len) < 50 && nr_101 > 0)
    {
      (*len)++;
      nr_101 = (nr_101 * bd2 - ((long)nr_101 * bd2));
    }
  
  result[(*len)] = oo;
  for(int i = 0;i < (*len);++i)
    {
      nr_10 *= bd2;
      result[(*len) - 1 - i] = (long)nr_10;
      nr_10 = (double)(nr_10 - (long)nr_10);
    }
  if(*len)
    (*len)++;
}

void convert_intreaga(int *intreaga, int len_intreaga, int *len, int *result, int baza_sursa, int baza_destinatie)
{
  long long number_10 = 0, baza = 1;
  printf("inceput - %d\n", len_intreaga);
  for(int i = 0;i < len_intreaga;++i)
  {
    printf("da\n");
    number_10 += baza * intreaga[i];
    baza *= (long long)baza_sursa;
  }
  printf("%lld\n", number_10);

  while(number_10)
  {
    result[(*len)] = number_10 % baza_destinatie;
    number_10 /= baza_destinatie;
    (*len)++;
  }
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

void separare(int *numar, int *fractionara, int *intreaga, int *len_fractionara, int *len_intreaga, int len)
{
  *len_fractionara = 0;
  for(int i = 0;i < len;++i)
    if(numar[i] == oo)
      {
        *len_fractionara = i; 
        break;
      }
    else fractionara[i] = numar[i];

  for(int i = *len_fractionara + 1;i < len;++i)
    intreaga[i - *len_fractionara - 1] = numar[i]; 
  *len_intreaga = ((*len_fractionara) ? len - *len_fractionara - 1 : len);

}

void ui_convert()
{
  int base_sursa, base_destinatie, len;
  char numar[4 * 201], fractionara[101], intreaga[101];
  scanf("%d", &base_sursa);
  scanf("%200s", numar);  
  scanf("%d", &base_destinatie);


  if(base_sursa < 2 || base_sursa > 26 || base_destinatie < 2 || base_destinatie > 26)
    {
      printf("Baze gresite! \n");
      return;
    }

  if(!verif_nr(base_sursa, numar))
    {
      printf("Numerele oferite nu sunt in baza indicata! \n");
      return;
    }

  if(!(min(base_sursa, base_destinatie) == 2 && !(max(base_sursa, base_destinatie) & (max(base_sursa, base_destinatie) - 1))))
    convert(numar, base_sursa, base_destinatie);
  else
    convert_power_2(numar, base_sursa, base_destinatie);
  print(numar);
}

void convert_low_to_high_power_2(char *numar, int len_numar, int baza_sursa, int baza_destinatie, char *result_2, int *len)
{
  int len_of_item = 0;
  (*len) = 0;
  while(true)
  {
    baza_destinatie >>= 1;
    if(!baza_destinatie)
      break;
    ++len_of_item;
  }

  int diff = 0;
  if((len_numar % len_of_item))
    {
      diff = len_of_item - (len_numar % len_of_item);
      for(int i = len_numar - 1;i >= 0;--i)
        numar[i + diff] = numar[i];
      for(int i = 0;i < diff;++i)
        numar[i] = '0';
      len_numar += diff;
    }

  for(int i = 0;i < len_numar;i += len_of_item)
  {
    int current_number = 0;
    for(int j = 0;j < len_of_item;++j)
      {
        int current_digit = char_int(numar[i + j]), putere = len_of_item - j - 1;
        current_number = current_number + (current_digit << putere); 
      }
    result_2[(*len)] = int_char(current_number);
    (*len) += 1;
  }
  result_2[(*len)] = 0;
}

void convert_high_to_low_power_2(char *numar, int len_numar, int baza_sursa, int baza_destinatie, char *result_2, int *len)
{
  int len_of_item = 0;
  while(true)
    {
      baza_sursa >>= 1;
      if(!baza_sursa)
        break;
      ++len_of_item;
    }
  for(int i = 0;i < len_numar;++i)
    {
      int current_item = char_int(numar[i]);
      (*len) += len_of_item;
      for(int j = 1;j <= len_of_item;++j)
        {
          result_2[(*len) - j] = (current_item & 1) + '0';
          current_item >>= 1;
        }
    }
  result_2[(*len)] = 0;
}

int convert_power_2(char *numar, int baza_sursa, int baza_destinatie)
{
  int len_numar = strlen(numar), len = 0;
  char result[4 * 201];
  if(baza_sursa < baza_destinatie)
    convert_low_to_high_power_2(numar, len_numar, baza_sursa, baza_destinatie, result, &len);
  else
    convert_high_to_low_power_2(numar, len_numar, baza_sursa, baza_destinatie, result, &len);
  
  strcpy(numar, result);
  return len;
}

int convert(char numar[], int baza_sursa, int baza_destinatie)
{
  if(baza_sursa == baza_destinatie)
    return strlen(numar);

  int len_intreaga, len_fractionara, len;
  int fractionara[151], intreaga[151];
  int numar_int[201], result[201];
  len = strlen(numar);
  string_to_int(numar, numar_int);

  separare(numar_int, fractionara, intreaga, &len_fractionara, &len_intreaga, len);

  printf("sir ---- \n");
  for(int i = 0;i < len_intreaga;++i)
    printf("%d ", intreaga[i]);
  printf("\n");

  len = 0;
  if(len_fractionara)
    convert_fractionara(fractionara,len_fractionara, &len, result, baza_sursa, baza_destinatie);
  convert_intreaga(intreaga, len_intreaga, &len, result, baza_sursa, baza_destinatie);

  printf("%d\n", len_intreaga);
  printf("%d\n", len);

  int_to_string(numar, result, len);
  return len;
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

int add1(int *numar1, int *numar2, int *rezultat, int len_numar1, int len_numar2, int baza)
{
  int t = 0, len = max(len_numar1, len_numar2);
  
  for(int i = 0;i <= max(len_numar1, len_numar2);++i)
    {
      rezultat[i] = numar1[i] + numar2[i] + t;
      t = rezultat[i] / baza;
      rezultat[i] %= baza;
    }
  if(rezultat[len]) ++len;
  return len;
}

void service_add(char numar1[], char numar2[], char *rezultat, int baza_numar1, int baza_numar2, int baza_rezultat)
{
  int len_numar1, len_numar2;
  len_numar1 = convert(numar1, baza_numar1, baza_rezultat);
  printf("%s %d %d\n", numar1, baza_numar1, baza_rezultat);
  len_numar2 = convert(numar2, baza_numar2, baza_rezultat);

  int numar1_int[201], numar2_int[201], rezultat_int[201];
  string_to_int(numar1, numar1_int);
  string_to_int(numar2, numar2_int);

  int len_rezultat = add1(numar1_int, numar2_int, rezultat_int, len_numar1, len_numar2, baza_rezultat);
  int_to_string(rezultat, rezultat_int, len_rezultat);
}

void ui_operatii(char *operatie)
{
  int baza_numar1, baza_numar2, baza_rezultat;
  char numar1[201], numar2[201], rezultat[202];

  scanf("%d", &baza_numar1);
  scanf("%200s", numar1);
  
  if(!verif_nr(baza_numar1, numar1))
  {
    printf("Numarul nu este in baza specificata! \n");
    return;
  }

  scanf("%d", &baza_numar2);
  scanf("%200s", numar2);
  
  if(!verif_nr(baza_numar2, numar2))
  {
    printf("Numarul nu este in baza specificata! \n");
    return;
  }

  scanf("%d", &baza_rezultat);


  switch(operatie[0])
    {
      case '+':
        service_add(numar1, numar2, rezultat, baza_numar1, baza_numar2, baza_rezultat);
        break;
      default:
        printf("Operatie invalida!\n");
    }
  printf("%s", rezultat);
}

void run()
{
  char operatie[10];
  repeat:

  printf("Operatia x pentru a inchide\n");
  printf("Baze : 2 - 26 \n");
  printf("%s \n%s\n", "conv => conversie (apoi baza numarului, numarul si baza dorita)", "semnul operatiei dorite (si apoi baza si cele doua numere)");
  
  scanf("%10s", operatie);

  if(!strcmp(operatie, "conv")) ui_convert();
  else ui_operatii(operatie);
  
  goto repeat;
}

void op()
{
  cc();  
  int_string(as, c, n1);
  print(as);
}

int main()
{
  run_all_tests();
  run();
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


void test_convert()
{
  /*
  char numar[201] = "655488.712\0";
  char numar_convertit[] = "2400200.554426416254";
  int baza_sursa = 10, baza_destinatie = 8;
  convert(numar, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit);++i)
    assert(numar[i] == numar_convertit[i]);
  
  char numar_convertit1[] = "655488.7119\0";
  char numar1[] = "2400200.554426416254";
  baza_sursa = 8, baza_destinatie = 10;
  convert(numar1, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit1);++i)
    assert(numar1[i] == numar_convertit1[i]);

  */
  char numar3[] = "A\0";
  char numar_convertit3[] = "10";
  int baza_sursa = 16, baza_destinatie = 10;
  convert(numar3, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit3);++i)
    assert(numar3[i] == numar_convertit3[i]);

}

void test_convert_power_2()
{
  char numar[4 * 201] = "BCF19\0";
  char numar_convertit[] = "10111100111100011001";
  int baza_sursa = 16, baza_destinatie = 2;
  convert_power_2(numar, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit);++i)
    assert(numar[i] == numar_convertit[i]);

  char numar1[4 * 201] = "1111000110110\0";
  char numar_convertit1[] = "17066\0";
  baza_sursa = 2, baza_destinatie = 8;
  convert_power_2(numar1, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit1);++i)
    assert(numar1[i] == numar_convertit1[i]);

  char numar2[4 * 201] = "101010110111011101\0";
  char numar_convertit2[] = "2ADDD\0";
  baza_sursa = 2, baza_destinatie = 16;
  convert_power_2(numar2, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit2);++i)
    assert(numar2[i] == numar_convertit2[i]);

  char numar3[4 * 201] = "11001001\0";
  char numar_convertit3[] = "3021\0";
  baza_sursa = 2, baza_destinatie = 4;
  convert_power_2(numar3, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit3);++i)
    assert(numar3[i] == numar_convertit3[i]);
}

void run_all_tests()
{
  test_convert();
  test_convert_power_2();
}
