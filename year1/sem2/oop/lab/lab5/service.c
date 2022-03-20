#include "service.h"

SERVICE_TRANZACTII CreateService(REPOSITORY* Repository, ValidationFunction Validation)
{
    SERVICE_TRANZACTII service;
    /*if (service == NULL)
    {
        DestroyRepository(&Repository);
        return -1;
    }*/

    service.Repository = Repository;
    service.ValidateTranzactie = Validation;

    return service;
}

int StoreTranzactie(PSERVICE_TRANZACTII Service, int Id, int Zi, double Suma, int Tip, char* Descriere, char* errors)
{
    if (errors == NULL)
    {
        return -1;
    }
    errors[0] = '\0';
    if (Service == NULL || errors == NULL)
    {
        strcat(errors, "Storing failed!\n");
        return -1;
    }

    ElemType Tranzactie;
    /*if (CreateProdus(&Produs, Id, Tip, Producator, Model, Pret, Cantitate) != 0)
    {
        strcat(errors, "Could not create a product!\n");
        return -1;
    }*/
    Tranzactie = CreateTranzactie(Id, Zi, Suma, Tip, Descriere);

    if (Service->ValidateTranzactie(Tranzactie, errors) != 0)
    {
        DestroyTranzactie(Tranzactie);
        return -1;
    }
    if(InsertTranzactie(Service->Repository, Tranzactie) == -1)
    {
        DestroyTranzactie(Tranzactie);
        strcat(errors, "The transaction with this id already exists!\n");
        return -1;
    }

    return 0;
}

int EraseTranzactie(PSERVICE_TRANZACTII Service, int Id, char* errors)
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


    if (DeleteTranzactie(Service->Repository, Id) != 0)
    {
        strcat(errors, "The product does not exist!\n");
        return -1;
    }

    return 0;
}

int ChangeTranzactie(PSERVICE_TRANZACTII Service, int Id, double Suma, int Zi, char* errors)
{
    if (errors == NULL)
    {
        return -1;
    }
    errors[0] = '\0';
    if (Service == NULL || errors == NULL)
    {
        strcat(errors, "Modification failed!\n");
        return -1;
    }

    ElemType Tranzactie;
    if (SearchTranzactie(Service->Repository->List, Id, &Tranzactie) != 0)
    {
        strcat(errors, "The transaction does not exist!\n");
        return -1;
    }
    Tranzactie = CopyTranzactie(Tranzactie);

    if (Suma != -oo)
    {
        SetSuma((PTRANZACTIE)Tranzactie, Suma);
    }
    else
    {
        Suma = GetSuma(Tranzactie);
    }

    if (Zi != -oo)
    {
        SetZi((PTRANZACTIE)Tranzactie, Zi);
    }
    else
    {
        Zi = GetZi(Tranzactie);
    }

    if (Service->ValidateTranzactie(Tranzactie, errors) != 0)
    {
        DestroyTranzactie(Tranzactie);
        return -1;
    }

    if (ModifyTranzactie(Service->Repository, Id, Suma, Zi) != 0)
    {
        DestroyTranzactie(Tranzactie);
        strcat(errors, "The modification failed!\n");
        return -1;
    }

    DestroyTranzactie(Tranzactie);

    return 0;
}

MY_LIST* ViewTranzactii(PSERVICE_TRANZACTII Service, int Mode, int AscendingMode, char* errors)
{
    errors[0] = '\0';

    MY_LIST* List = CopyList(Service->Repository->List);
    if (Mode == 0) //zi
    {
        if (AscendingMode == 0) //crescator
        {
            BubbleSort(List, compareZi, ascendingMode);
        }
        else
        {
            BubbleSort(List, compareZi, descendingMode);
        }
    }
    else
    {
        if (AscendingMode == 0) //crescator
        {
            BubbleSort(List, compareSuma, ascendingMode);
        }
        else
        {
            BubbleSort(List, compareSuma, descendingMode);
        }
    }

    return List;
}

MY_LIST* FilterTranzactii(PSERVICE_TRANZACTII Service, int Tip, double Suma, int Zi, int Mode, int sumMode, char* errors)
{
    errors[0] = '\0';

    MY_LIST* Array = CreateList();
    int count = GetLength(Service->Repository->List);

    for (int i = 0; i < count; ++i)
    {
        ElemType Tranzactie = GetElement(Service->Repository->List, i);

        if (Mode == 0)
        {
            if (isType(Tranzactie, Tip))
            {
                ElemType Copy = CopyTranzactie(Tranzactie);
                Insert(Array, Copy);
            }
        }
        else if(Mode == 1)
        {
            if (sumMode == 0) //mai mic
            {
                if (smallerSum(Tranzactie, Suma))
                {
                    ElemType Copy = CopyTranzactie(Tranzactie);
                    Insert(Array, Copy);
                }
            }
            else
            {
                if (biggerSum(Tranzactie, Suma))
                {
                    ElemType Copy = CopyTranzactie(Tranzactie);
                    Insert(Array, Copy);
                }
            }
        }
        else
        {
            if (isDay(Tranzactie, Zi))
            {
                ElemType Copy = CopyTranzactie(Tranzactie);
                Insert(Array, Copy);
            }
        }
    }

    return Array;
}

int Undo(PSERVICE_TRANZACTII Service)
{
    return UndoOperation(&(Service->Repository));
}

int DestroyService(PSERVICE_TRANZACTII Service)
{
    /*if (DestroyRepository(&repository) != 0)
    {
        return -1;
    }*/
    DestroyRepository(Service->Repository);

    return 0;
}

static void testCreateDestroy()
{
    SERVICE_TRANZACTII Service;

    ValidationFunction validate = ValidateTranzactie;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(DestroyService(&Service) == 0);
}

static void testStore()
{
    ElemType Tranzactie;
    ElemType Result;

    SERVICE_TRANZACTII Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateTranzactie;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(StoreTranzactie(&Service, 6, 4, 56.12, 0, "ceva", NULL) == -1);
    assert(StoreTranzactie(NULL, 6, 4, 56.12, 0, "ceva", errors) == -1);
    assert(strcmp(errors, "Storing failed!\n") == 0);

    assert(StoreTranzactie(NULL, 6, 4, 56.12, 0, "ceva", NULL) == -1);

    assert(SearchTranzactie(Service.Repository->List, 6, &Result) == -1);

    assert(StoreTranzactie(&Service, 6, 4, 56.12, 0, "ceva", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    SearchTranzactie(Service.Repository->List, 6, &Result);
    Tranzactie = CreateTranzactie(6, 4, 56.12, 0, "ceva");
    assert(TranzactieEqual(Tranzactie, Result) == 1);

    DestroyTranzactie(Tranzactie);

    assert(StoreTranzactie(&Service, 6, 1, 5168, 0, "ceva", errors) == -1);
    assert(strcmp(errors, "The transaction with this id already exists!\n") == 0);
    
    assert(StoreTranzactie(&Service, -1, 65, -1, 0, "", errors) == -1);
    assert(strcmp(errors, "Invalid id!\nInvalid day!\nInvalid sum!\nInvalid description!\n") == 0);

    assert(StoreTranzactie(&Service, -1, 65, -1, 5, "", errors) == -1);
    assert(strcmp(errors, "Invalid id!\nInvalid day!\nInvalid sum!\nInvalid type!\nInvalid description!\n") == 0);
    for (int i = 0; i < 120; ++i)
    {
        assert(StoreTranzactie(&Service, i + 10, 4, 56.12, 0, "ceva", errors) == 0);
        assert(GetLength(Service.Repository->List) == i + 2);
    }

    assert(GetLength(Service.Repository->List) == 121);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void testErase()
{
    SERVICE_TRANZACTII Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateTranzactie;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(EraseTranzactie(&Service, 6, errors) == -1);
    assert(EraseTranzactie(NULL, 6, errors) == -1);
    assert(strcmp(errors, "Erasing failed!\n") == 0);
    assert(EraseTranzactie(&Service, 6, NULL) == -1);

    assert(StoreTranzactie(&Service, 6, 4, 56.12, 0, "ceva", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    for (int i = 0; i < 120; ++i)
    {
        assert(StoreTranzactie(&Service, i + 10, 4, 56.12, 0, "ceva", errors) == 0);
        assert(GetLength(Service.Repository->List) == i + 2);
    }

    for (int i = 0; i < 120; ++i)
    {
        assert(EraseTranzactie(&Service, i + 10, errors) == 0);
        assert(GetLength(Service.Repository->List) == 121 - i - 1);
    }

    assert(GetLength(Service.Repository->List) == 1);

    ElemType Tranzactie = RemoveLast(Service.Repository->List);
    assert(GetId(Tranzactie) == 6);
    DestroyTranzactie(Tranzactie);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void testChange()
{
    SERVICE_TRANZACTII Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateTranzactie;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(StoreTranzactie(&Service, 6, 5, 198, 0, "ceva", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    assert(ChangeTranzactie(&Service, 7, 150, 5, errors) == -1);
    assert(strcmp(errors, "The transaction does not exist!\n") == 0);

    assert(ChangeTranzactie(NULL, 6, 150, 5, errors) == -1);
    assert(strcmp(errors, "Modification failed!\n") == 0);

    assert(ChangeTranzactie(&Service, 6, 150, 5, NULL) == -1);

    assert(ChangeTranzactie(&Service, 6, -1, 67, errors) == -1);
    assert(strcmp(errors, "Invalid day!\nInvalid sum!\n") == 0);
    assert(ChangeTranzactie(&Service, 6, 150, 5, errors) == 0);

    MY_LIST* Array;
    Array = ViewTranzactii(&Service, 0, 0, errors);
    assert(fabs(GetSuma(GetElement(Array, 0)) - 150) <= epsilon);
    assert(GetZi(GetElement(Array, 0)) == 5);
    Destroy(Array, DestroyTranzactie);

    assert(ChangeTranzactie(&Service, 6, -oo, 14, errors) == 0);
    Array = ViewTranzactii(&Service, 0, 0, errors);
    assert(fabs(GetSuma(GetElement(Array, 0)) - 150) <= epsilon);
    assert(GetZi(GetElement(Array, 0)) == 14);
    Destroy(Array, DestroyTranzactie);

    assert(ChangeTranzactie(&Service, 6, 5005.43, -oo, errors) == 0);
    Array = ViewTranzactii(&Service, 0, 0, errors);
    assert(fabs(GetSuma(GetElement(Array, 0)) - 5005.43) <= epsilon);
    assert(GetZi(GetElement(Array, 0)) == 14);
    Destroy(Array, DestroyTranzactie);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void testView()
{
    SERVICE_TRANZACTII Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateTranzactie;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(StoreTranzactie(&Service, 6, 5, 198, 0, "ceva", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);


    assert(StoreTranzactie(&Service, 7, 7, 178, 0, "ceva", errors) == 0);
    assert(GetLength(Service.Repository->List) == 2);

    MY_LIST* Array = ViewTranzactii(&Service, 0, 0, errors);
    assert(GetId(GetElement(Array, 0)) == 6);
    assert(GetId(GetElement(Array, 1)) == 7);
    Destroy(Array, DestroyTranzactie);

    Array = ViewTranzactii(&Service, 0, 1, errors);
    assert(GetId(GetElement(Array, 1)) == 6);
    assert(GetId(GetElement(Array, 0)) == 7);
    Destroy(Array, DestroyTranzactie);

    Array = ViewTranzactii(&Service, 1, 0, errors);
    assert(GetId(GetElement(Array, 1)) == 6);
    assert(GetId(GetElement(Array, 0)) == 7);
    Destroy(Array, DestroyTranzactie);

    Array = ViewTranzactii(&Service, 1, 1, errors);
    assert(GetId(GetElement(Array, 0)) == 6);
    assert(GetId(GetElement(Array, 1)) == 7);
    Destroy(Array, DestroyTranzactie);

    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void testFilter()
{
    SERVICE_TRANZACTII Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateTranzactie;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(StoreTranzactie(&Service, 6, 5, 198, 0, "ceva", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);


    assert(StoreTranzactie(&Service, 7, 7, 178, 0, "ceva", errors) == 0);
    assert(GetLength(Service.Repository->List) == 2);


    MY_LIST* Array = FilterTranzactii(&Service, 0, 15, 0, 0, 0, errors);
    assert(GetLength(Array) == 2);
    Destroy(Array, DestroyTranzactie);

    Array = FilterTranzactii(&Service, 0, 180, 0, 1, 0, errors);
    assert(GetLength(Array) == 1);
    Destroy(Array, DestroyTranzactie);

    Array = FilterTranzactii(&Service, 0, 200, 0, 1, 0, errors);
    assert(GetLength(Array) == 2);
    Destroy(Array, DestroyTranzactie);

    Array = FilterTranzactii(&Service, 0, 200, 0, 1, 1, errors);
    assert(GetLength(Array) == 0);
    Destroy(Array, DestroyTranzactie);

    Array = FilterTranzactii(&Service, 0, 180, 0, 1, 1, errors);
    assert(GetLength(Array) == 1);
    Destroy(Array, DestroyTranzactie);

    Array = FilterTranzactii(&Service, 0, 180, 7, 2, 1, errors);
    assert(GetLength(Array) == 1);
    Destroy(Array, DestroyTranzactie);

    Array = FilterTranzactii(&Service, 0, 180, 15, 2, 1, errors);
    assert(GetLength(Array) == 0);
    Destroy(Array, DestroyTranzactie);
    
    assert(DestroyService(&Service) == 0);
    free(errors);
}

static void testUndo()
{
    //PTRANZACTIE Result, Tranzactie;

    SERVICE_TRANZACTII Service;
    char* errors = (char*)malloc(100 * sizeof(char));

    ValidationFunction validate = ValidateTranzactie;
    REPOSITORY* Repository = CreateRepository();

    Service = CreateService(Repository, validate);

    assert(StoreTranzactie(&Service, 6, 4, 56.12, 0, "ceva", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    assert(Undo(&Service) == 0);
    assert(GetLength(Service.Repository->List) == 0);
    assert(Undo(&Service) == -1);

    assert(StoreTranzactie(&Service, 6, 4, 56.12, 0, "ceva", errors) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    assert(EraseTranzactie(&Service, 6, errors) == 0);
    assert(GetLength(Service.Repository->List) == 0);

    assert(Undo(&Service) == 0);
    assert(GetLength(Service.Repository->List) == 1);

    for (int i = 0; i < 10; ++i)
    {
        assert(StoreTranzactie(&Service, i + 10, 4, 56.12, 0, "ceva", errors) == 0);
    }
    assert(GetLength(Service.Repository->List) == 11);

    for (int i = 0; i < 10; ++i)
    {
        assert(Undo(&Service) == 0);
        assert(GetLength(Service.Repository->List) == 10 - i);
    }

    MY_LIST* Array;
    Array = ViewTranzactii(&Service, 0, 0, errors);
    assert(fabs(GetSuma(GetElement(Array, 0)) - 56.12) <= epsilon);
    assert(GetZi(GetElement(Array, 0)) == 4);
    Destroy(Array, DestroyTranzactie);

    assert(ChangeTranzactie(&Service, 6, 150, 5, errors) == 0);
    
    Array = ViewTranzactii(&Service, 0, 0, errors);
    assert(fabs(GetSuma(GetElement(Array, 0)) - 150) <= epsilon);
    assert(GetZi(GetElement(Array, 0)) == 5);
    Destroy(Array, DestroyTranzactie);

    assert(Undo(&Service) == 0);

    Array = ViewTranzactii(&Service, 0, 0, errors);
    assert(fabs(GetSuma(GetElement(Array, 0)) - 56.12) <= epsilon);
    assert(GetZi(GetElement(Array, 0)) == 4);
    Destroy(Array, DestroyTranzactie);


    DestroyService(&Service);
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
    testUndo();
}