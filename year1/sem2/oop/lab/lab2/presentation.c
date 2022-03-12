#include "presentation.h"
#include "utils.h"

int readCommand()
{
    printf("Give a command: \n0 - Exit\n1 - Add a product\n2 - Delete a product\n3 - Modify a product\n4 - View products\n5 - Filter products\n");
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

int CreateConsole(PCONSOLE* Console, PSERVICE_PRODUCTS ServiceProduse)
{
    if (Console == NULL || ServiceProduse == NULL)
    {
        return -1;
    }

    PCONSOLE console = (PCONSOLE)malloc(sizeof(CONSOLE));
    if (console == NULL)
    {
        return -1;
    }

    console->ServiceProduse = ServiceProduse;

    *Console = console;

    return 0;
}

int DestroyConsole(PCONSOLE* Console)
{
    if (Console == NULL)
    {
        return -1;
    }

    PREPOSITORY_PRODUSE service = (*Console)->ServiceProduse;
    if (DestroyService(&service) != 0)
    {
        return -1;
    }

    free(*Console);

    return 0;
}

int consoleAddProdus(PCONSOLE Console, char* errors)
{
    errors[0] = NULL;
    int id, cantitate;
    char *tip, *producator, *model;

    tip = (char*)malloc(INPUT_SIZE * sizeof(char));
    producator = (char*)malloc(INPUT_SIZE * sizeof(char));
    model = (char*)malloc(INPUT_SIZE * sizeof(char));

    double pret;
    
    if (tip == NULL || producator == NULL || model == NULL)
    {
        if (tip != NULL)
        {
            free(tip);
        }

        if (producator != NULL)
        {
            free(producator);
        }

        if (model != NULL)
        {
            free(model);
        }

        strcat(errors, "The adding failed!\n");
        return -1;
    }

    printf("Id: ");
    if (scanf_s("%d", &id) != 1)
    {
        free(tip);
        free(producator);
        free(model);
        strcat(errors, "Could not read the id!\n");
        return -1;
    }
    printf("Type: ");
    if (scanf("%20s", tip) != 1)
    {
        free(tip);
        free(producator);
        free(model);
        strcat(errors, "Could not read the type!\n");
        return -1;
    }
    printf("Manufacturer: ");
    if (scanf("%20s", producator) != 1)
    {
        free(tip);
        free(producator);
        free(model);
        strcat(errors, "Could not read the manufacturer!\n");
        return -1;
    }
    printf("Model: ");
    if (scanf("%20s", model) != 1)
    {
        free(tip);
        free(producator);
        free(model);
        strcat(errors, "Could not read the model!\n");
        return -1;
    }
    printf("Price: ");
    if (scanf("%lf", &pret) != 1)
    {
        free(tip);
        free(producator);
        free(model);
        strcat(errors, "Could not read the price!\n");
        return -1;
    }
    printf("Quantity: ");
    if (scanf("%d", &cantitate) != 1)
    {
        free(tip);
        free(producator);
        free(model);
        strcat(errors, "Could not read the quantity!\n");
        return -1;
    }
    printf("\n");

    if (StoreProdus(Console->ServiceProduse, id, tip, producator, model, pret, cantitate, errors) != 0)
    {
        free(tip);
        free(producator);
        free(model);
        strcat(errors, "The adding failed!\n");
        return -1;
    }

    free(tip);
    free(producator);
    free(model);

    return 0;
}

int consoleDeleteProdus(PCONSOLE Console, char* errors)
{
    errors[0] = NULL;
    int id;

    printf("Id: ");
    if (scanf_s("%d", &id) != 1)
    {
        strcat(errors, "Could not read the id!\n");
        return -1;
    }

    if (EraseProdus(Console->ServiceProduse, id, errors) != 0)
    {
        return -1;
    }

    return 0;
}

int consoleModifyProdus(PCONSOLE Console, char* errors)
{
    errors[0] = NULL;
    int id, cantitate = -oo;
    double pret = -oo;

    int modifyType;
    printf("0 - Modify just the price\n1 - Modify just the quantity\n2 - Modify both\n");
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

    if (modifyType == 0 || modifyType == 2)
    {
        printf("New price: ");
        if (scanf_s("%lf", &pret) != 1)
        {
            strcat(errors, "Could not read the price!\n");
            return -1;
        }
    }

    if (modifyType == 1 || modifyType == 2)
    {
        printf("New quantity: ");
        if (scanf_s("%d", &cantitate) != 1)
        {
            strcat(errors, "Could not read the quantity!\n");
            return -1;
        }
    }

    if (ChangeProdus(Console->ServiceProduse, id, pret, cantitate, errors) != 0)
    {
        strcat(errors, "The changing failed!\n");
        return -1;
    }

    return 0;
}

int consoleViewProduse(PCONSOLE Console, char* errors)
{
    errors[0] = NULL;
    int mode;

    printf("0 - Increasing mode\n1 - Decreasing mode\n");

    printf("Mode: ");
    if (scanf_s("%d", &mode) != 1)
    {
        strcat(errors, "Could not read the mode!\n");
        return -1;
    }

    if (mode != 0 && mode != 1)
    {
        strcat(errors, "The mode must be 0 or 1!\n");
        return -1;
    }

    PPRODUS Array;
    if (ViewProduse(Console->ServiceProduse, mode, &Array, errors) != 0)
    {
        strcat(errors, "The viewing failed!\n");
        return -1;
    }

    int count = GetLength(Console->ServiceProduse->Repository);
    for (int i = 0; i < count; ++i)
    {
        PrintFormat(Array[i]);
    }

    free(Array);

    return 0;
}

int consoleFilterProduse(PCONSOLE Console, char* errors)
{
    errors[0] = NULL;
    char *producator = (char*)malloc(INPUT_SIZE * sizeof(char));
    if (producator == NULL)
    {
        strcat(errors, "The filtering failed!\n");
        return -1;
    }
    double pret;
    int cantitate, number;

    printf("For every filter type -1 if you do not want to filter by it\n");

    printf("Manufacturer: ");
    if (scanf("%20s", producator) != 1)
    {
        free(producator);
        strcat(errors, "Could not read the mode!\n");
        return -1;
    }
    printf("Price: ");
    if (scanf("%lf", &pret) != 1)
    {
        free(producator);
        strcat(errors, "Could not read the price!\n");
        return -1;
    }
    printf("Quantity: ");
    if (scanf("%d", &cantitate) != 1)
    {
        free(producator);
        strcat(errors, "Could not read the quantity!\n");
        return -1;
    }

    PPRODUS Array;
    if (FilterProduse(Console->ServiceProduse, producator, pret, cantitate, &Array, &number, errors) != 0)
    {
        free(producator);
        return -1;
    }

    for (int i = 0; i < number; ++i)
    {
        PrintFormat(Array[i]);
    }

    free(Array);
    free(producator);

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
            returnValue = consoleAddProdus(Console, errors);
        }
        else if (command == 2)
        {
            returnValue = consoleDeleteProdus(Console, errors);
        }
        else if (command == 3)
        {
            returnValue = consoleModifyProdus(Console, errors);
        }
        else if (command == 4)
        {
            returnValue = consoleViewProduse(Console, errors);
        }
        else if (command == 5)
        {
            returnValue = consoleFilterProduse(Console, errors);
        }
        else
        {
            printf("Invalid command!\n");
            continue;
        }

        if (returnValue != 0)
        {
            while ((command = getchar()) != '\n' && command != EOF);
            printf("%s", errors);
        }
    }

    free(errors);

    return 0;
}