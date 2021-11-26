//Tema electronica Zarzu Victor-Eugen

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define oo 0x3f3f3f3f
#define char_int(n) (n == '.' ? oo : n <= '9' ? (n - '0') : (n - 'A' + 10))
#define int_char(n) (n == oo ? '.' : n <= 9 ? ('0' + n) : ('A' + n - 10))
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

void conv();
void run_all_tests();
void ui_convert();
int convert();
int convert_power_2();
void op();
int add();

void print(char *s)
{
  /*
  functie care tipareste sirul de caractere s
  params: s - un pointer care un sir de caractere
  return: -
  */
  printf("Rezultat: %s\n", s);
}

void string_to_int(char *numar, int *result)
{
  /*
  functie care converteste un sir de char (numar) catre un sir de intregi (result)
  params: numar - un pointer catre un sir de char; result - un pointer catre un sir de intregi
  return: -
  */
  for(int i = strlen(numar) - 1;i >= 0;--i)
    result[strlen(numar) - i - 1] = char_int(numar[i]); //se converteste, dar se si inverseaza pentru ulterioarele operatii
} 

void int_to_string(char *numar_string, int *numar_int, int len)
{
  /*
  functie care converteste un sir de intregi (numar_int) catre un sir de char (numar_string)
  params: numar_string - un pointer catre un sir de char; numar_int - un pointer catre un sir de intregi; len - un intreg
  return: -
  */
  for(int i = 0;i < len;++i)
    numar_string[len - i - 1] = int_char(numar_int[i]); //se converteste, dar se si inverseaza, rezultatul fiind inversat in formatul string
  numar_string[len] = 0;
}

void convert_intreaga(int *intreaga, int len_intreaga, int *len, int *result, int baza_sursa, int baza_destinatie)
{
  /*
  functie care converteste un sir de intregi din baza_sursa in baza_destinatie
  params: intreaga - un pointer catre un sir de intregi
          len_intreaga - un intreg reprezentand lungimea sirului in intregi initial
          len - un pointer catre o valoare intreaga reprezentand lungimea sirului final
          result - un pointer catre un sir de intregi reprezentand sirul rezultat in urma conversiei
          baza_sursa - un intreg reprezentand baza sursa
          baza_destinatie - un intreg reprezentand baza destinatie
  return: -
  */  
  long long number_10 = 0, baza = 1;

  for(int i = 0;i < len_intreaga;++i)
  {
    number_10 += baza * intreaga[i];
    baza *= (long long)baza_sursa;
  }

  while(number_10)
  {
    result[(*len)] = number_10 % baza_destinatie;
    number_10 /= baza_destinatie;
    (*len)++;
  }
}

bool verif_nr(int b, char *s)
{
  /*
  functie care verifica daca sirul oferit prin s este in baza indicata
  params: b - un intreg reprezentand baza in care ar trebui sa fie numarul oferit
          s - un pointer catre un sir de caractere
  return: true - daca numarul oferit este in baza indicata
          fals - daca numarul oferit nu este in baza indicata

  */
  for(int i = 0;i < strlen(s);++i)
    if(!(s[i] >= '0' && s[i] - '0' <= 26))
      return false;
  for(int i = 0;i < strlen(s);++i)
    if(char_int(s[i]) >= b)
      return false;
  return true;
}

int convert_service(char *numar, int base_sursa, int base_destinatie)
{
  /*
  functia service pentru convertire
  params: numar - un pointer la inceputul unui sir de caractere
          base_sursa - un intreg reprezentand baza sursa a numarului
          base_destinatie - un intreg reprezentand baza destinatie a numarului
  return: lungimea sirului convertit
  */  
  int len;

  if((base_sursa & (base_sursa - 1)) || (base_destinatie & (base_destinatie) - 1)) //se verifica daca nu trebuie facuta o conversie intre baze puteri a lui 2
    len = convert(numar, base_sursa, base_destinatie);
  else
    len = convert_power_2(numar, base_sursa, base_destinatie);
  return len;
}

void ui_convert()
{
  /*
  functie pentru ui-ul de convertire numar
  */
  int base_sursa, base_destinatie, len;
  char numar[4 * 201];
  printf("baza sursa\nnumar\nbaza destinatie\n\n");
  scanf("%d", &base_sursa);
  scanf("%200s", numar);  
  scanf("%d", &base_destinatie);

  if(base_sursa < 2 || base_sursa > 36 || base_destinatie < 2 || base_destinatie > 36)
    {
      printf("Baze gresite! \n");
      return;
    }

  if(!verif_nr(base_sursa, numar))
    {
      printf("Numerele oferite nu sunt in baza indicata! \n");
      return;
    }

  /*
  if(!(min(base_sursa, base_destinatie) == 2 && !(max(base_sursa, base_destinatie) & (max(base_sursa, base_destinatie) - 1)))) //se verifica daca o baza este 2 si cealalta este o baza putere a lui 2 
    convert(numar, base_sursa, base_destinatie);
  else
    convert_power_2(numar, base_sursa, base_destinatie);
  */
  convert_service(numar, base_sursa, base_destinatie);
  print(numar);
}


void convert_low_to_high_power_2(char *numar, int len_numar, int baza_sursa, int baza_destinatie, char *result_2, int *len)
{
  /*
  functie care converteste un numar din baza doi intr-o baza care este putere a lui doi
  params: numar - un pointer catre un sir de caractere
          len_numar - lungimea numarului oferit
          baza_sursa - baza sursa (2 in cazul acesta)
          baza_destinatie - baza sursa
          result_2 - un pointer catre un sir de caractere reprezentand rezultatul conversiei
          len - un intreg reprezentand lungimea sirului destinatie
  return: -
  */
  if(baza_sursa == baza_destinatie) {
    (*len) = len_numar;
    strcpy(result_2, numar);
    return;
  }

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
  /*
  functie care converteste un numar dintr-o baza putere a lui doi in baza doi
  params: numar - un pointer catre un sir de caractere
          len_numar - lungimea numarului oferit
          baza_sursa - baza sursa 
          baza_destinatie - baza sursa (2 in cazul acesta)
          result_2 - un pointer catre un sir de caractere reprezentand rezultatul conversiei
          len - un intreg reprezentand lungimea sirului destinatie
  return: -
  */
  if(baza_sursa == baza_destinatie) {
    (*len) = len_numar;
    strcpy(result_2, numar);
    return;
  }

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
  /*
  functie care converteste un numar dintr-o baza putere a lui doi in alta baza putere a lui doi
  params: numar - un pointer catre un sir de caractere
          baza_sursa - baza sursa a numarului
          baza_destinatie - baza destinatie a numarului
  return: un intreg reprezentand lungimea numarului convertit
  */
  int len_numar = strlen(numar), len = 0;
  char result[4 * 201];
  convert_high_to_low_power_2(numar, len_numar, baza_sursa, 2, result, &len);
  strcpy(numar, result);
  len_numar = len; len = 0;
  convert_low_to_high_power_2(numar, len_numar, 2, baza_destinatie, result, &len);

  /*
  if(baza_sursa < baza_destinatie)
    convert_low_to_high_power_2(numar, len_numar, baza_sursa, baza_destinatie, result, &len);
  else
    convert_high_to_low_power_2(numar, len_numar, baza_sursa, baza_destinatie, result, &len);
  */

  strcpy(numar, result);
  return len;
}


int convert(char *numar, int baza_sursa, int baza_destinatie)
{
  /*
  functie care converteste un numar din baza sursa in baza destinatie
  params: numar - un pointer catre un sir de caractere
          baza_sursa - baza sursa a numarului
          baza_destinatie - baza destinatie a numarului
  return: un intreg reprezentand lungimea numarului convertit
  */
  if(baza_sursa == baza_destinatie)
    return strlen(numar);

  int len_numar = strlen(numar), len;
  int numar_int[201], result[201];
  string_to_int(numar, numar_int);

  len = 0;
  convert_intreaga(numar_int, len_numar, &len, result, baza_sursa, baza_destinatie);

  int_to_string(numar, result, len);
  return len;
}


int add(int *numar1, int *numar2, int *rezultat, int len_numar1, int len_numar2, int baza)
{
  /*
  functie care aduna doua numere intr-o baza
  params: numar1 - un pointer catre un sir de intregi
          numar2 - un pointer catre un sir de intregi
          rezultat - un pointer catre un sir de intregi
          len_numar1 - un intreg reprezentand lungimea numarului 1
          len_numar2 - un intreg reprezentand lungimea numarului 2
          baza - un intreg reprezentand baza numerelor
  return: un intreg reprezentand lungimea numarului rezultat in urma adunarii
  */
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

int sub(int *numar1, int *numar2, int *rezultat, int len_numar1, int len_numar2, int baza)
{
  /*
  functie care scade doua numere intr-o baza
  params: numar1 - un pointer catre un sir de intregi
          numar2 - un pointer catre un sir de intregi
          rezultat - un pointer catre un sir de intregi
          len_numar1 - un intreg reprezentand lungimea numarului 1
          len_numar2 - un intreg reprezentand lungimea numarului 2
          baza - un intreg reprezentand baza numerelor
  return: un intreg reprezentand lungimea numarului rezultat in urma scaderii
  */
  int t = 0;
  int len = len_numar1;
  for(int i = 0;i < len_numar1;++i)
    {
      rezultat[i] = numar1[i] - t - numar2[i];
      t = 0;
      if(rezultat[i] < 0)
      {
        rezultat[i] += baza;
        t = 1;
      }
    }
  for(int i = len_numar1 - 1;i >= 0;--i)
    if(!rezultat[i]) --len;
    else break;
  if(!len) ++len;
  return len;
}

int mul(int *numar1, int *numar2, int *rezultat, int len_numar1, int len_numar2, int baza)
{
  /*
  functie care inmulteste un numar cu o cifra intr-o baza
  params: numar1 - un pointer catre un sir de intregi
          numar2 - un pointer catre un sir de intregi
          rezultat - un pointer catre un sir de intregi
          len_numar1 - un intreg reprezentand lungimea numarului 1
          len_numar2 - un intreg reprezentand lungimea numarului 2
          baza - un intreg reprezentand baza numerelor
  return: un intreg reprezentand lungimea numarului rezultat in urma inmultirii
  */
  int t = 0;
  for(int i = 0;i <= len_numar1;++i)
  {
    rezultat[i] = numar2[0] * numar1[i] + t;
    t = rezultat[i] / baza;
    rezultat[i] %= baza;
  }

  if(rezultat[len_numar1]) ++len_numar1;
  return len_numar1;
}

int div(int *numar1, int *numar2, int *rezultat, int len_numar1, int len_numar2, int baza, int *rest)
{
  /*
  functie care imparte un numar cu o cifra intr-o baza
  params: numar1 - un pointer catre un sir de intregi
          numar2 - un pointer catre un sir de intregi
          rezultat - un pointer catre un sir de intregi
          len_numar1 - un intreg reprezentand lungimea numarului 1
          len_numar2 - un intreg reprezentand lungimea numarului 2
          baza - un intreg reprezentand baza numerelor
          rest - un intreg reprezentand restul impartirii
  return: un intreg reprezentand lungimea numarului rezultat in urma impartirii
  */
  int t = 0;
  for(int i = len_numar1 - 1;i >= 0;--i)
  {
    rezultat[i] = t * baza + numar1[i];
    t = rezultat[i] % numar2[0];
    rezultat[i] /= numar2[0];
  }

  *rest = t;
  for(int i = len_numar1 - 1;i >= 0;--i)
    {
      if(!rezultat[i])
        --len_numar1;
      else
        break;
    }
  return len_numar1;
}

void service_div(char *numar1, char *numar2, char *rezultat, int baza_numar1, int baza_numar2, int baza_rezultat, int *rest)
{
  /*
  functia service pentru impartire
  params: numar1 - un pointer catre un sir de caractere
          numar2 - un pointer catre un sir de caractere 
          rezultat - un pointer catre un sir de caractere 
          baza_numar1 - un intreg reprezentand baza numarului 1
          baza_numar2 - un intreg reprezentand baza numarului 2
          baza_rezultat - un intreg reprezentand baza numarului rezultat
          rest - un intreg reprezentand restul impartirii
  return: - 
  */
  int len_numar1, len_numar2;
  len_numar1 = convert_service(numar1, baza_numar1, baza_rezultat);
  len_numar2 = convert_service(numar2, baza_numar2, baza_rezultat);

  int numar1_int[201], numar2_int[201], rezultat_int[201];
  memset(numar1_int, 0, sizeof(numar1_int));
  memset(numar2_int, 0, sizeof(numar2_int));
  memset(rezultat_int, 0, sizeof(rezultat_int));
  string_to_int(numar1, numar1_int);
  string_to_int(numar2, numar2_int);

  int len_rezultat = div(numar1_int, numar2_int, rezultat_int, len_numar1, len_numar2, baza_rezultat, rest);
  int_to_string(rezultat, rezultat_int, len_rezultat);

}

void service_mul(char *numar1, char *numar2, char *rezultat, int baza_numar1, int baza_numar2, int baza_rezultat)
{
  /*
  functie service pentru inmultire
  params: numar1 - un pointer catre un sir de caractere
          numar2 - un pointer catre un sir de caractere 
          rezultat - un pointer catre un sir de caractere 
          baza_numar1 - un intreg reprezentand baza numarului 1
          baza_numar2 - un intreg reprezentand baza numarului 2
          baza_rezultat - un intreg reprezentand baza numarului rezultat
  return: -
  */
  int len_numar1, len_numar2;
  len_numar1 = convert_service(numar1, baza_numar1, baza_rezultat);
  len_numar2 = convert_service(numar2, baza_numar2, baza_rezultat);

  int numar1_int[201], numar2_int[201], rezultat_int[201];
  memset(numar1_int, 0, sizeof(numar1_int));
  memset(numar2_int, 0, sizeof(numar2_int));
  memset(rezultat_int, 0, sizeof(rezultat_int));
  string_to_int(numar1, numar1_int);
  string_to_int(numar2, numar2_int);

  int len_rezultat = mul(numar1_int, numar2_int, rezultat_int, len_numar1, len_numar2, baza_rezultat);
  int_to_string(rezultat, rezultat_int, len_rezultat);
}

void service_sub(char *numar1, char *numar2, char *rezultat, int baza_numar1, int baza_numar2, int baza_rezultat)
{
  /*
  functie service pentru scadere
  params: numar1 - un pointer catre un sir de caractere
          numar2 - un pointer catre un sir de caractere 
          rezultat - un pointer catre un sir de caractere 
          baza_numar1 - un intreg reprezentand baza numarului 1
          baza_numar2 - un intreg reprezentand baza numarului 2
          baza_rezultat - un intreg reprezentand baza numarului rezultat
  return: -
  */
  int len_numar1, len_numar2;
  len_numar1 = convert_service(numar1, baza_numar1, baza_rezultat);
  len_numar2 = convert_service(numar2, baza_numar2, baza_rezultat);
  if(len_numar2 > len_numar1)
    {
      printf("Primul numar trebuie sa fie mai mare decat al doilea!\n");
      rezultat[0] = 0;
      return;
    }
  else if(len_numar2 == len_numar1)
  {
    for(int i = 0;i < len_numar1;++i)
      if(numar1[i] < numar2[i])
        {
          printf("Primul numar trebuie sa fie mai mare decat al doilea!\n");
          rezultat[0] = 0;
          return;
        }
  }
        

  int numar1_int[201], numar2_int[201], rezultat_int[201];
  memset(numar1_int, 0, sizeof(numar1_int));
  memset(numar2_int, 0, sizeof(numar2_int));
  memset(rezultat_int, 0, sizeof(rezultat_int));
  string_to_int(numar1, numar1_int);
  string_to_int(numar2, numar2_int);

  int len_rezultat = sub(numar1_int, numar2_int, rezultat_int, len_numar1, len_numar2, baza_rezultat);
  int_to_string(rezultat, rezultat_int, len_rezultat);
}

void service_add(char numar1[], char numar2[], char *rezultat, int baza_numar1, int baza_numar2, int baza_rezultat)
{
  /*
  functie service pentru adunare
  params: numar1 - un pointer catre un sir de caractere
          numar2 - un pointer catre un sir de caractere 
          rezultat - un pointer catre un sir de caractere 
          baza_numar1 - un intreg reprezentand baza numarului 1
          baza_numar2 - un intreg reprezentand baza numarului 2
          baza_rezultat - un intreg reprezentand baza numarului rezultat
  return: -
  */
  int len_numar1, len_numar2;
  len_numar1 = convert_service(numar1, baza_numar1, baza_rezultat);
  len_numar2 = convert_service(numar2, baza_numar2, baza_rezultat);

  int numar1_int[201], numar2_int[201], rezultat_int[201];
  memset(numar1_int, 0, sizeof(numar1_int));
  memset(numar2_int, 0, sizeof(numar2_int));
  memset(rezultat_int, 0, sizeof(rezultat_int));
  string_to_int(numar1, numar1_int);
  string_to_int(numar2, numar2_int);

  int len_rezultat = add(numar1_int, numar2_int, rezultat_int, len_numar1, len_numar2, baza_rezultat);
  int_to_string(rezultat, rezultat_int, len_rezultat);
}

void ui_operatii(char operatie)
{
  /*
  functie ui pentru operatii
  params: operatie - un caracter care codifica opeartia dorita
  */
  printf("%s\n", "baza numarului 1\nnumarul 1\nbaza numarului 2\nnumarul 2\nbaza rezultatului\n");
  int baza_numar1, baza_numar2, baza_rezultat, rest;
  char numar1[201], numar2[201], rezultat[10002];

  if(operatie != '+' && operatie != '-' && operatie != '*' && operatie != '/')
    {
      printf("Operatie invalida!\n");
      return;
    }

  scanf("%d", &baza_numar1);
  if(baza_numar1 < 2 || baza_numar1 > 36)
    {
      printf("Baza gresita! \n");
      return;
    }

  scanf("%200s", numar1);

  
  if(!verif_nr(baza_numar1, numar1))
  {
    printf("Numarul nu este in baza specificata! \n");
    return;
  }

  scanf("%d", &baza_numar2);
  if(baza_numar2 < 2 || baza_numar2 > 36)
    {
      printf("Baza gresita! \n");
      return;
    }

  scanf("%200s", numar2);
  
  if(!verif_nr(baza_numar2, numar2))
  {
    printf("Numarul nu este in baza specificata! \n");
    return;
  }

  scanf("%d", &baza_rezultat);
  if(baza_rezultat < 2 || baza_rezultat > 36)
    {
      printf("Baza gresita! \n");
      return;
    }


  switch(operatie)
    {
      case '+':
        service_add(numar1, numar2, rezultat, baza_numar1, baza_numar2, baza_rezultat);
        break;
      case '-':
        service_sub(numar1, numar2, rezultat, baza_numar1, baza_numar2, baza_rezultat);
        break;
      case '*':
        if(char_int(strlen(numar2)) / 10)
          {
            printf("Valoarea trebuie inmultita cu o cifra!\n");
            return;
          }
        service_mul(numar1, numar2, rezultat, baza_numar1, baza_numar2, baza_rezultat);
        break;
      case '/':
        if(char_int(strlen(numar2)) / 10)
          {
            printf("Valoarea trebuie inmultita cu o cifra!\n");
            return;
          }
        service_div(numar1, numar2, rezultat, baza_numar1, baza_numar2, baza_rezultat, &rest);
        break;
      default:
        printf("Operatie invalida!\n");
    }
  printf("%s ", rezultat);
  if(operatie == '/')
    printf("rest: %c", int_char(rest));
  printf("\n");
}

void ui()
{
  /*
  functia ui a aplicatiei
  */
  char operatie[10], end;
  printf("Zarzu Victor-Eugen\n");
  while(true)
  {
    printf("Baze - 2 - 36 \n");
    printf("exit - iesire\n");
    printf("%s\n", "convert - conversia unui numar dintr-o baza in alta");
    printf("%s\n", "+, -, *, / - adunare, scadere, inmultire, impartire");
    printf(">");
      
    scanf("%s", operatie);

    if(!strcmp(operatie, "exit")) return;

    if(!strcmp(operatie, "convert")) ui_convert();
    else if((strlen(operatie) == 1) && (operatie[0] == '+' || operatie[0] == '-' || operatie[0] == '*' || operatie[0] == '/')) ui_operatii(operatie[0]);
    else printf("Comanda invalida!\n");
  }
}

int main()
{
  run_all_tests();
  ui();
  return 0;
}

void test_convert()
{
  char numar[20] = "655488\0";
  char numar_convertit[] = "2400200";
  int baza_sursa = 10, baza_destinatie = 8;
  convert_service(numar, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit);++i)
    assert(numar[i] == numar_convertit[i]);
  
  char numar_convertit1[] = "655488\0";
  char numar1[] = "2400200";
  baza_sursa = 8, baza_destinatie = 10;
  convert_service(numar1, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit1);++i)
    assert(numar1[i] == numar_convertit1[i]);

  char numar3[] = "A\0";
  char numar_convertit3[] = "10";
  baza_sursa = 16, baza_destinatie = 10;
  convert_service(numar3, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit3);++i)
    assert(numar3[i] == numar_convertit3[i]);

}

void test_convert_power_2()
{
  char numar[20] = "BCF19\0";
  char numar_convertit[] = "10111100111100011001";
  int baza_sursa = 16, baza_destinatie = 2;
  convert_service(numar, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit);++i)
    assert(numar[i] == numar_convertit[i]);

  char numar1[20] = "23123\0";
  char numar_convertit1[] = "1333\0";
  baza_sursa = 4, baza_destinatie = 8;
  convert_service(numar1, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit1);++i)
    assert(numar1[i] == numar_convertit1[i]);

  char numar2[20] = "101010110111011101\0";
  char numar_convertit2[] = "2ADDD\0";
  baza_sursa = 2, baza_destinatie = 16;
  convert_service(numar2, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit2);++i)
    assert(numar2[i] == numar_convertit2[i]);

  char numar3[20] = "11001001\0";
  char numar_convertit3[] = "3021\0";
  baza_sursa = 2, baza_destinatie = 4;
  convert_service(numar3, baza_sursa, baza_destinatie);

  for(int i = 0;i < strlen(numar_convertit3);++i)
    assert(numar3[i] == numar_convertit3[i]);
}

void test_add()
{
  char numar1[] = "41351";
  char numar2[] = "EAE19BC";
  char rezultat[20];
  char rez[] = "246332227";
  int baza_numar1 = 10, baza_numar2 = 16, baza_rezultat = 10;

  service_add(numar1, numar2, rezultat, baza_numar1, baza_numar2, baza_rezultat);

  for(int i = 0;i < strlen(rez);++i)
    assert(rezultat[i] == rez[i]);
  
  char numar11[] = "452165";
  char numar22[] = "AA46912";
  char rez1[] = "129257B";
  baza_numar1 = 7, baza_numar2 = 11, baza_rezultat = 16;

  service_add(numar11, numar22, rezultat, baza_numar1, baza_numar2, baza_rezultat);

  for(int i = 0;i < strlen(rez1);++i)
    assert(rezultat[i] == rez1[i]);

  char numar111[10] = "AB45";
  char numar222[] = "452";
  char rez2[] = "22301233";
  baza_numar1 = 16, baza_numar2 = 8, baza_rezultat = 4;

  service_add(numar111, numar222, rezultat, baza_numar1, baza_numar2, baza_rezultat);
  //printf("\n%s rezultat", rezultat);

  for(int i = 0;i < strlen(rez1);++i)
    assert(rezultat[i] == rez2[i]);

}

void test_sub()
{
  char numar1[] = "574319";
  char numar2[] = "AB";
  char rezultat[10];
  char rez[] = "574148";
  int baza_numar1 = 10, baza_numar2 = 16, baza_rezultat = 10;

  service_sub(numar1, numar2, rezultat, baza_numar1, baza_numar2, baza_rezultat);

  for(int i = 0;i < strlen(rez);++i)
    assert(rezultat[i] == rez[i]);
  
  char numar11[] = "4521665";
  char numar22[] = "A9";
  char rez1[] = "88B7E";
  baza_numar1 = 7, baza_numar2 = 11, baza_rezultat = 16;

  service_sub(numar11, numar22, rezultat, baza_numar1, baza_numar2, baza_rezultat);

  for(int i = 0;i < strlen(rez1);++i)
    assert(rezultat[i] == rez1[i]);
}

void test_mul()
{
  char numar1[] = "574319";
  char numar2[] = "1";
  char rezultat[10];
  char rez[] = "574319";
  int baza_numar1 = 10, baza_numar2 = 10, baza_rezultat = 10;

  service_mul(numar1, numar2, rezultat, baza_numar1, baza_numar2, baza_rezultat);

  for(int i = 0;i < strlen(rez);++i)
    assert(rezultat[i] == rez[i]);
  
  char numar11[] = "56";
  char numar22[] = "3";
  char rez1[] = "153";
  baza_numar1 = 10, baza_numar2 = 7, baza_rezultat = 7;

  service_mul(numar11, numar22, rezultat, baza_numar1, baza_numar2, baza_rezultat);

  for(int i = 0;i < strlen(rez1);++i)
    assert(rezultat[i] == rez1[i]);
}

void test_div()
{
  char numar1[] = "AB5689";
  char numar2[] = "8";
  char rezultat[10];
  int baza_numar1 = 16, baza_numar2 = 10, baza_rezultat = 10, rest;

  service_div(numar1, numar2, rezultat, baza_numar1, baza_numar2, baza_rezultat, &rest);

  char rez[] = "1403601";
  for(int i = 0;i < strlen(rez);++i)
    assert(rezultat[i] == rez[i]);
  
  char numar11[] = "56";
  char numar22[] = "3";
  char rez1[] = "153";
  baza_numar1 = 10, baza_numar2 = 7, baza_rezultat = 7;

  service_mul(numar11, numar22, rezultat, baza_numar1, baza_numar2, baza_rezultat);

  for(int i = 0;i < strlen(rez1);++i)
    assert(rezultat[i] == rez1[i]);
}

void run_all_tests()
{
  test_convert();
  test_convert_power_2();
  test_add();
  test_div();
}
