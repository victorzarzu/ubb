#include "TestUndo.h"

void TestUndo::testUndoStore() const {
	CarRepo repo{};
	Masina masina{ "BC11AAA", "Dacia", "Logan", "berlina" };
	Masina masina1{ "BC22AAA", "Renault", "Logan", "berlina" };
	
	repo.store(masina);
	UndoStore undo{ repo, masina };
	repo.store(masina1);
	assert(repo.getLength() == 2);


	undo.doUndo();
	assert(repo.getLength() == 1);
}

void TestUndo::testUndoErase() const {
	CarRepo repo{};
	Masina masina{ "BC11AAA", "Dacia", "Logan", "berlina" };
	Masina masina1{ "BC22AAA", "Renault", "Logan", "berlina" };

	repo.store(masina);
	repo.store(masina1);
	assert(repo.getLength() == 2);

	UndoErase undo{ repo, masina1 };
	repo.erase(masina1);

	assert(repo.getLength() == 1);

	undo.doUndo();
	assert(repo.getLength() == 2);
}

void TestUndo::testUndoModify() const {
	CarRepo repo{};
	Masina masina{ "BC11AAA", "Dacia", "Logan", "berlina" };
	Masina masina1{ "BC22AAA", "Renault", "Logan", "berlina" };

	repo.store(masina);
	repo.store(masina1);
	assert(repo.getLength() == 2);

	UndoModify undo{ repo, masina };
	Masina masinaModify("BC11AAA", "Volvo", "S40", "berlina");
	repo.modify(masinaModify);

	auto m = repo.find("BC11AAA");
	assert(m.GetNrInmatriculare() == "BC11AAA");
	assert(m.GetProducator() == "Volvo");
	assert(m.GetModel() == "S40");
	assert(m.GetTip() == "berlina");

	undo.doUndo();
	m = repo.find("BC11AAA");
	assert(m.GetNrInmatriculare() == "BC11AAA");
	assert(m.GetProducator() == "Dacia");
	assert(m.GetModel() == "Logan");
	assert(m.GetTip() == "berlina");
}

void TestUndo::runAllTests() const {
	testUndoStore();
	testUndoErase();
	testUndoModify();
}