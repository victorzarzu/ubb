#include "service.h"

int CreateService(PSERVICE_PRODUCTS* Service, PREPOSITORY_PRODUSE Repository, ValidationFunction Validation)
{
    if (Service == NULL || Repository == NULL || Validation == NULL)
    {
        if (Repository != NULL)
        {
            DestroyRepository(&Repository);
        }
        return -1;
    }

    PSERVICE_PRODUCTS service = (PSERVICE_PRODUCTS)malloc(sizeof(SERVICE_PRODUCTS));
    /*if (service == NULL)
    {
        DestroyRepository(&Repository);
        return -1;
    }*/

    service->Repository = Repository;
    service->ValidateProduct = Validation;

    *Service = service;

    return 0;
}

int StoreProdus(PSERVICE_PRODUCTS Service, int Id, char* Tip, char* Producator, char* Model, double Pret, int Cantitate, char* errors)
{
    if (errors == NULL)
    {
        return -1;
    }
    errors[0] = NULL;
    if (Service == NULL || Tip == NULL || Producator == NULL || Model == NULL || errors == NULL)
    {
        strcat(errors, "Storing failed!\n");
        return -1;
    }

    PPRODUS Produs;
    /*if (CreateProdus(&Produs, Id, Tip, Producator, Model, Pret, Cantitate) != 0)
    {
        strcat(errors, "Could not create a product!\n");
        return -1;
    }*/
    CreateProdus(&Produs, Id, Tip, Producator, Model, Pret, Cantitate);

    if (Service->ValidateProduct(*Produs, errors) != 0)
    {
        DestroyProdus(&Produs);
        return -1;
    }
    int returnCode = InsertProdus(Service->Repository, Produs);
    if (returnCode == -1)
    {
        DestroyProdus(&Produs);
        strcat(errors, "The product with this id already exists!\n");
        return -1;
    }
    else if (returnCode == 1)
    {
        DestroyProdus(&Produs);
    }

    return 0;
}

int EraseProdus(PSERVICE_PRODUCTS Service, int Id, char* errors)
{
    if (errors == NULL)
    {
        return -1;
    }
    errors[0] = '\0';
    if (Service == NULL)
    {
        strcat(errors, "Erasing failed!\n");
        return -1;
    }
    

    if (DeleteProdus(Service->Repository, Id) != 0)
    {
        strcat(errors, "The product does not exist!\n");
        return -1;
    }

    return 0;
}

int ChangeProdus(PSERVICE_PRODUCTS Service, int Id, double Pret, int Cantitate, char* errors)
{
    if (errors == NULL)
    {
        return -1;
    }
    errors[0] = NULL;
    if (Service == NULL || errors == NULL)
    {
        strcat(errors, "Modification failed!\n");
        return -1;
    }

    PRODUS Produs;
    if (SearchProdus(Service->Repository, Id, &Produs) != 0)
    {
        strcat(errors, "The product does not exist!\n");
        return -1;
    }

    if (Cantitate != -oo)
    {
        SetCantitate(&Produs, Cantitate);
    }
    else
    {
        Cantitate = GetCantitate(Produs);
    }

    if (Pret != -oo)
    {
        SetPret(&Produs, Pret);
    }
    else
    {
        Pret = GetPret(Produs);
    }

    if (Service->ValidateProduct(Produs, errors) != 0)
    {
        return -1;
    }

    /*if (ModifyProdus(Service->Repository, Id, Pret, Cantitate) != 0)
    {
        strcat(errors, "The modification failed!\n");
        return -1;
    }*/
    ModifyProdus(Service->Repository, Id, Pret, Cantitate);

    return 0;
}

int ViewProduse(PSERVICE_PRODUCTS Service, int Mode, PPRODUS* Array, char* errors)
{
    if (errors == NULL)
    {
        return -1;
    }
    errors[0] = NULL;
    if (Service == NULL || Array == NULL)
    {
        strcat(errors, "Viewing failed!\n");
        return -1;
    }

    if (GetLength(Service->Repository) == 0)
    {
        strcat(errors, "There are no products!\n");
        return -1;
    }

    /*if (GetAll(Service->Repository, Array) != 0)
    {
        free(*Array);
        strcat(errors, "Viewing failed!\n");
        return -1;
    }*/
    GetAll(Service->Repository, Array);

    int length = GetLength(Service->Repository);
    if (Mode == 0)
    {
        SelectionSort(*Array, CompareProduseIncreasing, length);
        //qsort(*Array, Service->Repository->Count, sizeof(PRODUS), CompareProduseIncreasing);
    }
    else
    {
        SelectionSort(*Array, CompareProduseDecreasing, length);
        //qsort(*Array, Service->Repository->Count, sizeof(PRODUS), CompareProduseDecreasing);
    }

    return 0;
}

int FilterProduse(PSERVICE_PRODUCTS Service, char* Producator, double Pret, int Cantitate, PPRODUS* Array, int* Number, char* errors)
{
    if (errors == NULL)
    {
        return -1;
    }
    errors[0] = NULL;
    if (Service == NULL || Array == NULL || Number == NULL)
    {
        strcat(errors, "Filtering failed!\n");
        return -1;
    }

    if (GetLength(Service->Repository) == 0)
    {
        strcat(errors, "There are no products!\n");
        return -1;
    }

    PPRODUS array;
    /*if (GetAll(Service->Repository, &array) != 0)
    {
        return -1;
    }*/
    GetAll(Service->Repository, &array);
    int count = GetLength(Service->Repository);
    PPRODUS arrayFilter = (PPRODUS)malloc(count * sizeof(PRODUS));
    /*if (arrayFilter == NULL)
    {
        free(array);
        strcat(errors, "Viewing failed!\n");
        return -1;
    }*/

    *Number = 0;
    char* producatorHere;
    for (int i = 0; i < count; ++i)
    {
        PRODUS Produs;
        int length = max(strlen(GetProducator(array[i])), strlen(Producator));
        producatorHere = (char*)malloc(sizeof(char) * (length + 1));
        /*if (producatorHere == NULL)
        {
            free(array);
            free(arrayFilter);
            strcat(errors, "Viewing failed!\n");
            return -1;
        }*/

        double pretHere = Pret;
        int cantitateHere = Cantitate;
        if (strcmp(Producator, "-1") == 0)
        {
            char* producator = GetProducator(array[i]);
            strcpy(producatorHere, producator);
        }
        else
        {
            strcpy(producatorHere, Producator);
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
        free(producatorHere);
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

    PREPOSITORY_PRODUSE repository = (*Service)->Repository;
    /*if (DestroyRepository(&repository) != 0)
    {
        return -1;
    }*/
    DestroyRepository(&repository);

    free(*Service);
    *Service = NULL;

    return 0;
}

static void testCreateDestroy()
{
    PSERVICE_PRODUCTS Service;

    ValidationFunction validate = ValidateProdus;
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);

    assert(CreateService(NULL, NULL, NULL) == -1);
    assert(CreateService(NULL, Repo, NULL) == -1);
    assert(CreateRepository(&Repo) == 0);

    assert(CreateService(&Service, Repo, validate) == 0);

    assert(DestroyService(NULL) == -1);
    assert(DestroyService(&Service) == 0);
}

static void testStore()
{
    PPRODUS Produs;
    PRODUS Result;

    PSERVICE_PRODUCTS Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateProdus;
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);

    assert(CreateService(&Service, Repo, validate) == 0);

    assert(StoreProdus(Service, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10, NULL) == -1);
    assert(StoreProdus(NULL, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10, errors) == -1);
    assert(strcmp(errors, "Storing failed!\n") == 0);

    assert(StoreProdus(NULL, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10, errors) == -1);
    assert(StoreProdus(Service, 6, "laptop", NULL, "IE 652", 3299.99, 10, errors) == -1);
    assert(StoreProdus(Service, 6, "laptop", "Lenvo", "IE 652", 3299.99, 10, NULL) == -1);

    assert(SearchProdus(Service->Repository, 6, &Result) == -1);

    assert(StoreProdus(Service, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10, errors) == 0);
    assert(GetLength(Service->Repository) == 1);
;
    assert(SearchProdus(Service->Repository, 6, &Result) == 0);
    assert(CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10) == 0);
    assert(ProdusEqual(*Produs, Result) == 1);
    assert(GetCantitate(Result) == 10);

    assert(DestroyProdus(&Produs) == 0);

    assert(StoreProdus(Service, 6, "laptop", "Lenovo", "IE 652", 3299.99, 6, errors) == 0);
    assert(GetLength(Service->Repository) == 1);

    assert(StoreProdus(Service, 6, "haha", "nana", "Wow", 3299.99, 10, errors) == -1);
    assert(strcmp(errors, "The product with this id already exists!\n") == 0);

    assert(StoreProdus(Service, 6, "", "Lenovo", "IE 652", 3299.99, -10, errors) == -1);
    assert(strcmp(errors, "Invalid type!\nInvalid quantity!\n") == 0);

    assert(StoreProdus(Service, -5, "", "", "", -5, -10, errors) == -1);
    assert(strcmp(errors, "Invalid id!\nInvalid type!\nInvalid manufacturer!\nInvalid model!\nInvalid price!\nInvalid quantity!\n") == 0);

    for (int i = 0; i < 120; ++i)
    {
        assert(StoreProdus(Service, i + 10, "laptop", "Lenovo", "IE 652", 3299.99, 6, errors) == 0);
        assert(GetLength(Service->Repository) == i + 2);
    }

    assert(GetLength(Service->Repository) == 121);

    assert(DestroyService(&Service) == 0);
    assert(Service == NULL);
    free(errors);
}

static void testErase()
{
    PSERVICE_PRODUCTS Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateProdus;
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);

    assert(CreateService(&Service, Repo, validate) == 0);

    assert(EraseProdus(Service, 6, errors) == -1);
    assert(EraseProdus(NULL, 6, errors) == -1);
    assert(strcmp(errors, "Erasing failed!\n") == 0);
    assert(EraseProdus(Service, 6, NULL) == -1);

    assert(StoreProdus(Service, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10, errors) == 0);
    assert(GetLength(Service->Repository) == 1);

    for (int i = 0; i < 120; ++i)
    {
        assert(StoreProdus(Service, i + 10, "laptop", "Lenovo", "IE 652", 3299.99, 6, errors) == 0);
        assert(GetLength(Service->Repository) == i + 2);
    }
    
    for (int i = 0; i < 120; ++i)
    {
        assert(EraseProdus(Service, i + 10, errors) == 0);
        assert(GetLength(Service->Repository) == 121 - i - 1);
    }

    assert(GetLength(Service->Repository) == 1);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void testChange()
{
    PSERVICE_PRODUCTS Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateProdus;
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);

    assert(CreateService(&Service, Repo, validate) == 0);

    assert(StoreProdus(Service, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10, errors) == 0);
    assert(GetLength(Service->Repository) == 1);

    assert(ChangeProdus(Service, 7, 150, 5, errors) == -1);
    assert(strcmp(errors, "The product does not exist!\n") == 0);

    assert(ChangeProdus(NULL, 6, 150, 5, errors) == -1);
    assert(strcmp(errors, "Modification failed!\n") == 0);

    assert(ChangeProdus(Service, 6, 150, 5, NULL) == -1);

    assert(ChangeProdus(Service, 6, -1, 5, errors) == -1);
    assert(strcmp(errors, "Invalid price!\n") == 0);
    assert(ChangeProdus(Service, 6, 150, 5, errors) == 0);
    PPRODUS Array;
    assert(ViewProduse(Service, 0, &Array, errors) == 0);
    assert(fabs(GetPret(Array[0]) - 150) <= epsilon);
    assert(GetCantitate(Array[0]) == 5);
    free(Array);

    assert(ChangeProdus(Service, 6, -oo, 100, errors) == 0);
    assert(ViewProduse(Service, 0, &Array, errors) == 0);
    assert(fabs(GetPret(Array[0]) - 150) <= epsilon);
    assert(GetCantitate(Array[0]) == 100);
    free(Array);

    assert(ChangeProdus(Service, 6, 5005.43, -oo, errors) == 0);
    assert(ViewProduse(Service, 0, &Array, errors) == 0);
    assert(fabs(GetPret(Array[0]) - 5005.43) <= epsilon);
    assert(GetCantitate(Array[0]) == 100);

    assert(DestroyService(&Service) == 0);
    free(Array);
    free(errors);
}

static void testView()
{
    PPRODUS Array = NULL;
    PSERVICE_PRODUCTS Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateProdus;
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);

    assert(CreateService(&Service, Repo, validate) == 0);

    assert(ViewProduse(NULL, 0, &Array, errors) == -1);
    assert(strcmp(errors, "Viewing failed!\n") == 0);
    assert(ViewProduse(Service, 0, &Array, NULL) == -1);

    assert(ViewProduse(Service, 0, NULL, errors) == -1);
    assert(strcmp(errors, "Viewing failed!\n") == 0);

    assert(ViewProduse(Service, 0, &Array, errors) == -1);
    assert(strcmp(errors, "There are no products!\n") == 0);

    assert(StoreProdus(Service, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10, errors) == 0);
    assert(GetLength(Service->Repository) == 1);

    assert(StoreProdus(Service, 6, "laptop", NULL, "IE 652", 3299.99, 10, errors) == -1);

    assert(StoreProdus(Service, 8, "televizor", "Samsung", "IE 652", 150, 10, errors) == 0);
    assert(GetLength(Service->Repository) == 2);

    assert(ViewProduse(Service, 0, &Array, errors) == 0);
    assert(fabs(GetPret(Array[0]) - 150) <= epsilon);
    assert(fabs(GetPret(Array[1]) - 3299.99) <= epsilon);

    free(Array);
    assert(ViewProduse(Service, 1, &Array, errors) == 0);
    assert(fabs(GetPret(Array[1]) - 150) <= epsilon);
    assert(fabs(GetPret(Array[0]) - 3299.99) <= epsilon);

    assert(ChangeProdus(Service, 8, 3299.99, 10, errors) == 0);
    assert(ChangeProdus(Service, 8, 3299.99, 6, errors) == 0);

    free(Array);
    assert(ViewProduse(Service, 0, &Array, errors) == 0);
    assert(GetCantitate(Array[0]) == 6);
    assert(GetCantitate(Array[1]) == 10);

    free(Array);
    assert(ViewProduse(Service, 1, &Array, errors) == 0);
    assert(GetCantitate(Array[1]) == 6);
    assert(GetCantitate(Array[0]) == 10);

    assert(DestroyService(&Service) == 0);
    free(Array);
    free(errors);
}

static void testFilter()
{
    PPRODUS Array;
    PSERVICE_PRODUCTS Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateProdus;
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);

    assert(CreateService(&Service, Repo, validate) == 0);

    int number;
    assert(FilterProduse(NULL, "ceva", 154, 6, &Array, &number, errors) == -1);
    assert(strcmp(errors, "Filtering failed!\n") == 0);
    assert(FilterProduse(Service, "ceva", 154, 6, &Array, &number, NULL) == -1);

    assert(FilterProduse(Service, "ceva", 154, 6, &Array, &number, errors) == -1);
    assert(strcmp(errors, "There are no products!\n") == 0);


    assert(StoreProdus(Service, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10, errors) == 0);
    assert(GetLength(Service->Repository) == 1);

    assert(StoreProdus(Service, 8, "televizor", "Samsung", "IE 652", 150, 10, errors) == 0);
    assert(GetLength(Service->Repository) == 2);


    assert(FilterProduse(Service, "-1", -1, 10, &Array, &number, errors) == 0);
    assert(number == 2);

    free(Array);
    assert(FilterProduse(Service, "Samsung", -1, -1, &Array, &number, errors) == 0);
    assert(number == 1);

    free(Array);
    assert(FilterProduse(Service, "-1", -1, -1, &Array, &number, errors) == 0);
    assert(number == 2);

    free(Array);
    assert(FilterProduse(Service, "-1", 3299.99, -1, &Array, &number, errors) == 0);
    assert(number == 1);

    assert(StoreProdus(Service, 5, "laptop", "Lenovo", "IE 652", 3299.99, 10, errors) == 0);
    assert(GetLength(Service->Repository) == 3);

    free(Array);
    assert(FilterProduse(Service, "-1", 3299.99, -1, &Array, &number, errors) == 0);
    assert(number == 2);

    free(Array);
    assert(FilterProduse(Service, "-1", 1, -1, &Array, &number, errors) == -1);
    assert(number == 0);
    assert(strcmp(errors, "There are no products!\n") == 0);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

void testService()
{
    testCreateDestroy();
    testStore();
    testView();
    testErase();
    testChange();
    testFilter();
}