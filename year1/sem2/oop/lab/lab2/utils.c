#include "utils.h"

int isInteger(char* text)
{
    if (text == NULL)
    {
        return -1;
    }

    for (int i = 0; i < strlen(text); ++i)
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

    for (int i = 0; i < strlen(text); ++i)
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

void BubbleSort(PPRODUS Array, CompareFunction cmpF, int length)
{
    int change = 1;
    while (change == 1)
    {
        change = 0;
        for (int i = 0; i < length - 1; ++i)
        {
            PRODUS Produs1 = Array[i];
            PRODUS Produs2 = Array[i + 1];
            if (cmpF(&Produs1, &Produs2) > 0)
            {
                Array[i] = Produs2;
                Array[i + 1] = Produs1;
                change = 1;
            }
        }
    }
}

void SelectionSort(PPRODUS Array, CompareFunction cmpF, int length)
{
    for(int i = 0;i < length;++i)
        for (int j = i + 1; j < length; ++j)
        {
            PRODUS Produs1 = Array[i];
            PRODUS Produs2 = Array[j];
            if (cmpF(&Produs1, &Produs2) > 0)
            {
                Array[i] = Produs2;
                Array[j] = Produs1;
            }
        }
}

void testUtils()
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

    PPRODUS Array = (PPRODUS)malloc(10 * sizeof(PRODUS));
    PPRODUS Produs;
    CreateProdus(&Produs, 6, "ceva", "ceva", "altceva", 5, 10);
    Array[0] = *Produs;

    PPRODUS Produs1;
    CreateProdus(&Produs1, 6, "ceva", "ceva", "altceva", 5, 11);
    Array[1] = *Produs1;

    BubbleSort(Array, CompareProduseIncreasing, 2);
    assert(GetCantitate(Array[0]) == 10);
    assert(GetCantitate(Array[1]) == 11);

    BubbleSort(Array, CompareProduseDecreasing, 2);
    assert(GetCantitate(Array[0]) == 11);
    assert(GetCantitate(Array[1]) == 10);

    SelectionSort(Array, CompareProduseIncreasing, 2);
    assert(GetCantitate(Array[0]) == 10);
    assert(GetCantitate(Array[1]) == 11);

    SelectionSort(Array, CompareProduseDecreasing, 2);
    assert(GetCantitate(Array[0]) == 11);
    assert(GetCantitate(Array[1]) == 10);

    DestroyProdus(&Produs);
    DestroyProdus(&Produs1);
    free(Array);
}