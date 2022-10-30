#define _CRT_SECURE_NO_WARNINGS
#include "domain.h"
#include "validation.h"

static int compareIncresingInt(int a, int b) {
    return a < b;
};
static int compareDecreasingInt(int a, int b) {
    return a > b;
};
static int compareIncresingDouble(double a, double b) {
    return a < b;
};
static int compareDecreasingDouble(double a, double b) {
    return a > b;
};

int GetId(PTRANZACTIE Tranzactie)
{
    return Tranzactie->Id;
}

void SetId(PTRANZACTIE Tranzactie, int Id)
{
    Tranzactie->Id = Id;
}

int GetTip(PTRANZACTIE Tranzactie)
{
    return Tranzactie->Tip;
}

void SetTip(PTRANZACTIE Tranzactie, int Tip)
{
    Tranzactie->Tip = Tip;
}

int GetZi(PTRANZACTIE Tranzactie)
{
    return Tranzactie->Zi;
}

void SetZi(PTRANZACTIE Tranzactie, int Zi)
{
    Tranzactie->Zi = Zi;
}

double GetSuma(PTRANZACTIE Tranzactie)
{
    return Tranzactie->Suma;
}

void SetSuma(PTRANZACTIE Tranzactie, double Suma)
{
    Tranzactie->Suma = Suma;
}

char* GetDescriere(PTRANZACTIE Tranzactie)
{
    return Tranzactie->Descriere;
}

void SetDescriere(PTRANZACTIE Tranzactie, char* Descriere)
{
    int lenDescriere = strlen(Descriere) + 1;
    char* newDescriere = (char*)malloc(lenDescriere * sizeof(char));
    /*if (newModel == NULL)
    {
        return;
    }*/
    strcpy(newDescriere, Descriere);

    free(Tranzactie->Descriere);
    Tranzactie->Descriere = newDescriere;
}

/*int PrintFormat(TRANZACTIE TRANZACTIE)
{
    printf("Tip: %s\nProducator: %s\nModel: %s\nPret: %f\nCantitate: %d\n\n", TRANZACTIE.Tip, TRANZACTIE.Producator, TRANZACTIE.Model, TRANZACTIE.Pret, TRANZACTIE.Cantitate);
}*/

int TranzactieEqual(PTRANZACTIE Tranzactie1, PTRANZACTIE Tranzactie2)
{
    if (Tranzactie1->Id != Tranzactie2->Id)
    {
        return 0;
    }
    if (Tranzactie1->Zi != Tranzactie2->Zi)
    {
        return 0;
    }
    if (fabs(Tranzactie1->Suma - Tranzactie2->Suma) > epsilon)
    {
        return 0;
    }
    if (Tranzactie1->Tip != Tranzactie2->Tip)
    {
        return 0;
    }
    if (strcmp(Tranzactie1->Descriere, Tranzactie2->Descriere) != 0)
    {
        return 0;
    }

    return 1;
}

int CompareTranzactieZi(const PTRANZACTIE Tranzactie1, const PTRANZACTIE Tranzactie2, comparerInt comparer)
{
    return comparer(Tranzactie1->Zi, Tranzactie2->Zi);
}

int CompareTranzactieSuma(const PTRANZACTIE Tranzactie1, const PTRANZACTIE Tranzactie2, comparerDouble comparer)
{
    return comparer(Tranzactie1->Suma, Tranzactie2->Suma);
}

TRANZACTIE* CreateTranzactie(int Id, int Zi, double Suma, int Tip, char* Descriere)
{
    TRANZACTIE* Tranzactie = malloc(sizeof(TRANZACTIE));

    Tranzactie->Id = Id;
    Tranzactie->Zi = Zi;
    Tranzactie->Suma = Suma;
    Tranzactie->Tip = Tip;

    int descriereLength = strlen(Descriere);
    char* descriere = (char*)malloc(sizeof(char) * (descriereLength + 1));
    strcpy(descriere, Descriere);
    Tranzactie->Descriere = descriere;

    return Tranzactie;
}

TRANZACTIE* CopyTranzactie(PTRANZACTIE Tranzactie)
{
    return CreateTranzactie(Tranzactie->Id, Tranzactie->Zi, Tranzactie->Suma, Tranzactie->Tip, Tranzactie->Descriere);
}

void DestroyTranzactie(PTRANZACTIE Tranzactie)
{
    free(Tranzactie->Descriere);
    free(Tranzactie);
}

static void testCreateAndDestroy(void)
{
    TRANZACTIE* Tranzactie;
    Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(Tranzactie->Id == 6);
    assert(Tranzactie->Zi == 16);
    assert(fabs(Tranzactie->Suma - 15.76) <= epsilon);
    assert(Tranzactie->Tip == 0);
    assert(strcmp(Tranzactie->Descriere, "ceva") == 0);

    DestroyTranzactie(Tranzactie);
}

static void testGetAndSet(void)
{
    TRANZACTIE* Tranzactie;
    Tranzactie = Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    SetId(Tranzactie, 6);
    assert(GetId(Tranzactie) == 6);

    SetZi(Tranzactie, 17);
    assert(GetZi(Tranzactie) == 17);

    SetSuma(Tranzactie, 156.98);
    assert(fabs(GetSuma(Tranzactie) - 156.98) <= epsilon);

    SetTip(Tranzactie, 1);
    assert(GetTip(Tranzactie) == 1);

    SetDescriere(Tranzactie, "altceva");
    assert(strcmp(GetDescriere(Tranzactie), "altceva") == 0);

    TRANZACTIE* TranzactieCreata;
    TranzactieCreata = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(GetId(Tranzactie) == 6);
    assert(GetZi(Tranzactie) == 17);
    assert(fabs(GetSuma(Tranzactie) - 156.98) <= epsilon);
    assert(GetTip(Tranzactie) == 1);
    assert(strcmp(GetDescriere(Tranzactie), "altceva") == 0);

    DestroyTranzactie(TranzactieCreata);

    DestroyTranzactie(Tranzactie);
}

static void testCompare(void)
{
    TRANZACTIE* Tranzactie;
    Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");

    TRANZACTIE* TranzactieIdentic = CopyTranzactie(Tranzactie);
    assert(TranzactieEqual(Tranzactie, TranzactieIdentic) == 1);

    TRANZACTIE* TranzactieDiferit;
    TranzactieDiferit = CreateTranzactie(7, 16, 15.76, 0, "ceva");
    assert(TranzactieEqual(Tranzactie, TranzactieDiferit) == 0);
    DestroyTranzactie(TranzactieDiferit);

    TranzactieDiferit = CreateTranzactie(6, 15, 15.76, 0, "ceva");
    assert(TranzactieEqual(Tranzactie, TranzactieDiferit) == 0);
    DestroyTranzactie(TranzactieDiferit);

    TranzactieDiferit = CreateTranzactie(6, 16, 7, 0, "ceva");
    assert(TranzactieEqual(Tranzactie, TranzactieDiferit) == 0);
    DestroyTranzactie(TranzactieDiferit);

    TranzactieDiferit = CreateTranzactie(6, 16, 15.76, 1, "ceva");
    assert(TranzactieEqual(Tranzactie, TranzactieDiferit) == 0);
    DestroyTranzactie(TranzactieDiferit);

    TranzactieDiferit = CreateTranzactie(6, 16, 15.76, 0, "altceva");
    assert(TranzactieEqual(Tranzactie, TranzactieDiferit) == 0);
    DestroyTranzactie(TranzactieDiferit);

    TranzactieDiferit = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    SetZi(TranzactieDiferit, 8);
    assert(CompareTranzactieZi(Tranzactie, TranzactieDiferit, compareIncresingInt) == 0);
    assert(CompareTranzactieZi(TranzactieDiferit, Tranzactie, compareIncresingInt) == 1);
    assert(CompareTranzactieZi(Tranzactie, TranzactieDiferit, compareDecreasingInt) == 1);
    assert(CompareTranzactieZi(TranzactieDiferit, Tranzactie, compareDecreasingInt) == 0);

    SetSuma(TranzactieDiferit, 15.77);
    assert(CompareTranzactieSuma(Tranzactie, TranzactieDiferit, compareIncresingDouble) == 1);
    assert(CompareTranzactieSuma(TranzactieDiferit, Tranzactie, compareIncresingDouble) == 0);
    assert(CompareTranzactieSuma(Tranzactie, TranzactieDiferit, compareDecreasingDouble) == 0);
    assert(CompareTranzactieSuma(TranzactieDiferit, Tranzactie, compareDecreasingDouble) == 1);

    TRANZACTIE* Copy = CopyTranzactie(Tranzactie);
    assert(TranzactieEqual(Tranzactie, Copy) == 1);

    DestroyTranzactie(Tranzactie);
    DestroyTranzactie(Copy);
    DestroyTranzactie(TranzactieIdentic);
    DestroyTranzactie(TranzactieDiferit);
}

static void testValidate(void)
{
    TRANZACTIE* Tranzactie;
    Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    char* errors = malloc(100 * sizeof(char));
    errors[0] = '\0';

    assert(ValidateTranzactie(Tranzactie, errors) == 0);

    TRANZACTIE* TranzactieInvalida;
    TranzactieInvalida = CreateTranzactie(-1, 16, 15.76, 0, "");

    assert(ValidateTranzactie(TranzactieInvalida, errors) == -1);
    assert(strcmp(errors, "Invalid id!\nInvalid description!\n") == 0);
    DestroyTranzactie(TranzactieInvalida);

    TranzactieInvalida = CreateTranzactie(-1, -5, 0, -5, "");
    assert(ValidateTranzactie(TranzactieInvalida, errors) == -1);
    assert(strcmp(errors, "Invalid id!\nInvalid day!\nInvalid sum!\nInvalid type!\nInvalid description!\n") == 0);

    DestroyTranzactie(Tranzactie);
    DestroyTranzactie(TranzactieInvalida);

    free(errors);
}

void testDomain(void)
{
    testCreateAndDestroy();
    testGetAndSet();
    testCompare();
    testValidate();
}