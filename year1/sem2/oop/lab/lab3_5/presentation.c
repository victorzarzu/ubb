#define _CRT_SECURE_NO_WARNINGS
#include "presentation.h"
#include "utils.h"

int readCommand()
{
    printf("Give a command: \n0 - Exit\n1 - Add a transaction\n2 - Delete a transaction\n3 - Modify a transaction\n4 - View transactions\n5 - Filter transactions\n6 - Undo\n");
    char strCommand[2];
    int command;
    if (scanf("%1s", strCommand) != 1)
    {
        return -1;
    }

    while ((command = getchar()) != '\n' && command != EOF);

    if (isInteger(strCommand) != 1)
    {
        return -1;
    }

    return atoi(strCommand);
}

CONSOLE CreateConsole(SERVICE_TRANZACTII ServiceTranzactii)
{
    CONSOLE console;

    console.ServiceTranzactii = ServiceTranzactii;

    return console;
}

void DestroyConsole(CONSOLE* Console)
{
    DestroyService(&(Console->ServiceTranzactii));
}

static int consoleAddTranzactie(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    int id, zi, tipInt;
    double suma;
    char *descriere, *tip;

    descriere = (char*)malloc(INPUT_SIZE * sizeof(char));
    tip = (char*)malloc(INPUT_SIZE * sizeof(char));

    if (tip == NULL || descriere == NULL)
    {
        free(tip);
        free(descriere);
        strcat(errors, "The adding failed!\n");
        return -1;
    }

    printf("Id: ");
    if (scanf_s("%d", &id) != 1)
    {
        free(tip);
        free(descriere);
        strcat(errors, "Invalid id!\n");
        return -1;
    }
    printf("Day: ");
    if (scanf_s("%d", &zi) != 1)
    {
        free(tip);
        free(descriere);
        strcat(errors, "Invalid day!\n");
        return -1;
    }
    printf("Sum: ");
    if (scanf_s("%lf", &suma) != 1)
    {
        free(tip);
        free(descriere);
        strcat(errors, "Invalid sum!\n");
        return -1;
    }
    printf("Type: ");
    if (scanf_s("%s", tip, 20) != 1)
    {
        free(tip);
        free(descriere);
        strcat(errors, "Invalid type!\n");
        return -1;
    }
    else
    {
        if (strcmp(tip, "entry") != 0 && strcmp(tip, "exit") != 0)
        {
            tipInt = 2;
        }
        else if (strcmp(tip, "entry") == 0)
        {
            tipInt = 0;
        }
        else
        {
            tipInt = 1;
        }
    }
    printf("Description: ");
    if (scanf_s("%s", descriere, 20) != 1)
    {
        free(tip);
        free(descriere);
        strcat(errors, "Invalid description!\n");
        return -1;
    }
    printf("\n");

    if (StoreTranzactie(&(Console->ServiceTranzactii), id, zi, suma, tipInt, descriere, errors) != 0)
    {
        free(tip);
        free(descriere);
        strcat(errors, "The adding failed!\n");
        return -1;
    }

    free(tip);
    free(descriere);

    return 0;
}

static int consoleDeleteTranzactie(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    int id;

    printf("Id: ");
    if (scanf_s("%d", &id) != 1)
    {
        strcat(errors, "Could not read the id!\n");
        return -1;
    }

    if (EraseTranzactie(&(Console->ServiceTranzactii), id, errors) != 0)
    {
        return -1;
    }

    return 0;
}

int consoleModifyTranzactie(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    int id, zi = -oo;
    double suma = -oo;

    int modifyType;
    printf("0 - Modify just the day\n1 - Modify just the sum\n2 - Modify both\n");
    if (scanf_s("%d", &modifyType) != 1)
    {
        strcat(errors, "Could not read the id!\n");
        return -1;
    }

    if (modifyType != 0 && modifyType != 1 && modifyType != 2)
    {
        strcat(errors, "Invalid command!\n");
        return -1;
    }

    printf("Id: ");
    if (scanf_s("%d", &id) != 1)
    {
        strcat(errors, "Could not read the id!\n");
        return -1;
    }

    if (modifyType == 1 || modifyType == 2)
    {
        printf("New sum: ");
        if (scanf_s("%lf", &suma) != 1)
        {
            strcat(errors, "Invalid sum!\n");
            return -1;
        }
    }

    if (modifyType == 0 || modifyType == 2)
    {
        printf("New day: ");
        if (scanf_s("%d", &zi) != 1)
        {
            strcat(errors, "Invalid day!\n");
            return -1;
        }
    }
    Console->ServiceTranzactii;
    if (ChangeTranzactie(&(Console->ServiceTranzactii), id, suma, zi, errors) != 0)
    {
        strcat(errors, "The changing failed!\n");
        return -1;
    }

    return 0;
}

static int consoleViewTranzactii(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    int mode, ascMode;

    printf("0 - By day\n1 - By sum\n");

    printf("Mode: ");
    if (scanf_s("%d", &mode) != 1)
    {
        strcat(errors, "Could not read the mode!\n");
        return -1;
    }

    printf("0 - Ascending\n1 - Descending\n");
    printf("Ascending mode: ");
    if (scanf_s("%d", &ascMode) != 1)
    {
        strcat(errors, "Could not read the ascending mode!\n");
        return -1;
    }

    if ((mode != 0 && mode != 1) || (ascMode != 0 && ascMode != 1))
    {
        strcat(errors, "The mode must be 0 or 1!\n");
        return -1;
    }

    MY_LIST* Array;

    Array = ViewTranzactii(&(Console->ServiceTranzactii), mode, ascMode, errors);

    int count = GetLength(Array);
    for (int i = 0; i < count; ++i)
    {
        ElemType Tranzactie = GetElement(Array, i);
        printf("Day: %d\nSum: %lf\nType: ", GetZi(Tranzactie), GetSuma(Tranzactie));
        int tip = GetTip(Tranzactie);
        if (tip == 0)
        {
            printf("entry\n");
        }
        else
        {
            printf("exit\n");
        }
        printf("Description: %s\n\n", GetDescriere(Tranzactie));
    }

    if (count == 0)
    {
        printf("There are not products!\n");
    }

    Destroy(Array, DestroyTranzactie);

    return 0;
}

static int consoleFilterTranzactii(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    double suma = 0;
    int tipInt = 0, sumMode = 0, mode = 0, zi = 0;

    char *tip = (char*)malloc(INPUT_SIZE * sizeof(char));

    printf("0 - Filter by type\n1 - Filter by sum\n2 - Filter by day\n");

    if (scanf("%d", &mode) != 1)
    {
        free(tip);
        strcat(errors, "Invalid mode!\n");
        return -1;
    }
    if (mode != 0 && mode != 1 && mode != 2)
    {
        free(tip);
        strcat(errors, "Invalid mode!\n");
        return -1;
    }

    if (mode == 0)
    {
        printf("Type: ");
        if (scanf_s("%s", tip, 20) != 1)
        {
            free(tip);
            strcat(errors, "Invalid type!\n");
            return -1;
        }

        if (strcmp(tip, "entry") != 0 && strcmp(tip, "exit") != 0)
        {
            free(tip);
            strcat(errors, "Invalid type!\n");
            return -1;
        }
        else if (strcmp(tip, "entry") == 0)
        {
            tipInt = 0;
        }
        else
        {
            tipInt = 1;
        }
    }
    else if(mode == 1)
    {
        printf("Sum: ");
        if (scanf("%lf", &suma) != 1)
        {
            free(tip);
            strcat(errors, "Invalid sum!\n");
            return -1;
        }

        printf("0 - Transactions with sum smaller\n1 - Transactions with sum bigger\n");
        if (scanf("%d", &sumMode) != 1)
        {
            free(tip);
            strcat(errors, "Invalid mode!\n");
            return -1;
        }
        if (sumMode != 0 && sumMode != 1)
        {
            free(tip);
            strcat(errors, "Invalid mode!\n");
            return -1;
        }
    }
    else
    {
        printf("Day: ");
        if (scanf("%d", &zi) != 1)
        {
            free(tip);
            strcat(errors, "Invalid sum!\n");
            return -1;
        }
    }

    MY_LIST* Array;
    Array = FilterTranzactii(&(Console->ServiceTranzactii), tipInt, suma, zi, mode, sumMode, errors);
    int length = GetLength(Array);

    for (int i = 0; i < length; ++i)
    {
        ElemType Tranzactie = GetElement(Array, i);
        printf("Day: %d\nSum: %lf\nType: ", GetZi(Tranzactie), GetSuma(Tranzactie));
        int tipI = GetTip(Tranzactie);
        if (tipI == 0)
        {
            printf("entry\n");
        }
        else
        {
            printf("exit\n");
        }
        printf("Description: %s\n\n", GetDescriere(Tranzactie));
    }

    if (length == 0)
    {
        printf("There are not products!\n");
    }

    free(tip);
    Destroy(Array, DestroyTranzactie);

    return 0;
}

int consoleUndo(PCONSOLE Console, char* errors)
{
    errors[0] = '\0';
    if (Undo(&(Console->ServiceTranzactii)) != 0)
    {
        strcat(errors, "No more undos!\n");
        return -1;
    }
    return 0;
}

int runConsole(PCONSOLE Console)
{
    if (Console == NULL)
    {
        return -1;
    }

    char* errors = (char*)malloc(100 * sizeof(char));
    if (errors == NULL)
    {
        return -1;
    }

    while (1)
    {
        int command = readCommand();
        int returnValue = 0;
        if (command == 0)
        {
            break;
        }
        else if (command == 1)
        {
            returnValue = consoleAddTranzactie(Console, errors);
        }
        else if (command == 2)
        {
            returnValue = consoleDeleteTranzactie(Console, errors);
        }
        else if (command == 3)
        {
            returnValue = consoleModifyTranzactie(Console, errors);
        }
        else if (command == 4)
        {
            returnValue = consoleViewTranzactii(Console, errors);
        }
        else if (command == 5)
        {
            returnValue = consoleFilterTranzactii(Console, errors);
        }
        else if (command == 6)
        {
            returnValue = consoleUndo(Console, errors);
        }
        else
        {
            printf("Invalid command!\n");
            continue;
        }

        if (returnValue != 0)
        {
            //while ((command = getchar()) != '\n' && command != EOF);
            printf("%s", errors);
        }
        printf("\n");
    }

    free(errors);

    return 0;
}