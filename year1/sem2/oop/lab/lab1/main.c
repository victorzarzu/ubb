#include <stdio.h>

void ui();
void Goldbach(int, int*, int*);
int isPrime(int);
int GetNextPrime(int);
int GetPreviousPrime(int);

int main()
{
    ui();
    return 0;
}

void ui()
{
    /**
    * Function for UI
    */

    printf("1 - Goldbach\n0 - Exit\n");

    int cmd;
    while (1)
    {
        scanf_s("%d", &cmd);

        if (cmd == 1)
        {
            int n;
            scanf_s("%d", &n);

            if (n % 2)
            {
                printf("The number is not even!\n");
                continue;
            }
            else if (n <= 2)
            {
                printf("The number needs to be strictly greater than 2!\n");
                continue;
            }

            int number1, number2;
            Goldbach(n, &number1, &number2);

            printf("The searched numbers are %d and %d\n", number1, number2);
        }
        else if (cmd == 0)
        {
            break;
        }
        else
        {
            printf("Invalid command\n");
        }
    }
}

int isPrime(int n)
{
    /**
    * Function that checks if the number given as parameter is prime
    *
    * @param n - integer
    *
    * @result - 1 - if n is prime
    *           0 - otherwise
    */

    if (n < 2) return 0;
    if (n == 2) return 1;
    if (!(n % 2)) return 0;

    int d = 3;
    while (d * d <= n)
    {
        if (!(n % d))
            return 0;
        d += 2;
    }

    return 1;
}

int GetNextPrime(int n)
{
    /**
    * Function that returns the first number greater than n that is prime
    *
    * @param n - integer number
    *
    * @return - integer that represents the first number prime greater than n
    */

    while (isPrime(n) == 0)
        n++;

    return n;
}

int GetPreviousPrime(int n)
{
    /**
    * Function that returns the first number smaller than n that is prime
    *
    * @param n - integer number
    *
    * @return - integer that represents the first number prime smaller than n
    */

    while (isPrime(n) == 0)
        n--;

    return n;
}

void Goldbach(int n, int* number1, int* number2)
{
    /**
    * Function that determines two prime numbers that sum up to n
    *
    * @params: n - integer
    *          number1 - pointer to integer
    *          number2 - pointer to integer
    *
    * @return - 2 integer numbers through number1 and number2 pointers that sum up to n
    */
    *number1 = *number2 = n / 2;

    *number1 = GetPreviousPrime(*number1);
    *number2 = GetNextPrime(*number2);

    while (*number1 + *number2 != n)
    {
        int sum = *number1 + *number2;

        if (sum < n)
        {
            (*number1)++;
            *number1 = GetNextPrime(*number1);
        }
        else
        {
            (*number2)--;
            *number2 = GetPreviousPrime(*number2);
        }
    }
}