#include "GUI.h"
#include <QtWidgets/QApplication>

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

int main(int argc, char *argv[])
{
	TestMasina const tMasina{};
	TestRepo const tRepo{};
	TestValidatorMasina const tValidator{};
	TestStore const tStore{};
	TestMasiniSpalate const tMasiniSpalate{};
	TestUndo const tUndo{};

	Test const test{ tMasina, tRepo, tValidator, tStore, tMasiniSpalate, tUndo };

	test.runAllTests();

	if (true) {
		QApplication a(argc, argv);
		
		CarRepo repo{};
		CarRepoFile repoFile{ "data.out" };
		ValidatorMasina const validator{};
		CarStore service{ repoFile, validator };
		GUI console{ service, validator };

		console.run();

		return a.exec();
	}

}
