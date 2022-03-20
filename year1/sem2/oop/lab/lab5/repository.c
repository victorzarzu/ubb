#include "repository.h"

PREPOSITORY CreateRepository()
{
    PREPOSITORY Repository = malloc(sizeof(REPOSITORY));

    Repository->List = CreateList();
    Repository->UndoList = CreateList();

    return Repository;
}

void DestroyRepository(PREPOSITORY Repository)
{
    Destroy(Repository->List, DestroyTranzactie);
    Destroy(Repository->UndoList, DestroyList);

    free(Repository);
}

int InsertTranzactie(PREPOSITORY Repository, ElemType Tranzactie)
{
    MY_LIST* Copy = CopyList(Repository->List);

    ElemType TranzactieFound;
    int count = GetLength(Repository->List);
    for (int i = 0; i < count; ++i)
    {
        TranzactieFound = GetElement(Repository->List, i);
        if (GetId(TranzactieFound) == GetId(Tranzactie))
        {
            Destroy(Copy, DestroyTranzactie);
            return -1;
        }
    }
    Insert(Repository->UndoList, Copy);

    Insert(Repository->List, Tranzactie);

    return 0;
}

int DeleteTranzactie(PREPOSITORY Repository, int Id)
{
    ElemType Tranzactie;
    int returnValue = -1;
    MY_LIST* Copy = CopyList(Repository->List);

    int count = GetLength(Repository->List);
    for (int i = 0; i < count; ++i)
    {
        Tranzactie = GetElement(Repository->List, i);
        if (GetId(Tranzactie) == Id)
        {
            /*if (DestroyProdus(&(List->Array[i])) != 0)
            {
                return -1;
            }*/
            DestroyTranzactie(Repository->List->Array[i]);
            for (int j = i; j < count - 1; ++j)
                Repository->List->Array[j] = Repository->List->Array[j + 1];
            returnValue = 0;
            Repository->List->Count = (Repository->List->Count) - 1;
            break;
        }
    }

    MaintainListBelow(Repository->List);

    if (returnValue != -1)
    {
        Insert(Repository->UndoList, Copy);
    }
    else
    {
        Destroy(Copy, DestroyTranzactie);
    }

    return returnValue;
}

int ModifyTranzactie(PREPOSITORY Repository, int Id, double Suma, int Zi)
{
    MY_LIST* Copy = CopyList(Repository->List);

    ElemType Tranzactie;
    int count = GetLength(Repository->List);
    for (int i = 0; i < count; ++i)
    {
        Tranzactie = GetElement(Repository->List, i);
        if (GetId(Tranzactie) == Id)
        {
            SetSuma((PTRANZACTIE)Tranzactie, Suma);
            SetZi((PTRANZACTIE)Tranzactie, Zi);

            Insert(Repository->UndoList, Copy);
            return 0;
        }
    }
    Destroy(Copy, DestroyTranzactie);
    return -1;
}

int UndoOperation(PREPOSITORY* Repository)
{
    if (GetLength((*Repository)->UndoList) == 0)
    {
        return -1;
    }

    MY_LIST* Last = RemoveLast((*Repository)->UndoList);
    Destroy((*Repository)->List, DestroyTranzactie);
    (*Repository)->List = Last;
    
    return 0;
}

static void testCreateAndDestroy()
{
    PREPOSITORY Repo = CreateRepository();
    assert(GetLength(Repo->List) == 0);
    assert(GetLength(Repo->UndoList) == 0);

    DestroyRepository(Repo);
}

static void testInsert()
{
    PREPOSITORY Repo = CreateRepository();
    
    ElemType Tranzactie1, Tranzactie2, Tranzactie3;
    Tranzactie1 = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(InsertTranzactie(Repo, Tranzactie1) == 0);
    assert(GetLength(Repo->List) == 1);

    assert(InsertTranzactie(Repo, Tranzactie1) == -1);

    Tranzactie3 = CreateTranzactie(8, 156, 1967.9, 1, "altceva");
    assert(InsertTranzactie(Repo, Tranzactie3) == 0);
    assert(GetLength(Repo->List) == 2);

    for (int i = 0; i < 120; ++i)
    {
        Tranzactie2 = CreateTranzactie(i + 10, 6, 6, 6, "trsa");
        assert(InsertTranzactie(Repo, Tranzactie2) == 0);
        assert(GetLength(Repo->List) == i + 3);
    }

    assert(GetLength(Repo->List) == 122);

    DestroyRepository(Repo);
}

static void testDelete()
{
    PREPOSITORY Repo = CreateRepository();

    ElemType Tranzactie;
    Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(InsertTranzactie(Repo, Tranzactie) == 0);
    assert(GetLength(Repo->List) == 1);

    assert(DeleteTranzactie(Repo, 6) == 0);
    assert(GetLength(Repo->List) == 0);

    assert(DeleteTranzactie(Repo, 6) == -1);

    for (int i = 0; i < 120; ++i)
    {
        Tranzactie = CreateTranzactie(i + 10, 16, 15.76, 0, "ceva");
        assert(InsertTranzactie(Repo, Tranzactie) == 0);
    }
    for (int i = 0; i < 120; ++i)
    {
        assert(DeleteTranzactie(Repo, i + 10) == 0);
        assert(GetLength(Repo->List) == 120 - i - 1);
    }

    assert(GetLength(Repo->List) == 0);

    DestroyRepository(Repo);
}

static void testModify()
{
    PREPOSITORY Repo = CreateRepository();

    ElemType Tranzactie;
    Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(InsertTranzactie(Repo, Tranzactie) == 0);

    assert(ModifyTranzactie(Repo, 8, 150, 6) == -1);
    assert(ModifyTranzactie(Repo, 6, 150, 6) == 0);

    ElemType Result;
    assert(SearchTranzactie(Repo->List, 6, &Result) == 0);
    assert(GetZi(Result) == 6);

    Tranzactie = CreateTranzactie(6, 6, 150, 0, "ceva");
    assert(TranzactieEqual(Tranzactie, Result) == 1);

    DestroyTranzactie(Tranzactie);

    DestroyRepository(Repo);
}

static void testSearch()
{
    MY_LIST* List;
    List = CreateList();
    assert(GetLength(List) == 0);

    ElemType Tranzactie;
    Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(Insert(List, Tranzactie) == 0);

    ElemType Result;
    assert(SearchTranzactie(List, 6, &Result) == 0);
    assert(TranzactieEqual(Result, Tranzactie) == 1);

    assert(SearchTranzactie(List, 9, &Result) == -1);

    for (int i = 0; i < 120; ++i)
    {
        Tranzactie = CreateTranzactie(i + 10, 16, 15.76, 0, "ceva");
        Insert(List, Tranzactie);
    }

    for (int i = 0; i < 120; ++i)
    {
        assert(SearchTranzactie(List, i + 10, &Result) == 0);
        assert(GetId(Result) == i + 10);
    }

    assert(Destroy(List, DestroyTranzactie) == 0);
}

static void testUndo()
{
    PREPOSITORY Repo = CreateRepository();

    ElemType Tranzactie;
    Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(InsertTranzactie(Repo, Tranzactie) == 0);
    assert(GetLength(Repo->List) == 1);

    assert(UndoOperation(&Repo) == 0);
    assert(GetLength(Repo->List) == 0);
    assert(UndoOperation(&Repo) == -1);

    Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(InsertTranzactie(Repo, Tranzactie) == 0);
    assert(GetLength(Repo->List) == 1);

    for (int i = 0; i < 10; ++i)
    {
        Tranzactie = CreateTranzactie(i + 10, 16, 15.76, 0, "ceva");
        assert(InsertTranzactie(Repo, Tranzactie) == 0);
    }

    assert(GetLength(Repo->List) == 11);
    assert(UndoOperation(&Repo) == 0);
    assert(GetLength(Repo->List) == 10);

    assert(DeleteTranzactie(Repo, 10) == 0);
    assert(GetLength(Repo->List) == 9);
    assert(UndoOperation(&Repo) == 0);
    assert(GetLength(Repo->List) == 10);

    assert(ModifyTranzactie(Repo, 6, 150, 6) == 0);

    ElemType Result;
    assert(SearchTranzactie(Repo->List, 6, &Result) == 0);
    assert(fabs(GetSuma(Result) - 150) <= epsilon);
    assert(GetZi(Result) == 6);

    assert(UndoOperation(&Repo) == 0);
    assert(SearchTranzactie(Repo->List, 6, &Result) == 0);
    assert(fabs(GetSuma(Result) - 15.76) <= epsilon);
    assert(GetZi(Result) == 16);

    DestroyRepository(Repo);
}

void testRepository()
{
    testCreateAndDestroy();
    testInsert();
    testDelete();
    testModify();
    testSearch();
    testUndo();
}