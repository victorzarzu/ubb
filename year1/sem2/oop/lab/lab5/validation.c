#include "validation.h"

int ValidateTranzactie(TRANZACTIE* Tranzactie, char* errors)
{
    errors[0] = '\0';
    if (GetId(Tranzactie) < 0)
    {
        strcat(errors, "Invalid id!\n");
    }
    if (GetZi(Tranzactie) <= 0 || GetZi(Tranzactie) > 31)
    {
        strcat(errors, "Invalid day!\n");
    }
    if (GetSuma(Tranzactie) <= 0)
    {
        strcat(errors, "Invalid sum!\n");
    }
    if (GetTip(Tranzactie) != 0 && GetTip(Tranzactie) != 1)
    {
        strcat(errors, "Invalid type!\n");
    }
    if (strlen(GetDescriere(Tranzactie)) == 0)
    {
        strcat(errors, "Invalid description!\n");
    }


    if (strlen(errors) > 0)
    {
        return -1;
    }

    return 0;
}