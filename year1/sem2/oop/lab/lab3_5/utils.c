#include "utils.h"

int isInteger(char* text)
{
    if (text == NULL)
    {
        return -1;
    }

    for (int i = 0; i < (int)strlen(text); ++i)
    {
        if (strchr("0123456789", text[i]) == NULL)
        {
            return 0;
        }
    }

    return 1;
}

int isDouble(char* text)
{
    if (text == NULL)
    {
        return -1;
    }

    int pointFound = 0;

    for (int i = 0; i < (int)strlen(text); ++i)
    {
        if (!pointFound && strchr(".", text[i]) != NULL)
        {
            pointFound ^= 1;
        }
        else if (strchr("0123456789", text[i]) == NULL)
        {
            return 0;
        }
    }

    return 1;
}

int compareZi(PTRANZACTIE t1, PTRANZACTIE t2) { 
    if (GetZi(t1) == GetZi(t2))
    {
        return 0;}
    else if (GetZi(t1) < GetZi(t2))
    {
        return 1;
    }
    return -1;
}

int compareSuma(PTRANZACTIE t1, PTRANZACTIE t2) { 
    if (fabs(GetSuma(t1) - GetSuma(t2)) <= epsilon)
    {
        return 0;}
    else if (GetSuma(t1) < GetSuma(t2))
    {
        return 1;
    }
    return -1;
}

int ascendingMode(int result) { return result; }

int descendingMode(int result) { 
    if (!result)
    {
        return 0;
    }
    if (result == 1)
    {
        return -1;
    }
    return 1;
}

int isType(PTRANZACTIE t, int Tip) {
    return t->Tip == Tip;
}
int isDay(PTRANZACTIE t, int Zi) {
    return t->Zi == Zi;
}
int biggerSum(PTRANZACTIE t, double Suma) {
    return t->Suma > Suma;
}
int smallerSum(PTRANZACTIE t, double Suma) {
    return t->Suma < Suma;
}

void BubbleSort(PMY_LIST List, CompareFunction cmpF, AscendingMode ascF)
{
    int length = GetLength(List);
    int change = 1;
    while (change == 1)
    {
        change = 0;
        for (int i = 0; i < length - 1; ++i)
        {
            ElemType Tranzactie1 = GetElement(List, i);
            ElemType Tranzactie2 = GetElement(List, i + 1);
            if (ascF(cmpF(Tranzactie1, Tranzactie2)) == -1)
            {
                SetElement(List, i, Tranzactie2);
                SetElement(List, i + 1, Tranzactie1);
                change = 1;
            }
        }
    }
}

void SelectionSort(PMY_LIST List, CompareFunction cmpF, AscendingMode ascF)
{
    int length = GetLength(List);
    for (int i = 0; i < length; ++i)
        for (int j = i + 1; j < length; ++j)
        {
            ElemType Tranzactie1 = GetElement(List, i);
            ElemType Tranzactie2 = GetElement(List, i + 1);
            if (ascF(cmpF(Tranzactie1, Tranzactie2)) == -1)
            {
                SetElement(List, i, Tranzactie2);
                SetElement(List, i + 1, Tranzactie1);
            }
        }
}

static void testFunctions()
{
    char* text = "123";
    assert(isInteger(text) == 1);

    text = "123.12";
    assert(isInteger(text) == 0);

    text = "text";
    assert(isInteger(text) == 0);

    text = "123";
    assert(isDouble(text) == 1);

    text = "123.12";
    assert(isDouble(text) == 1);

    text = "123.12.1";
    assert(isDouble(text) == 0);

    text = "text";
    assert(isDouble(text) == 0);

    assert(isInteger(NULL) == -1);
    assert(isDouble(NULL) == -1);

    ElemType Tranzactie = CreateTranzactie(6, 5, 198, 0, "ceva");
    assert(isType(Tranzactie, 0) == 1);
    assert(isType(Tranzactie, 1) == 0);

    assert(smallerSum(Tranzactie, 260) == 1);
    assert(smallerSum(Tranzactie, 167) == 0);

    assert(biggerSum(Tranzactie, 260) == 0);
    assert(biggerSum(Tranzactie, 167) == 1);

    ElemType TranzactieNoua = CreateTranzactie(6, 7, 198, 0, "ceva");
    assert(compareZi(Tranzactie, TranzactieNoua) == 1);
    assert(compareSuma(Tranzactie, TranzactieNoua) == 0);

    DestroyTranzactie(TranzactieNoua);
    DestroyTranzactie(Tranzactie);
}

static void testSort()
{
    MY_LIST* Array = CreateList();
    ElemType Tranzactie;
    Tranzactie = CreateTranzactie(6, 5, 198, 0, "ceva");
    Insert(Array, Tranzactie);

    ElemType Tranzactie1;
    Tranzactie1 = CreateTranzactie(7, 7, 178, 0, "ceva");
    Insert(Array, Tranzactie1);
    assert(GetLength(Array) == 2);

    BubbleSort(Array, compareZi, ascendingMode);
    assert(GetId(GetElement(Array, 0)) == 6);
    assert(GetId(GetElement(Array, 1)) == 7);

    BubbleSort(Array, compareZi, descendingMode);
    assert(GetId(GetElement(Array, 1)) == 6);
    assert(GetId(GetElement(Array, 0)) == 7);

    BubbleSort(Array, compareSuma, ascendingMode);
    assert(GetId(GetElement(Array, 0)) == 7);
    assert(GetId(GetElement(Array, 1)) == 6);

    BubbleSort(Array, compareSuma, descendingMode);
    assert(GetId(GetElement(Array, 1)) == 7);
    assert(GetId(GetElement(Array, 0)) == 6);

    SelectionSort(Array, compareZi, ascendingMode);
    assert(GetId(GetElement(Array, 0)) == 6);
    assert(GetId(GetElement(Array, 1)) == 7);

    SelectionSort(Array, compareZi, descendingMode);
    assert(GetId(GetElement(Array, 1)) == 6);
    assert(GetId(GetElement(Array, 0)) == 7);

    SelectionSort(Array, compareSuma, ascendingMode);
    assert(GetId(GetElement(Array, 0)) == 7);
    assert(GetId(GetElement(Array, 1)) == 6);

    SelectionSort(Array, compareSuma, descendingMode);
    assert(GetId(GetElement(Array, 1)) == 7);
    assert(GetId(GetElement(Array, 0)) == 6);

    ElemType Tranzactie2;
    Tranzactie2 = CreateTranzactie(9, 7, 178, 0, "ceva");
    Insert(Array, Tranzactie2);

    BubbleSort(Array, compareSuma, ascendingMode);
    assert(GetId(GetElement(Array, 0)) == 7);
    assert(GetId(GetElement(Array, 1)) == 9);
    assert(GetId(GetElement(Array, 2)) == 6);

    BubbleSort(Array, compareSuma, descendingMode);
    assert(GetId(GetElement(Array, 2)) == 9);
    assert(GetId(GetElement(Array, 1)) == 7);
    assert(GetId(GetElement(Array, 0)) == 6);

    BubbleSort(Array, compareZi, ascendingMode);
    assert(GetId(GetElement(Array, 0)) == 6);
    assert(GetId(GetElement(Array, 1)) == 7);
    assert(GetId(GetElement(Array, 2)) == 9);

    Destroy(Array, DestroyTranzactie);
}

void testUtils()
{
    testSort();
    testFunctions();
}