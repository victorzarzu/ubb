#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS

#include "presentation.h"
#include "validation.h"
#include "infrastructure.h"
#include "service.h"
#include "testing.h"
#include <crtdbg.h>

int main(void)
{
    runAllTests();

    ValidationFunction validator = ValidateTranzactie;

    PREPOSITORY Repository = CreateRepository();

    SERVICE_TRANZACTII service = CreateService(Repository, validator);

    CONSOLE console = CreateConsole(service);

    runConsole(&console);

    DestroyConsole(&console);

    _CrtDumpMemoryLeaks();

    return 0;
}