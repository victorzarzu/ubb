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
}