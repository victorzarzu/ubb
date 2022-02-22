#include <stdio.h>

static void PrintareHelloWorld()
{
    printf("Hello World\n");
}

static void CalculareSuma()
{
    int* n = (int*)malloc(sizeof(int));
    if (n == NULL)
    {
        return 0;
    }

    int* number = (int*)malloc(sizeof(int));
    if (number == NULL)
    {
        return 0;
    }
    int* sum = (int*)malloc(sizeof(int));
    if (sum == NULL)
    {
        return 0;
    }
    *sum = 0;

    scanf_s("%d", n);

    for (int i = 0; i < *n; ++i)
    {
        scanf_s("%d", number);
        *sum += *number;
    }

    printf("%d", *sum);

    free(n);
    free(number);
    free(sum);
}

int main()
{
    PrintareHelloWorld();
    CalculareSuma();
    return 0;
}