#define _CRTDBG_MAP_ALLOC

#include "Test.h"
#include "TestMasina.h"
#include "TestRepo.h"
#include "TestValidatorMasina.h"
#include "TestStore.h"
#include "TestMasiniSpalate.h"
#include "TestUndo.h"

#include "CarRepo.h"
#include "CarRepoFile.h"
#include "MasiniSpalate.h"
#include "ValidatorMasina.h"
#include "CarStore.h"
#include "Console.h"

#include <crtdbg.h>

int main() {
	TestMasina const tMasina{};
	TestRepo const tRepo{};
	TestValidatorMasina const tValidator{};
	TestStore const tStore{};
	TestMasiniSpalate const tMasiniSpalate{};
	TestUndo const tUndo{};

	Test const test{ tMasina, tRepo, tValidator, tStore, tMasiniSpalate, tUndo };

	test.runAllTests();

	if (true) {
		CarRepo repo{};
		CarRepoFile repoFile{ "data.out" };
		ValidatorMasina const validator{};
		CarStore service{ repoFile, validator };
		ConsoleUI console{ service };

		//console.run();
	}


	_CrtDumpMemoryLeaks();

	return 0;
}