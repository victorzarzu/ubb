#include "service.h"

int CreateService(PSERVICE_PRODUCTS* Service, PREPOSITORY_PRODUSE Repository, ValidationFunction Validation)
{
    if (Service == NULL || Repository == NULL || Validation == NULL )
    {
        return -1;
    }

    PSERVICE_PRODUCTS service = (PSERVICE_PRODUCTS)malloc(sizeof(SERVICE_PRODUCTS));
    if (service == NULL)
    {
        return -1;
    }

    service->Repository = Repository;
    service->ValidateProduct = Validation;

    *Service = service;

    return 0;
}

int StoreProdus(PSERVICE_PRODUCTS Service, int Id, char* Tip, char* Producator, char* Model, double Pret, int Cantitate, char* errors)
{
    if(Service == NULL || errors == NULL)
    {
        return -1;
    }

    errors[0] = NULL;
    PPRODUS Produs;
    if (CreateProdus(&Produs, Id, Tip, Producator, Model, Pret, Cantitate) != 0)
    {
        strcat(errors, "Could not create a product!\n");
        return -1;
    }

    if (Service->ValidateProduct(*Produs, errors) != 0)
    {
        free(Produs);
        return -1;
    }
    if (InsertProdus(Service->Repository, Produs) != 0)
    {
        free(Produs);
        strcat(errors, "The product with this id already exists!\n");
        return -1;
    }

    return 0;
}

int EraseProdus(PSERVICE_PRODUCTS Service, int Id, char* errors)
{
    if (Service == NULL || errors == NULL)
    {
        return -1;
    }
    errors[0] = NULL;

    if (DeleteProdus(Service->Repository, Id) != 0)
    {
        strcat(errors, "The product does not exist!\n");
        return -1;
    }

    return 0;
}

int ChangeProdus(PSERVICE_PRODUCTS Service, int Id, double Pret, int Cantitate, char* errors)
{
    if (Service == NULL || errors == NULL)
    {
        return -1;
    }
    errors[0] = NULL;

    PPRODUS Produs = (PPRODUS)malloc(sizeof(PRODUS));
    if (Produs == NULL)
    {
        strcat(errors, "Modification failed!\n");
        return -1;
    }
    if (SearchProdus(Service->Repository, Id, Produs) != 0)
    {
        strcat(errors, "The product does not exist!\n");
        return -1;
    }

    if (Cantitate != -oo)
    {
        SetCantitate(Produs, Cantitate);
    }
    else
    {
        Cantitate = GetCantitate(*Produs);
    }

    if (Pret != -oo)
    {
        SetPret(Produs, Pret);
    }
    else
    {
        Pret = GetPret(*Produs);
    }

    if (Service->ValidateProduct(*Produs, errors) != 0)
    {
        return -1;
    }

    if (ModifyProdus(Service->Repository, Id, Pret, Cantitate) != 0)
    {
        strcat(errors, "The modification failed!\n");
        return -1;
    }

    return 0;
}

int ViewProduse(PSERVICE_PRODUCTS Service, int Mode, PPRODUS* Array, char* errors)
{
    if (Service == NULL || Array == NULL || errors == NULL)
    {
        strcat(errors, "Viewing failed!\n");
        return -1;
    }
    errors[0] = NULL;

    if (GetLength(Service->Repository) == 0)
    {
        strcat(errors, "There are no products!\n");
        return -1;
    }

    PPRODUS array = (PPRODUS)malloc(Service->Repository->Count * sizeof(PRODUS));
    if (array == NULL)
    {
        strcat(errors, "Viewing failed!\n");
        return -1;
    }

    *Array = array;
    if (GetAll(Service->Repository, Array) != 0)
    {
        return -1;
    }

    if (Mode == 0)
    {
        qsort(*Array, Service->Repository->Count, sizeof(PRODUS), CompareProduseIncreasing);
    }
    else
    {
        qsort(*Array, Service->Repository->Count, sizeof(PRODUS), CompareProduseDecreasing);
    }

    return 0;
}

int FilterProduse(PSERVICE_PRODUCTS Service, char* Producator, double Pret, int Cantitate, PPRODUS* Array, int* Number, char* errors)
{
    if (Service == NULL || Array == NULL || errors == NULL)
    {
        return -1;
    }
    errors[0] = NULL;

    if (GetLength(Service->Repository) == 0)
    {
        strcat(errors, "There are no products!\n");
        return -1;
    }

    PPRODUS array = (PPRODUS)malloc(Service->Repository->Count * sizeof(PRODUS));
    if (array == NULL)
    {
        strcat(errors, "Viewing failed!\n");
        return -1;
    }

    if (GetAll(Service->Repository, &array) != 0)
    {
        return -1;
    }

    PPRODUS arrayFilter = (PPRODUS)malloc(Service->Repository->Count * sizeof(PRODUS));
    if (arrayFilter == NULL)
    {
        free(array);
        strcat(errors, "Viewing failed!\n");
        return -1;
    }

    *Number = 0;
    int count = GetLength(Service->Repository);
    for (int i = 0; i < count; ++i)
    {
        PRODUS Produs;
        int length = strlen(GetProducator(array[i]));
        char* producatorHere = (char*)malloc(sizeof(char) * (length + 1));
        if (producatorHere == NULL)
        {
            free(array);
            free(arrayFilter);
            strcat(errors, "Viewing failed!\n");
            return -1;
        }

        strcpy(producatorHere, Producator);
        double pretHere = Pret;
        int cantitateHere = Cantitate;

        if (strcmp(Producator, "-1") == 0)
        {
            char* producator = GetProducator(array[i]);
            strcpy(producatorHere, producator);
        }
        if (fabs(Pret + 1) <= epsilon)
        {
            pretHere = GetPret(array[i]);
        }
        if (Cantitate == -1)
        {
            cantitateHere = GetCantitate(array[i]);
        }

        char* producator = GetProducator(array[i]);
        double pret = GetPret(array[i]);
        int cantitate = GetCantitate(array[i]);

        if (strcmp(producator, producatorHere) == 0 && fabs(pret - pretHere) <= epsilon && cantitate == cantitateHere)
        {
            arrayFilter[*Number] = array[i];
            *Number = *Number + 1;
        }

        //free(producatorHere);
    }

    
    free(array);
    *Array = arrayFilter;

    if (*Number == 0)
    {
        free(*Array);
        strcat(errors, "There are no products!\n");
        return -1;
    }

    return 0;
}

int DestroyService(PSERVICE_PRODUCTS* Service)
{
    if (Service == NULL)
    {
        return -1;
    }

    if (DestroyRepository(&((*Service)->Repository)) != 0)
    {
        return -1;
    }
    
    free(*Service);

    return 0;
}

void testService()
{
    PSERVICE_PRODUCTS Service = (PSERVICE_PRODUCTS)malloc(sizeof(SERVICE_PRODUCTS));
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateProdus;
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);

    PPRODUS Result = NULL;
    assert(CreateProdus(&Result, 0, "", "", "", 0, 0) == 0);

    assert(CreateService(NULL, Repo, validate) == -1);
    assert(CreateService(&Service, NULL, validate) == -1);
    assert(CreateService(&Service, Repo, NULL) == -1);
    assert(CreateService(NULL, NULL, NULL) == -1);

    assert(CreateService(&Service, Repo, validate) == 0);
    assert(StoreProdus(Service, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10, errors) == 0);
    assert(GetLength(Service->Repository) == 1);

    assert(StoreProdus(Service, 6, "", "Lenovo", "IE 652", 3299.99, -10, errors) == -1);
    assert(strcmp(errors, "Invalid type!\nInvalid quantity!\n") == 0);

    assert(StoreProdus(Service, 3, "televizor", "Samsung", "Wow", 3299.99, 10, errors) == 0);
    assert(GetLength(Service->Repository) == 2);

    assert(StoreProdus(Service, 3, "haha", "nana", "Wow", 3299.99, 10, errors) == -1);
    assert(strcmp(errors, "The product with this id already exists!\n") == 0);

    assert(StoreProdus(NULL, 3, "haha", "nana", "Wow", 3299.99, 10, errors) == -1);
    assert(StoreProdus(Service, 3, "haha", "nana", "Wow", 3299.99, 10, NULL) == -1);
    assert(StoreProdus(NULL, 3, "haha", "nana", "Wow", 3299.99, 10, NULL) == -1);

    assert(EraseProdus(Service, 3, errors) == 0);
    assert(GetLength(Service->Repository) == 1);

    assert(EraseProdus(Service, 3, errors) == -1);
    assert(strcmp(errors, "The product does not exist!\n") == 0);

    assert(EraseProdus(NULL, 3, errors) == -1);
    assert(EraseProdus(Service, 3, NULL) == -1);
    assert(EraseProdus(NULL, 3, NULL) == -1);

    assert(ChangeProdus(Service, 6, 2999.99, 5, errors) == 0);
    assert(SearchProdus(Service->Repository, 6, Result) == 0);
    assert(fabs(GetPret(*Result) - 2999.99) <= epsilon);
    assert(GetCantitate(*Result) == 5);

    assert(ChangeProdus(Service, 6, -6, -1, errors) == -1);
    assert(strcmp(errors, "Invalid price!\nInvalid quantity!\n") == 0);

    assert(ChangeProdus(Service, 2, 2999.99, 5, errors) == -1);
    assert(strcmp(errors, "The product does not exist!\n") == 0);

    assert(ChangeProdus(NULL, 2, 2999.99, 5, errors) == -1);
    assert(ChangeProdus(Service, 2, 2999.99, 5, NULL) == -1);
    assert(ChangeProdus(NULL, 2, 2999.99, 5, NULL) == -1);

    assert(GetLength(Service->Repository) == 1);
    for (int i = 15; i < 25; ++i)
    {
        assert(StoreProdus(Service, i, "televizor", "Samsung", "IE 652", i * 10, i, errors) == 0);
    }

    PPRODUS Array = NULL;

    assert(ViewProduse(Service, 0, &Array, errors) == 0);
    assert(fabs(GetPret(Array[0]) - 150) <= epsilon);
    assert(fabs(GetPret(Array[1]) - 160) <= epsilon);
    assert(fabs(GetPret(Array[10]) - 2999.99) <= epsilon);

    assert(ViewProduse(Service, 1, &Array, errors) == 0);
    assert(fabs(GetPret(Array[10]) - 150) <= epsilon);
    assert(fabs(GetPret(Array[9]) - 160) <= epsilon);
    assert(fabs(GetPret(Array[0]) - 2999.99) <= epsilon);

    assert(ViewProduse(NULL, 1, &Array, errors) == -1);
    assert(ViewProduse(Service, 1, NULL, errors) == -1);
    assert(ViewProduse(NULL, 1, NULL, errors) == -1);
    //assert(ViewProduse(NULL, 1, NULL, NULL) == -1);

    int number = 0;
    assert(FilterProduse(NULL, "Samsung", -1, -1, &Array, &number, errors) == -1);
    assert(FilterProduse(Service, "Samsung", -1, -1, NULL, &number, errors) == -1);

    assert(FilterProduse(Service, "Samsung", -1, -1, &Array, &number, errors) == 0);
    assert(fabs(GetPret(Array[0]) - 150) <= epsilon);
    assert(FilterProduse(Service, "Lenovo", -1, -1, &Array, &number, errors) == 0);
    assert(fabs(GetPret(Array[0]) - 2999.99) <= epsilon);
    assert(FilterProduse(Service, "Lenovo", 2999.99, -1, &Array, &number, errors) == 0);
    assert(fabs(GetPret(Array[0]) - 2999.99) <= epsilon);

    assert(DestroyService(NULL) == -1);
    assert(GetLength(Service->Repository) == 11);
    assert(DestroyService(&Service) == 0);

    free(errors);
}