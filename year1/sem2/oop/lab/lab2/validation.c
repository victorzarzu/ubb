#include "validation.h"

int ValidateProdus(PRODUS Produs, char* errors)
{
    errors[0] = '\0';
    if (GetId(Produs) < 0)
    {
        strcat(errors, "Invalid id!\n");
    }

    int lenTip = strlen(GetTip(Produs));
    if (lenTip == 0)
    {
        printf("%s\n", GetTip(Produs));
        strcat(errors, "Invalid type!\n");
    }

    int lenProducator = strlen(GetProducator(Produs));
    if (lenProducator == 0)
    {
        strcat(errors, "Invalid manufacturer!\n");
    }

    int lenModel = strlen(GetModel(Produs));
    if (lenModel == 0)
    {
        strcat(errors, "Invalid model!\n");
    }
    if (GetPret(Produs) <= 0)
    {
        strcat(errors, "Invalid price!\n");
    }
    if (GetCantitate(Produs) < 0)
    {
        strcat(errors, "Invalid quantity!\n");
    }


    if (strlen(errors) > 0)
    {
        return -1;
    }

    return 0;
}