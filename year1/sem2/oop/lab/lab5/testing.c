#include "testing.h"

void runAllTests(void)
{
    testDomain();
    testInfrastructure();
    testService();
    testUtils();
    testRepository();
}