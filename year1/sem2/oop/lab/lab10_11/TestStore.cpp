#include "TestStore.h"

void TestStore::testAddMasina() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "berlina");

	try {
		service.addMasina("BC34ABC", "Dacia", "Logan", "berlina");
		assert(false);
	}
	catch (const CarRepoException& ex) {
		stringstream out;
		out << ex;
		assert(out.str() == "Masina deja existenta!\n");
		assert(true);
	}

	try {
		service.addMasina("B34ABC", "Dacia", "", "berlina");
		assert(false);
	}
	catch (const ValidateException& ex) {
		stringstream out;
		out << ex;
		assert(out.str() == "Numar de inmatriculare invalid!\nModel invalid!\n");
		assert(true);
	}
}

void TestStore::testGetAll() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "berlina");
	service.addMasina("BC34ABD", "Dacia", "Logan", "berlina");

	auto list = service.getAll();
	assert(list.size() == 2);
	//assert(list.at(0).GetNrInmatriculare() == "BC34ABC");
}

void TestStore::testFind() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "berlina");
	service.addMasina("BC34ABD", "Dacia", "Logan", "berlina");

	auto masinaGasita = service.findMasina("BC34ABC");
	assert(masinaGasita.GetNrInmatriculare() == "BC34ABC");
	assert(masinaGasita.GetProducator() == "Dacia");
	assert(masinaGasita.GetModel() == "Logan");
	assert(masinaGasita.GetTip() == "berlina");

	try {
		service.findMasina("BC34ABE");
		assert(false);
	}
	catch (const CarRepoException& ex) {
		stringstream out;
		out << ex;
		assert(out.str() == "Masina inexistenta!\n");
	}
}

void TestStore::testErase() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "berlina");
	service.addMasina("BC34ABD", "Dacia", "Logan", "berlina");

	service.eraseMasina("BC34ABC");
	assert(service.getAll().size() == 1);

	try {
		service.eraseMasina("BC34ABC");
		assert(false);
	}
	catch (const CarRepoException& ex) {
		stringstream out;
		out << ex;
		assert(out.str() == "Masina inexistenta!\n");
	}
}

void TestStore::testModify() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "berlina");
	service.addMasina("BC34ABD", "Dacia", "Logan", "berlina");

	service.modifyMasina("BC34ABC", "Renault", "Megane", "berlina");
	auto masinaGasita = service.findMasina("BC34ABC");
	assert(masinaGasita.GetProducator() == "Renault");
	assert(masinaGasita.GetModel() == "Megane");
	assert(masinaGasita.GetTip() == "berlina");

	try {
		service.modifyMasina("SV12TYI", "Renault", "Symbol", "break");
		assert(false);
	}
	catch (const CarRepoException& ex) {
		stringstream out;
		out << ex;
		assert(out.str() == "Masina inexistenta!\n");
	}

	try {
		service.modifyMasina("BC34ABD", "", "Symbol", "");
		assert(false);
	}
	catch (const ValidateException& ex) {
		stringstream out;
		out << ex;
		assert(out.str() == "Producator invalid!\nTip invalid!\n");
	}
}

void TestStore::testSort() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "break");
	service.addMasina("BC34ABD", "Renault", "Logan", "berlina");

	auto sorted = service.sortByNtInmatriculare();
	assert(sorted.at(0).GetNrInmatriculare() == "BC34ABC");
	assert(sorted.at(1).GetNrInmatriculare() == "BC34ABD");

	sorted = service.sortByTip();
	assert(sorted.at(1).GetNrInmatriculare() == "BC34ABC");
	assert(sorted.at(0).GetNrInmatriculare() == "BC34ABD");

	sorted = service.sortByProducatorAndModel();
	assert(sorted.at(0).GetNrInmatriculare() == "BC34ABC");
	assert(sorted.at(1).GetNrInmatriculare() == "BC34ABD");

	service.modifyMasina("BC34ABC", "Renault", "Megane", "break");
	sorted = service.sortByProducatorAndModel();
	assert(sorted.at(1).GetNrInmatriculare() == "BC34ABC");
	assert(sorted.at(0).GetNrInmatriculare() == "BC34ABD");
}

void TestStore::testFilter() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "break");
	service.addMasina("BC34ABD", "Renault", "Logan", "berlina");
	service.addMasina("BC34ABF", "Renault", "Logan", "berlina");

	auto list = service.filterByProducator("Renault");
	assert(list.size() == 2);

	list = service.filterByProducator("Dacia");
	assert(list.size() == 1);

	list = service.filterByTip("berlina");
	assert(list.size() == 2);

	list = service.filterByTip("break");
	assert(list.size() == 1);

	service.addMasina("BV34ABC", "Dacia", "Logan", "break");
	list = service.filterByTip("break");
	assert(list.size() == 2);
}

void TestStore::testAddSpalate() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "break");
	service.addMasina("BC34ABD", "Renault", "Logan", "berlina");
	service.addMasina("BC34ABF", "Renault", "Logan", "berlina");
	service.addMasina("BV34ABC", "Dacia", "Logan", "break");

	assert(service.getListSize() == 0);

	service.adaugaMasinaSpalate("BC34ABC");
	assert(service.getListSize() == 1);

	try {
		service.adaugaMasinaSpalate("BC34ABC");
		assert(false);
	}
	catch (const SpalateException& se) {
		stringstream out;
		out << se;
		assert(out.str() == "Masina deja adaugata!\n");
	}

	service.adaugaMasinaSpalate("BC34ABD");
	assert(service.getListSize() == 2);

	try {
		service.adaugaMasinaSpalate("SV34ABC");
		assert(false);
	}
	catch (const CarRepoException& re) {
		stringstream out;
		out << re;
		assert(out.str() == "Masina inexistenta!\n");
	}

	service.clearMasiniSpalate();
	assert(service.getListSize() == 0);
}

void TestStore::testSpalate() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "break");
	service.addMasina("BC34ABD", "Renault", "Logan", "berlina");
	service.addMasina("BC34ABF", "Renault", "Logan", "berlina");
	service.addMasina("BV34ABC", "Dacia", "Logan", "break");
	service.addMasina("BV34ABF", "Dacia", "Logan", "break");
	service.addMasina("BV34ABE", "Dacia", "Logan", "break");

	service.populeazaMasiniSpalate(4);
	assert(service.getListSize() == 4);

	service.exportMasiniSpalate("result.csv");

	std::ifstream in{ "result.csv" };
	string line;
	int number = 0;

	while (std::getline(in, line)) {
		number++;
	}
	assert(number == 4);

	in.close();

	auto all = service.getAllSpalate();
	assert(all.size() == 4);

	try {
		service.populeazaMasiniSpalate(7);
		assert(false);
	}
	catch (const SpalateException& se) {
		stringstream out;
		out << se;
		assert(out.str() == "Numar de masini prea mare!\n");
		}
}

void TestStore::testRaport() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "break");
	service.addMasina("BC34ABD", "Renault", "Logan", "berlina");
	service.addMasina("BC34ABF", "Renault", "Logan", "berlina");
	service.addMasina("BV34ABC", "Dacia", "Logan", "break");
	service.addMasina("BV34ABF", "Dacia", "Logan", "break");
	service.addMasina("BV34ABE", "Dacia", "Logan", "break");

	auto result = service.raportTip("break");
	assert(result.GetCount() == 4);

	result = service.raportTip("ceva");
	assert(result.GetCount() == 0);
}

void TestStore::testUndo() const {
	CarRepo repo{};
	ValidatorMasina const validator{};
	CarStore service{ repo, validator };

	service.addMasina("BC34ABC", "Dacia", "Logan", "break");
	service.addMasina("BC34ABD", "Renault", "Logan", "berlina");
	service.addMasina("BC34ABF", "Renault", "Logan", "berlina");

	service.Undo();
	assert(service.getAll().size() == 2);
	service.Undo();
	assert(service.getAll().size() == 1);
	service.Undo();
	assert(service.getAll().size() == 0);

	try {
		service.Undo();
		assert(false);
	}
	catch (const CarStoreException& ce) {
		stringstream out;
		out << ce;
		assert(out.str() == "Nu mai exista operatii de undo!\n");
	}

	service.addMasina("BC34ABC", "Dacia", "Logan", "break");
	assert(service.getAll().size() == 1);

	service.eraseMasina("BC34ABC");
	assert(service.getAll().size() == 0);

	service.Undo();
	assert(service.getAll().size() == 1);
	service.eraseMasina("BC34ABC");

	service.addMasina("BC34ABC", "Dacia", "Logan", "break");
	service.addMasina("BC34ABD", "Renault", "Logan", "berlina");
	service.addMasina("BC34ABF", "Renault", "Logan", "berlina");

	service.modifyMasina("BC34ABC", "Renault", "Megane", "break");

	auto masinaGasita = service.findMasina("BC34ABC");
	assert(masinaGasita.GetNrInmatriculare() == "BC34ABC");
	assert(masinaGasita.GetProducator() == "Renault");
	assert(masinaGasita.GetModel() == "Megane");
	assert(masinaGasita.GetTip() == "break");

	service.Undo();
	masinaGasita = service.findMasina("BC34ABC");
	assert(masinaGasita.GetNrInmatriculare() == "BC34ABC");
	assert(masinaGasita.GetProducator() == "Dacia");
	assert(masinaGasita.GetModel() == "Logan");
	assert(masinaGasita.GetTip() == "break");
}

void TestStore::runAllTests() const {
	testAddMasina();
	testGetAll();
	testErase();
	testFind();
	testModify();
	testSort();
	testFilter();
	testAddSpalate();
	testSpalate();
	testRaport();
	testUndo();
}
