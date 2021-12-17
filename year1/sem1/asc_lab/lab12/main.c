#include <stdio.h>
#include <string.h>

int base2_to_integer(int);

int main()
{
    int n;
    scanf("%d", &n);
    
    char *number = (char*)malloc(33);
    if(number == NULL)
        return 0;
    
    for(int i = 1;i <= n;++i)
    {
        scanf("%s", number);
        printf("%d\n", base2_to_integer(strlen(number), number));
    }
    
    free(number);
    
    return 0;
}