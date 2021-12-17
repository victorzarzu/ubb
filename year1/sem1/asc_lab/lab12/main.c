#include <stdio.h>
#include <string.h>

char * base2_to_integer(int, char *, char *);

int main()
{
    int n;
    scanf("%d", &n);
    
    char *number2 = (char*)malloc(301);
    char *number8 = (char*)malloc(101);
    if(number2 == NULL || number8 == NULL)
        return 0;
    
    for(int i = 1;i <= n;++i)
    {
        scanf("%s", number2);
        printf("%s\n", base2_to_integer(strlen(number2), number2, number8));
    }
    
    free(number2);
    free(number8);
    
    return 0;
}