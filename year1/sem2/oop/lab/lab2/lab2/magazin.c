#include "presentation.h"
#include "validation.h"
#include "infrastructure.h"
#include "service.h"
#include "testing.h"

int main()
{
    runAllTests();

    ValidationFunction validator = ValidateProdus;

    PREPOSITORY_PRODUSE repository = NULL;
    if (CreateRepository(&repository) != 0)
    {
        exit(-1);
    }

    PSERVICE_PRODUCTS service = NULL;
    if (CreateService(&service, repository, validator) != 0)
    {
        if (DestroyRepository(&repository) != 0)
        {
            exit(-1);
        }
        exit(-1);
    }

    PCONSOLE console = NULL;
    if (CreateConsole(&console, service) != 0)
    {
        if (DestroyService(&service) != 0)
        {
            if (DestroyRepository(&repository) != 0)
            {
                exit(-1);
            }
            exit(-1);
        }
        exit(-1);
    }

    runConsole(console);

    if (DestroyConsole(&console) != 0)
    {
        if (DestroyService(&service) != 0)
        {
            if (DestroyRepository(&repository) != 0)
            {
                exit(-1);
            }
            exit(-1);
        }
        exit(-1);
    }

    return 0;
}