#include "domain.h"
#include "validation.h"

int GetId(PRODUS Produs)
{
    return Produs.Id;
}

void SetId(PPRODUS Produs, int Id)
{
    Produs->Id = Id;
}

char* GetTip(PRODUS Produs)
{
    return Produs.Tip;
}

void SetTip(PPRODUS Produs, char* Tip)
{
    int lenTip = strlen(Tip) + 1;
    char* newTip = (char*)malloc(lenTip * sizeof(char));
    /*if (newTip == NULL)
    {
        return;
    }*/
    strcpy(newTip, Tip);

    free(Produs->Tip);
    Produs->Tip = newTip;
}

char* GetProducator(PRODUS Produs)
{
    return Produs.Producator;
}

void SetProducator(PPRODUS Produs, char* Producator)
{
    int lenProducator = strlen(Producator) + 1;
    char* newProducator = (char*)malloc(lenProducator * sizeof(char));
    /*if (newProducator == NULL)
    {
        return;
    }*/
    strcpy(newProducator, Producator);

    free(Produs->Producator);
    Produs->Producator = newProducator;
}

char* GetModel(PRODUS Produs)
{
    return Produs.Model;
}

void SetModel(PPRODUS Produs, char* Model)
{
    int lenModel = strlen(Model) + 1;
    char* newModel = (char*)malloc(lenModel * sizeof(char));
    /*if (newModel == NULL)
    {
        return;
    }*/
    strcpy(newModel, Model);

    free(Produs->Model);
    Produs->Model = newModel;
}

double GetPret(PRODUS Produs)
{
    return Produs.Pret;
}

void SetPret(PPRODUS Produs, double Pret)
{
    Produs->Pret = Pret;
}

int GetCantitate(PRODUS Produs)
{
    return Produs.Cantitate;
}

void SetCantitate(PPRODUS Produs, int Cantitate)
{
    Produs->Cantitate = Cantitate;
}

/*int PrintFormat(PRODUS Produs)
{
    printf("Tip: %s\nProducator: %s\nModel: %s\nPret: %f\nCantitate: %d\n\n", Produs.Tip, Produs.Producator, Produs.Model, Produs.Pret, Produs.Cantitate);
}*/

int ProdusEqual(PRODUS Produs1, PRODUS Produs2)
{
    if (Produs1.Id != Produs2.Id)
    {
        return 0;
    }
    if (strcmp(Produs1.Tip, Produs2.Tip) != 0)
    {
        return 0;
    }
    if (strcmp(Produs1.Producator, Produs2.Producator) != 0)
    {
        return 0;
    }
    if (strcmp(Produs1.Model, Produs2.Model) != 0)
    {
        return 0;
    }
    if (fabs(Produs1.Pret - Produs2.Pret) > epsilon)
    {
        return 0;
    }

    return 1;
}

int CompareProduseIncreasing(const PRODUS* Produs1, const void* Produs2)
{
    if (Produs1 == NULL || Produs2 == NULL)
    {
        return -1;
    }

    if (fabs(((PPRODUS)Produs1)->Pret - ((PPRODUS)Produs2)->Pret) > epsilon)
    {
        if (((PPRODUS)Produs1)->Pret < ((PPRODUS)Produs2)->Pret)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }

    if (((PPRODUS)Produs1)->Cantitate != ((PPRODUS)Produs2)->Cantitate)
    {
        if (((PPRODUS)Produs1)->Cantitate < ((PPRODUS)Produs2)->Cantitate)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}

int CompareProduseDecreasing(const void* Produs1, const void* Produs2)
{
    if (Produs1 == NULL || Produs2 == NULL)
    {
        return -1;
    }

    if (fabs(((PPRODUS)Produs1)->Pret - ((PPRODUS)Produs2)->Pret) > epsilon)
    {
        if (((PPRODUS)Produs1)->Pret < ((PPRODUS)Produs2)->Pret)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    if (((PPRODUS)Produs1)->Cantitate != ((PPRODUS)Produs2)->Cantitate)
    {
        if (((PPRODUS)Produs1)->Cantitate < ((PPRODUS)Produs2)->Cantitate)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}

int CreateProdus(PPRODUS* Produs, int Id, char* Tip, char* Producator, char* Model, double Pret, int Cantitate)
{
    if (Produs == NULL)
    {
        return -1;
    }

    PPRODUS produs = (PPRODUS)malloc(sizeof(PRODUS));
    /*if (produs == NULL)
    {
        return -1;
    }*/

    produs->Id = Id;

    int tipLength = strlen(Tip);
    char* tip = (char*)malloc(sizeof(char) * (tipLength + 1));
    /*if (tip == NULL)
    {
        free(produs);
        return -1;
    }*/
    strcpy(tip, Tip);
    produs->Tip = tip;

    int producatorLength = strlen(Producator);
    char* producator = (char*)malloc(sizeof(char) * (producatorLength + 1));
    /*if (producator == NULL)
    {
        free(tip);
        free(produs);
        return -1;
    }*/
    strcpy(producator, Producator);
    produs->Producator = producator;

    int modelLength = strlen(Model);
    char* model = (char*)malloc(sizeof(char) * (modelLength + 1));
    /*if (model == NULL)
    {
        free(tip);
        free(producator);
        free(produs);
        return -1;
    }*/
    strcpy(model, Model);
    produs->Model = model;

    produs->Pret = Pret;
    produs->Cantitate = Cantitate;

    *Produs = produs;
    return 0;
}

int DestroyProdus(PPRODUS* Produs)
{
    if (Produs == NULL)
    {
        return -1;
    }

    free((*Produs)->Tip);
    free((*Produs)->Producator);
    free((*Produs)->Model);
    free(*Produs);
    *Produs = NULL;

    return 0;
}

static void testCreateAndDestroy()
{
    PPRODUS Produs;
    assert(CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10) == 0);

    assert(CreateProdus(NULL, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10) == -1);

    assert(DestroyProdus(NULL) == -1);
    assert(DestroyProdus(&Produs) == 0);
    assert(Produs == NULL);
}

static void testGetAndSet()
{
    PPRODUS Produs;
    assert(CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10) == 0);
    SetId(Produs, 6);
    assert(GetId(*Produs) == 6);

    SetId(Produs, 6);
    assert(GetId(*Produs) == 6);

    SetTip(Produs, "laptop");
    assert(strcmp(GetTip(*Produs), "laptop") == 0);

    SetProducator(Produs, "Lenovo");
    assert(strcmp(GetProducator(*Produs), "Lenovo") == 0);

    SetModel(Produs, "IE 652");
    assert(strcmp(GetModel(*Produs), "IE 652") == 0);

    SetPret(Produs, 3299.99);
    assert(fabs(GetPret(*Produs) - 3299.99) <= epsilon);

    SetCantitate(Produs, 10);
    assert(GetCantitate(*Produs) == 10);

    SetModel(Produs, "new model");
    assert(strcmp(GetModel(*Produs), "new model") == 0);

    SetPret(Produs, 567.98);
    assert(fabs(GetPret(*Produs) - 567.98) <= epsilon);

    SetCantitate(Produs, 7);
    assert(GetCantitate(*Produs) == 7);

    PPRODUS ProdusCreat = NULL;
    assert(CreateProdus(&ProdusCreat, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10) == 0);
    assert(GetId(*ProdusCreat) == 6);
    assert(strcmp(GetTip(*ProdusCreat), "laptop") == 0);
    assert(strcmp(GetProducator(*ProdusCreat), "Lenovo") == 0);
    assert(strcmp(GetModel(*ProdusCreat), "IE 652") == 0);
    assert(fabs(GetPret(*ProdusCreat) - 3299.99) <= epsilon);
    assert(GetCantitate(*ProdusCreat) == 10);

    assert(DestroyProdus(&ProdusCreat) == 0);
    assert(ProdusCreat == NULL);

    assert(DestroyProdus(&Produs) == 0);
    assert(Produs == NULL);
}

static void testCompare()
{
    PPRODUS Produs;
    assert(CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10) == 0);

    PRODUS ProdusIdentic = *Produs;
    assert(ProdusEqual(*Produs, ProdusIdentic) == 1);

    PPRODUS ProdusDiferit;
    assert(CreateProdus(&ProdusDiferit, 6, "televizor", "Dell", "IE 652", 3299.99, 5) == 0);
    assert(ProdusEqual(*Produs, *ProdusDiferit) == 0);

    SetTip(ProdusDiferit, "laptop");
    SetProducator(ProdusDiferit, "Lenovo");
    SetTip(ProdusDiferit, "IE 652");
    SetCantitate(ProdusDiferit, 10);
    SetPret(ProdusDiferit, 3299.98);
    assert(ProdusEqual(*Produs, *ProdusDiferit) == 0);
    assert(CompareProduseIncreasing(Produs, ProdusDiferit) == 1);
    assert(CompareProduseDecreasing(Produs, ProdusDiferit) == -1);
    assert(CompareProduseIncreasing(ProdusDiferit, Produs) == -1);
    assert(CompareProduseDecreasing(ProdusDiferit, Produs) == 1);

    SetPret(ProdusDiferit, 3299.99);
    SetCantitate(ProdusDiferit, 10);
    assert(CompareProduseIncreasing(Produs, ProdusDiferit) == 0);
    assert(CompareProduseDecreasing(Produs, ProdusDiferit) == 0);

    SetCantitate(Produs, 5);
    assert(CompareProduseIncreasing(Produs, ProdusDiferit) == -1);
    assert(CompareProduseDecreasing(Produs, ProdusDiferit) == 1);
    assert(CompareProduseIncreasing(ProdusDiferit, Produs)  == 1);
    assert(CompareProduseDecreasing(ProdusDiferit, Produs) == -1);

    SetTip(ProdusDiferit, "laptop");
    SetProducator(ProdusDiferit, "Dell");
    assert(ProdusEqual(*Produs, *ProdusDiferit) == 0);
    SetProducator(ProdusDiferit, "Lenovo");
    SetModel(ProdusDiferit, "altceva");
    assert(ProdusEqual(*Produs, *ProdusDiferit) == 0);
    SetModel(ProdusDiferit, "IE 652");
    SetPret(ProdusDiferit, 20.65);
    assert(ProdusEqual(*Produs, *ProdusDiferit) == 0);

    assert(CompareProduseIncreasing(Produs, NULL) == -1);
    assert(CompareProduseDecreasing(NULL, ProdusDiferit) == -1);

    assert(DestroyProdus(&Produs) == 0);
    assert(DestroyProdus(&ProdusDiferit) == 0);
}

static testValidate()
{
    PPRODUS Produs;
    assert(CreateProdus(&Produs, 6, "laptop", "Lenovo", "IE 652", 3299.99, 10) == 0);
    char* errors = (char*)malloc(100 * sizeof(char));
    errors[0] = NULL;

    SetModel(Produs, "new model");
    assert(strcmp(GetModel(*Produs), "new model") == 0);

    SetPret(Produs, 567.98);
    assert(fabs(GetPret(*Produs) - 567.98) <= epsilon);

    SetCantitate(Produs, 7);
    assert(GetCantitate(*Produs) == 7);

    assert(ValidateProdus(*Produs, errors) == 0);

    PPRODUS ProdusInvalid;
    assert(CreateProdus(&ProdusInvalid, -1, "ceva", "Dell", "a", -15.9, 4) == 0);

    assert(ValidateProdus(*ProdusInvalid, errors) == -1);
    assert(strcmp(errors, "Invalid id!\nInvalid price!\n") == 0);

    SetTip(ProdusInvalid, "");
    SetProducator(ProdusInvalid, "");
    SetModel(ProdusInvalid, "");
    SetCantitate(ProdusInvalid, -4);
    assert(ValidateProdus(*ProdusInvalid, errors) == -1);
    assert(strcmp(errors, "Invalid id!\nInvalid type!\nInvalid manufacturer!\nInvalid model!\nInvalid price!\nInvalid quantity!\n") == 0);

    assert(DestroyProdus(&Produs) == 0);
    assert(DestroyProdus(&ProdusInvalid) == 0);

    free(errors);
}

void testDomain()
{
    testCreateAndDestroy();
    testGetAndSet();
    testCompare();
    testValidate();
}