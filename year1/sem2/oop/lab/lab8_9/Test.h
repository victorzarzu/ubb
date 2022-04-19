#pragma once
#include "TestMasina.h"
#include "TestRepo.h"
#include "TestValidatorMasina.h"
#include "TestStore.h"
#include "TestMasiniSpalate.h"
#include "TestUndo.h"

class Test
{
private:
	const TestMasina& tMasina;
	const TestRepo& tRepo;
	const TestValidatorMasina& tValidator;
	const TestStore& tStore;
	const TestMasiniSpalate& tMasiniSpalate;
	const TestUndo& tUndo;
public:

	Test(const TestMasina& tMasina, const TestRepo& tRepo, const TestValidatorMasina& tValidator, const TestStore& tStore, const TestMasiniSpalate& tMasiniSpalate, const TestUndo& tUndo) noexcept : tMasina{ tMasina }, tRepo{ tRepo }, tValidator{ tValidator }, tStore{ tStore }, tMasiniSpalate{ tMasiniSpalate }, tUndo{ tUndo } { };
	void runAllTests() const;
};

