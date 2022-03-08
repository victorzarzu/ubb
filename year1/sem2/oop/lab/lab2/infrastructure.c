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

    PPRODUS* Array = (PPRODUS*)calloc(INITIAL_SIZE, sizeof(PPRODUS));
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

static int MaintainRepositoryIncreasing(PREPOSITORY_PRODUSE* Repository)
{
    if(Repository == NULL)
    {
        return -1;
    }

    if ((*Repository)->Count == (*Repository)->Size)
    {
        (*Repository)->Size = (*Repository)->Size * 2;
        PPRODUS* temporary = realloc((*Repository)->Array, sizeof(PRODUS*) * (*Repository)->Size);
        if (temporary == NULL)
        {
            return -1;
        }
        (*Repository)->Array = temporary;
    }

    return 0;
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
            return 0;
        }
        else if (GetId(*(Repository->Array[i])) == GetId(*Produs))
        {
            return -1;
        }
    }

    /*if (Repository->Count == Repository->Size)
    {
        Repository->Size = Repository->Size * 2;
        PPRODUS* temporary = realloc(Repository->Array, sizeof(PRODUS*) * Repository->Size);
        if (temporary == NULL)
        {
            return -1;
        }
        Repository->Array = temporary;
    }*/
    if(MaintainRepositoryIncreasing(&Repository) != 0)
    {
        return -1;
    }

    Repository->Array[Repository->Count] = Produs;
    Repository->Count = Repository->Count + 1;

    return 0;
}

static int MaintainRepositoryDecreasing(PREPOSITORY_PRODUSE* Repository)
{
    if(Repository == NULL)
    {
        return -1;
    }

    if ((*Repository)->Size > INITIAL_SIZE && (*Repository)->Size / (*Repository)->Count > RM)
    {
        (*Repository)->Size = (*Repository)->Size / RM;
        PPRODUS* temporary = realloc((*Repository)->Array, sizeof(PRODUS*) * (*Repository)->Size);
        if (temporary == NULL)
        {
            perror("The repository could not be alocated");
            exit(1);
        }
        (*Repository)->Array = temporary;
    }

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

    /*if (Repository->Size > INITIAL_SIZE && Repository->Size / Repository->Count > RM)
    {
        Repository->Size = Repository->Size / RM;
        PPRODUS* temporary = realloc(Repository->Array, sizeof(PRODUS*) * Repository->Size);
        if (temporary == NULL)
        {
            perror("The repository could not be alocated");
            exit(1);
        }
        Repository->Array = temporary;
    }*/
    if(MaintainRepositoryDecreasing((&Repository)) != 0)
    {
        return -1;
    }

    return returnValue;
}

int ModifyProdus(PREPOSITORY_PRODUSE Repository, int Id, double Pret, int Cantitate)
{
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

    int count = GetLength(Repository);
    PPRODUS newArray = (PPRODUS)malloc(sizeof(PRODUS) * count);
    if (newArray == NULL)
    {
        return -1;
    }

    for (int i = 0; i < count; ++i)
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

    free(*Repository);

    return 0;
}

int GetLength(PREPOSITORY_PRODUSE Repository)
{
    return Repository->Count;
}

static void testRepository()
{
    PREPOSITORY_PRODUSE Repo = NULL;
    assert(CreateRepository(&Repo) == 0);
    assert(GetLength(Repo) == 0);

    PPRODUS Produs = (PPRODUS)malloc(sizeof(PRODUS));
    CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10);
    PPRODUS Result = (PPRODUS)malloc(sizeof(PRODUS));

    assert(InsertProdus(Repo, Produs) == 0);
    assert(GetLength(Repo) == 1);
    assert(SearchProdus(Repo, 6, Result) == 0);
    assert(ProdusEqual(*Produs, *Result) == 1);

    PRODUS ProdusInexistent = { 3, "televizor", "Samsung", "Wow", 3299.99, 10 };
    assert(SearchProdus(Repo, 3, Result) == -1);

    PPRODUS ProdusNou = (PPRODUS)malloc(sizeof(PRODUS)); 
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
}

void testInfrastructure()
{
    testRepository();
}