#include "infrastructure.h"

int CreateRepository(PREPOSITORY_PRODUSE* Repository)
{
    if (Repository == NULL)
    {
        return -1;
    }

    PREPOSITORY_PRODUSE Repo = (PREPOSITORY_PRODUSE)malloc(sizeof(REPOSITORY_PRODUSE));
    if (Repo == NULL)
    {
        return -1;
    }

    PPRODUS* Array = (PPRODUS*)malloc(INITIAL_SIZE * sizeof(PPRODUS));
    if (Array == NULL)
    {
        return -1;
    }

    Repo->Array = Array;
    Repo->Count = 0;
    Repo->Size = INITIAL_SIZE;

    *Repository = Repo;

    return 0;
}

int SearchProdus(PREPOSITORY_PRODUSE Repository, int Id, PPRODUS Result)
{
    for (int i = 0; i < Repository->Count; ++i)
    {
        if (GetId(*(Repository->Array[i])) == Id)
        {
            *Result = *(Repository->Array[i]);
            return 0;
        }
    }

    return -1;
}

int InsertProdus(PREPOSITORY_PRODUSE Repository, PPRODUS Produs)
{
    for (int i = 0; i < Repository->Count; ++i)
    {
        if (ProdusEqual(*(Repository->Array[i]), *Produs) == 1)
        {
            int cantitateOld = GetCantitate(*(Repository->Array[i]));
            int cantitateNew = GetCantitate(*Produs);
            SetCantitate(Repository->Array[i], cantitateOld + cantitateNew);
            return 1;
        }
        else if (GetId(*(Repository->Array[i])) == GetId(*Produs))
        {
            return -1;
        }
    }

    if (Repository->Count == Repository->Size)
    {
        Repository->Size = Repository->Size * 2;
        PPRODUS* temporary = realloc(Repository->Array, sizeof(PRODUS*) * Repository->Size);
        if (temporary == NULL)
        {
            return 0;
        }
        Repository->Array = temporary;
    }

    Repository->Array[Repository->Count] = Produs;
    Repository->Count = Repository->Count + 1;

    return 0;
}

int DeleteProdus(PREPOSITORY_PRODUSE Repository, int Id)
{
    int returnValue = -1;
    for (int i = 0; i < Repository->Count; ++i)
    {
        if (GetId(*(Repository->Array[i])) == Id)
        {
            if (DestroyProdus(&(Repository->Array[i])) != 0)
            {
                return -1;
            }
            for (int j = i; j < Repository->Count - 1; ++j)
                Repository->Array[j] = Repository->Array[j + 1];
            returnValue = 0;
            Repository->Count = (Repository->Count) - 1;
            break;
        }
    }

    if (Repository->Size > INITIAL_SIZE && Repository->Size / Repository->Count > RM)
    {
        Repository->Size = Repository->Size / RM;
        PPRODUS* temporary = realloc(Repository->Array, sizeof(PRODUS*) * Repository->Size);
        if (temporary == NULL)
        {
            perror("The repository could not be alocated");
            exit(1);
        }
        Repository->Array = temporary;
    }

    return returnValue;
}

int ModifyProdus(PREPOSITORY_PRODUSE Repository, int Id, double Pret, int Cantitate)
{
    if (Repository == NULL)
    {
        return -1;
    }
    for (int i = 0; i < Repository->Count; ++i)
    {
        if (GetId(*(Repository->Array[i])) == Id)
        {
            SetPret(Repository->Array[i], Pret);
            SetCantitate(Repository->Array[i], Cantitate);
            return 0;
        }
    }
    return -1;
}

int ClearRepository(PREPOSITORY_PRODUSE Repository)
{
    if (Repository == NULL)
    {
        return -1;
    }

    while (GetLength(Repository) > 0)
    {
        int id = GetId(*(Repository->Array[0]));
        if (DeleteProdus(Repository, id) != 0)
        {
            return -1;
        }
    }

    return 0;
}

int GetAll(PREPOSITORY_PRODUSE Repository, PPRODUS* Array)
{
    if (Repository == NULL || Array == NULL)
    {
        return -1;
    }

    int length = GetLength(Repository);
    PPRODUS newArray = (PPRODUS)malloc(sizeof(PRODUS) * length);
    if (newArray == NULL)
    {
        return -1;
    }

    for (int i = 0; i < length; ++i)
    {
        newArray[i] = *(Repository->Array[i]);
    }

    *Array = newArray;

    return 0;
}

int DestroyRepository(PREPOSITORY_PRODUSE* Repository)
{
    if (Repository == NULL)
    {
        return -1;
    }

    if (ClearRepository(*Repository) != 0)
    {
        return -1;
    }

    free((*Repository)->Array);
    free(*Repository);
    *Repository = NULL;

    return 0;
}

int GetLength(PREPOSITORY_PRODUSE Repository)
{
    return Repository->Count;
}

static void testCreateDestroy()
{
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);
    assert(GetLength(Repo) == 0);

    assert(DestroyRepository(NULL) == -1);
    assert(DestroyRepository(&Repo) == 0);
    assert(Repo == NULL);
}

static void testInsert()
{
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);
    assert(GetLength(Repo) == 0);

    PPRODUS Produs1, Produs2, Produs3;
    CreateProdus(&Produs1, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10);
    assert(InsertProdus(Repo, Produs1) == 0);
    assert(GetLength(Repo) == 1);

    assert(InsertProdus(Repo, Produs1) == 1);
    assert(GetLength(Repo) == 1);

    CreateProdus(&Produs2, 6, "televizor", "Lenovo", "IE 652", 3299.99, 10);
    assert(InsertProdus(Repo, Produs2) == -1);
    assert(GetLength(Repo) == 1);
    DestroyProdus(&Produs2);

    CreateProdus(&Produs3, 8, "televizor", "Lenovo", "IE 652", 3299.99, 10);
    assert(InsertProdus(Repo, Produs3) == 0);
    assert(GetLength(Repo) == 2);

    for (int i = 0; i < 120; ++i)
    {
        CreateProdus(&Produs2, i + 10, "televizor", "Lenovo", "IE 652", 3299.99, 10);
        assert(InsertProdus(Repo, Produs2) == 0);
        assert(GetLength(Repo) == i + 3);
    }
    assert(GetLength(Repo) == 122);

    assert(DestroyRepository(&Repo) == 0);
}

static void testSearch()
{
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);
    assert(GetLength(Repo) == 0);

    PPRODUS Produs;
    CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10);
    assert(InsertProdus(Repo, Produs) == 0);

    PRODUS Result;
    assert(SearchProdus(Repo, 6, &Result) == 0);
    assert(ProdusEqual(Result, *Produs) == 1);
    assert(GetCantitate(Result) == 10);

    assert(InsertProdus(Repo, Produs) == 1);
    assert(SearchProdus(Repo, 6, &Result) == 0);
    assert(ProdusEqual(Result, *Produs) == 1);
    assert(GetCantitate(Result) == 20);

    assert(SearchProdus(Repo, 9, &Result) == -1);

    for (int i = 0; i < 120; ++i)
    {
        CreateProdus(&Produs, i + 10, "televizor", "Lenovo", "IE 652", 3299.99, i);
        InsertProdus(Repo, Produs);
    }

    for (int i = 0; i < 120; ++i)
    {
        assert(SearchProdus(Repo, i + 10, &Result) == 0);
        assert(GetCantitate(Result) == i);
    }

    assert(DestroyRepository(&Repo) == 0);
}

static void testModify()
{
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);
    assert(GetLength(Repo) == 0);

    PPRODUS Produs;
    CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10);
    assert(InsertProdus(Repo, Produs) == 0);

    assert(ModifyProdus(NULL, 6, 150, 6) == -1);
    assert(ModifyProdus(Repo, 6, 150, 6) == 0);

    PRODUS Result;
    assert(SearchProdus(Repo, 6, &Result) == 0);

    CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 150, 6);
    assert(ProdusEqual(*Produs, Result) == 1);
    assert(GetCantitate(Result) == 6);

    assert(DestroyProdus(&Produs) == 0);

    assert(DestroyRepository(&Repo) == 0);
}

static void testDelete()
{
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);
    assert(GetLength(Repo) == 0);

    PPRODUS Produs;
    CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10);
    assert(InsertProdus(Repo, Produs) == 0);
    assert(GetLength(Repo) == 1);

    assert(DeleteProdus(Repo, 6) == 0);
    assert(GetLength(Repo) == 0);

    assert(DeleteProdus(Repo, 6 == -1));

    for (int i = 0; i < 120; ++i)
    {
        CreateProdus(&Produs, i + 10, "televizor", "Lenovo", "IE 652", 3299.99, 10);
        assert(InsertProdus(Repo, Produs) == 0);
    }
    for (int i = 0; i < 120; ++i)
    {
        assert(DeleteProdus(Repo, i + 10) == 0);
        assert(GetLength(Repo) == 120 - i - 1);
    }

    assert(GetLength(Repo) == 0);

    assert(DestroyRepository(&Repo) == 0);
}

static void testClear()
{
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);
    assert(GetLength(Repo) == 0);

    PPRODUS Produs;

    for (int i = 0; i < 120; ++i)
    {
        CreateProdus(&Produs, i + 10, "televizor", "Lenovo", "IE 652", 3299.99, 10);
        assert(InsertProdus(Repo, Produs) == 0);
    }
    assert(GetLength(Repo) == 120);

    assert(ClearRepository(Repo) == 0);
    assert(GetLength(Repo) == 0);

    assert(DestroyRepository(&Repo) == 0);
}

static void testGetAll()
{
    PPRODUS Result = (PPRODUS)malloc(sizeof(PRODUS));

    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);
    assert(GetLength(Repo) == 0);

    PPRODUS Produs;
    CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10);
    assert(InsertProdus(Repo, Produs) == 0);

    PPRODUS ProdusNou;
    CreateProdus(&ProdusNou, 8, "televizor", "Samsung", "Wow", 3299.99, 10);
    assert(InsertProdus(Repo, ProdusNou) == 0);

    PPRODUS Array;
    assert(GetAll(Repo, &Array) == 0);
    assert(SearchProdus(Repo, 6, Result) == 0);
    assert(ProdusEqual(*Result, Array[0]) == 1);
    assert(SearchProdus(Repo, 8, Result) == 0);
    assert(ProdusEqual(*Result, Array[1]) == 1);

    assert(InsertProdus(Repo, Produs) == 1);

    assert(DestroyRepository(&Repo) == 0);

    free(Array);
    free(Result);
}

/*static void testRepository()
{
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);
    assert(GetLength(Repo) == 0);

    PPRODUS Produs;
    CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10);
    PPRODUS Result = (PPRODUS)malloc(sizeof(PRODUS));

    assert(InsertProdus(Repo, Produs) == 0);
    assert(GetLength(Repo) == 1);
    assert(SearchProdus(Repo, 6, Result) == 0);
    assert(ProdusEqual(*Produs, *Result) == 1);

    PRODUS ProdusInexistent = { 3, "televizor", "Samsung", "Wow", 3299.99, 10 };
    assert(SearchProdus(Repo, 3, Result) == -1);

    PPRODUS ProdusNou;
    CreateProdus(&ProdusNou, 8, "televizor", "Samsung", "Wow", 3299.99, 10);

    assert(InsertProdus(Repo, ProdusNou) == 0);
    assert(SearchProdus(Repo, 8, Result) == 0);
    assert(ProdusEqual(*ProdusNou, *Result) == 1);
    assert(GetLength(Repo) == 2);

    PPRODUS Array;
    assert(GetAll(Repo, &Array) == 0);
    assert(SearchProdus(Repo, 6, Result) == 0);
    assert(ProdusEqual(*Result, Array[0]) == 1);
    assert(SearchProdus(Repo, 8, Result) == 0);
    assert(ProdusEqual(*Result, Array[1]) == 1);

    assert(DeleteProdus(Repo, 6) == 0);
    assert(GetLength(Repo) == 1);
    assert(SearchProdus(Repo, 6, Result) == -1);
    assert(DeleteProdus(Repo, 6) == -1);

    CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10);
    assert(InsertProdus(Repo, Produs) == 0);
    assert(SearchProdus(Repo, 6, Result) == 0);
    assert(fabs(GetPret(*Result) - 3299.99) <= epsilon);
    assert(GetCantitate(*Result) == 10);

    assert(ModifyProdus(Repo, 6, 459.99, 2) == 0);
    assert(SearchProdus(Repo, 6, Result) == 0);
    assert(fabs(GetPret(*Result) - 459.99) <= epsilon);
    assert(GetCantitate(*Result) == 2);

    assert(ModifyProdus(Repo, 4, 56.8, 3) == -1);

    assert(ModifyProdus(Repo, 8, 1899.49, 1) == 0);
    assert(SearchProdus(Repo, 8, Result) == 0);
    assert(fabs(GetPret(*Result) - 1899.49) <= epsilon);
    assert(GetCantitate(*Result) == 1);

    assert(ClearRepository(Repo) == 0);
    assert(GetLength(Repo) == 0);

    for (int i = 0; i < 100; ++i)
    {
        CreateProdus(&Produs, i, "laptop", "Lenovo", "IE 652", 3299.99, 10);
        assert(InsertProdus(Repo, Produs) == 0);
        assert(GetLength(Repo) == i + 1);
    }

    CreateProdus(&Produs, 0, "laptop", "Lenovo", "IE 652", 3299.99, 15);
    assert(InsertProdus(Repo, Produs) == 0);
    assert(GetLength(Repo) == 100);
    assert(SearchProdus(Repo, 0, Result) == 0);
    assert(GetCantitate(*Result) == 25);

    CreateProdus(&Produs, 0, "televizor", "Lenovo", "IE 652", 3299.99, 15);
    assert(InsertProdus(Repo, Produs) == -1);

    assert(DestroyRepository(&Repo) == 0);

    free(Result);
}*/

void testInfrastructure()
{
    testCreateDestroy();
    testInsert();
    testSearch();
    testDelete();
    testClear();
    testGetAll();
    testModify();
}