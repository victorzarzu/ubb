#include "infrastructure.h"

MY_LIST* CreateList()
{
    MY_LIST* List = malloc(sizeof(MY_LIST));
    /*if (Repo == NULL)
    {
        return -1;
    }*/

    List->Array = (ElemType*)malloc(INITIAL_SIZE * sizeof(ElemType));
    List->Count = 0;
    List->Size = INITIAL_SIZE;

    return List;
}

ElemType GetElement(PMY_LIST List, int Position)
{
    return List->Array[Position];
}

ElemType SetElement(PMY_LIST List, int Position, ElemType Tranzactie)
{
    ElemType Result = GetElement(List, Position);
    List->Array[Position] = Tranzactie;
    return Result;
}

void MaintainListAbove(PMY_LIST List)
{
    if (List->Count == List->Size)
    {
        List->Size = List->Size * 2;
        ElemType* temporary = (ElemType*)malloc(sizeof(ElemType) * List->Size);
        /*if (temporary == NULL)
        {
            return 0;
        }*/
        for (int i = 0; i < List->Count; ++i)
        {
            temporary[i] = List->Array[i];
        }
        free(List->Array);
        List->Array = temporary;
    }
}

int Insert(PMY_LIST List, ElemType Element)
{
    MaintainListAbove(List);

    List->Array[List->Count] = Element;
    List->Count = List->Count + 1;

    return 0;
}

 void MaintainListBelow(PMY_LIST List)
{
    if (List->Size > INITIAL_SIZE && List->Size / List->Count > RM)
    {
        List->Size = List->Size / RM;
        ElemType* temporary = (ElemType*)malloc(sizeof(ElemType) * List->Size);
        /*if (temporary == NULL)
        {
            perror("The List could not be alocated");
            exit(1);
        }*/
        for (int i = 0; i < List->Count; ++i)
        {
            temporary[i] = List->Array[i];
        }
        free(List->Array);
        List->Array = temporary;
    }
}

int SearchTranzactie(PMY_LIST List, int Id, ElemType* Result)
{
     ElemType Tranzactie;
     for (int i = 0; i < List->Count; ++i)
     {
         Tranzactie = GetElement(List, i);
         if (GetId(Tranzactie) == Id)
         {
             *Result = Tranzactie;
             return 0;
         }
     }

     return -1;
 }

int Delete(PMY_LIST List, int Id, DestroyFunction destrF)
{
    ElemType Tranzactie;
    int returnValue = -1;
    for (int i = 0; i < List->Count; ++i)
    {
        Tranzactie = GetElement(List, i);
        if (GetId(Tranzactie) == Id)
        {
            /*if (DestroyProdus(&(List->Array[i])) != 0)
            {
                return -1;
            }*/
            destrF(List->Array[i]);
            for (int j = i; j < List->Count - 1; ++j)
                List->Array[j] = List->Array[j + 1];
            returnValue = 0;
            List->Count = (List->Count) - 1;
            break;
        }
    }

    MaintainListBelow(List);

    return returnValue;
}

ElemType RemoveLast(PMY_LIST List)
{
    ElemType last = GetElement(List, List->Count - 1);
    List->Count -= 1;
    return last;
}

int ClearList(PMY_LIST List, DestroyFunction destrF)
{
    if (List == NULL)
    {
        return -1;
    }

    while (GetLength(List) > 0)
    {
        ElemType Tranzactie = GetElement(List, 0);
        /*if (DeleteProdus(List, id) != 0)
        {
            return -1;
        }*/
        Delete(List, GetId(Tranzactie), destrF);
    }

    return 0;
}

MY_LIST* CopyList(PMY_LIST List)
{
    MY_LIST* ListCopy;
    ListCopy = CreateList();

    int length = GetLength(List);
    ElemType Tranzactie;
    for (int i = 0; i < length; ++i)
    {
        Tranzactie = GetElement(List, i);
        ElemType TranzactieInsert = CopyTranzactie(Tranzactie);
        Insert(ListCopy, TranzactieInsert);
    }

    return ListCopy;
}

void DestroyList(MY_LIST* List)
{
    Destroy(List, DestroyTranzactie);
}

int Destroy(PMY_LIST List, DestroyFunction destrF)
{
    if (List == NULL)
    {
        return -1;
    }

    /*if (ClearList(*List) != 0)
    {
        return -1;
    }*/
    int count = GetLength(List);
    for (int i = 0; i < count; ++i)
    {
        ElemType Element = GetElement(List, i);
        destrF(Element);
    }

    free(List->Array);
    free(List);

    return 0;
}

int GetLength(PMY_LIST List)
{
    return List->Count;
}

static void testCreateDestroy()
{
    MY_LIST* List;

    List = CreateList();
    assert(GetLength(List) == 0);

    assert(Destroy(NULL, DestroyList) == -1);
    assert(Destroy(List, DestroyList) == 0);
}

static void testInsert()
{
    MY_LIST* List;
    List = CreateList();
    assert(GetLength(List) == 0);

    ElemType Tranzactie1, Tranzactie2, Tranzactie3;
    Tranzactie1 = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(Insert(List, Tranzactie1) == 0);
    assert(GetLength(List) == 1);

    Tranzactie3 = CreateTranzactie(8, 156, 1967.9, 1, "altceva");
    assert(Insert(List, Tranzactie3) == 0);
    assert(GetLength(List) == 2);

    ElemType Result;
    Result = GetElement(List, 1);
    assert(TranzactieEqual(Result, Tranzactie3) == 1);

    ElemType TranzactieNoua = CreateTranzactie(5, 16, 1967.9, 1, "altceva");
    Result = SetElement(List, 1, TranzactieNoua);
    assert(TranzactieEqual(Result, Tranzactie3) == 1);
    DestroyTranzactie(Result);

    Result = GetElement(List, 1);
    assert(TranzactieEqual(Result, TranzactieNoua) == 1);

    for (int i = 0; i < 120; ++i)
    {
        Tranzactie2 = CreateTranzactie(i + 10, 6, 6, 6, "trsa");
        assert(Insert(List, Tranzactie2) == 0);
        assert(GetLength(List) == i + 3);
    }

    assert(GetLength(List) == 122);
    assert(Destroy(List, DestroyTranzactie) == 0);
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

static void testDelete()
{
    MY_LIST* List;
    List = CreateList();
    assert(GetLength(List) == 0);

    ElemType Tranzactie;
    Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(Insert(List, Tranzactie) == 0);
    assert(GetLength(List) == 1);

    assert(Delete(List, 6, DestroyTranzactie) == 0);
    assert(GetLength(List) == 0);

    assert(Delete(List, 6, DestroyTranzactie) == -1);

    for (int i = 0; i < 120; ++i)
    {
        Tranzactie = CreateTranzactie(i + 10, 16, 15.76, 0, "ceva");
        assert(Insert(List, Tranzactie) == 0);
    }
    for (int i = 0; i < 120; ++i)
    {
        assert(Delete(List, i + 10, DestroyTranzactie) == 0);
        assert(GetLength(List) == 120 - i - 1);
    }

    assert(GetLength(List) == 0);

    assert(Destroy(List, DestroyTranzactie) == 0);
}

static void testClear()
{
    MY_LIST* List;
    List = CreateList();
    assert(GetLength(List) == 0);

    ElemType Tranzactie;

    for (int i = 0; i < 120; ++i)
    {
        Tranzactie = CreateTranzactie(i, 16, 15.76, 0, "ceva");
        assert(Insert(List, Tranzactie) == 0);
    }
    assert(GetLength(List) == 120);
    assert(ClearList(NULL, DestroyTranzactie) == -1);

    assert(ClearList(List, DestroyTranzactie) == 0);
    assert(GetLength(List) == 0);

    assert(Destroy(List, DestroyTranzactie) == 0);
}

static void testCopyList()
{
    ElemType* Result = (ElemType*)malloc(sizeof(ElemType));
    ElemType* Result1 = (ElemType*)malloc(sizeof(ElemType));

    MY_LIST* List;
    List = CreateList();
    assert(GetLength(List) == 0);

    ElemType Tranzactie;
    Tranzactie = CreateTranzactie(6, 16, 15.76, 0, "ceva");
    assert(Insert(List, Tranzactie) == 0);

    ElemType TranzactieNoua;
    TranzactieNoua = CreateTranzactie(8, 16, 165634, 1, "ceva");
    assert(Insert(List, TranzactieNoua) == 0);

    MY_LIST* ListCopy;
    ListCopy = CopyList(List);
    assert(SearchTranzactie(List, 6, Result) == 0);
    assert(SearchTranzactie(ListCopy, 6, Result1) == 0);
    assert(TranzactieEqual(*Result, *Result1) == 1);
    assert(SearchTranzactie(List, 8, Result) == 0);
    assert(SearchTranzactie(ListCopy, 8, Result1) == 0);
    assert(TranzactieEqual(*Result, *Result1) == 1);

    assert(Destroy(List, DestroyTranzactie) == 0);
    assert(Destroy(ListCopy, DestroyTranzactie) == 0);

    free(Result);
    free(Result1);
}

static void testListeDeListe()
{
    MY_LIST* List = CreateList();
    Insert(List, CreateTranzactie(5, 15, 16.7, 0, "ceva"));
    Insert(List, CreateTranzactie(9, 15, 16.7, 0, "altceva"));

    MY_LIST* List1 = CreateList();
    MY_LIST* UndoL = CreateList();
    Insert(UndoL, List);
    assert(GetLength(UndoL) == 1);
    Insert(UndoL, List1);
    assert(GetLength(UndoL) == 2);

    Destroy(UndoL, DestroyList);
}

void testInfrastructure()
{
    testCreateDestroy();
    testInsert();
    testSearch();
    testDelete();
    testClear();
    testCopyList();
    testListeDeListe();
}