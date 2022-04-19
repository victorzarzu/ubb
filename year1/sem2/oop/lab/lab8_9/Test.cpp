#include "Test.h"

void Test::runAllTests() const {
	tMasina.runAllTests();
	tRepo.runAllTests();
	tValidator.runAllTests();
	tStore.runAllTests();
	tMasiniSpalate.runAllTests();
	tUndo.runAllTests();
}