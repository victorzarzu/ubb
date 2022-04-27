#include "TestRepo.h"

void TestRepo::testStore() const {
	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
	CarRepo repo{};
	assert(repo.getLength() == 0);

	repo.store(masina);
	assert(repo.getLength() == 1);

	try {
		Masina const masinaNoua{ "BC13BCG", "Ceva", "Logan", "berlina" };
		repo.store(masinaNoua);
		assert(false);
	}
	catch (const CarRepoException& ex) {
		stringstream out;
		out << ex;
		assert(out.str() == "Masina deja existenta!\n");
	}

	Masina const masinaNoua{ "BC13BC3", "Ceva", "Logan", "berlina" };
	//repo.store(masinaNoua);
	//assert(repo.getLength() == 2);
}

void TestRepo::testErase() const {
	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
	CarRepo repo{};

	repo.store(masina);
	Masina masinaNoua{ "BC13BCB", "Ceva", "Logan", "berlina" };
	repo.store(masinaNoua);

	Masina m{ "BC13BCB", "", "", "" };
	repo.erase(m);
	assert(repo.getLength() == 1);

	try {
		repo.erase(m);
		assert(false);
	}
	catch (const CarRepoException& ex) {
		stringstream out;
		out << ex;
		assert(out.str() == "Masina inexistenta!\n");
	}

	repo.store(masinaNoua);
	assert(repo.getLength() == 2);

	repo.clear();
	assert(repo.getLength() == 0);
}

void TestRepo::testFind() const {
	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
	CarRepo repo{};
	
	repo.store(masina);
	auto masinaGasita = repo.find("BC13BCG");
	assert(masinaGasita.GetNrInmatriculare() == masina.GetNrInmatriculare());
	assert(masinaGasita.GetProducator() == masina.GetProducator());
	assert(masinaGasita.GetModel() == masina.GetModel());
	assert(masinaGasita.GetTip() == masina.GetTip());

	try {
		repo.find("SV13BCG");
		assert(false);
	}
	catch (const CarRepoException& e) {
		stringstream os;
		os << e;
		assert(os.str() == "Masina inexistenta!\n");
		assert(true);
	}
}

void TestRepo::testGetAll() const {
	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
	CarRepo repo{};

	repo.store(masina);

	Masina masinaNoua{ "BC13BCE", "Ceva", "Logan", "berlina" };
	repo.store(masinaNoua);
	assert(repo.getLength() == 2);

	auto list = repo.getAll();
	assert(list.size() == 2);
}

void TestRepo::testPrint() const {
	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
	CarRepo repo{};

	repo.store(masina);

	Masina masinaNoua{ "BC13BCE", "Ceva", "Logan", "berlina" };
	repo.store(masinaNoua);

	stringstream os;
	os << repo;
	assert(os.str() == "BC13BCG | Dacia | Logan | berlina\nBC13BCE | Ceva | Logan | berlina\n");
}

void TestRepo::testModify() const {
	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
	CarRepo repo{};
	
	repo.store(masina);
	Masina masinaModify{ "BC13BCG", "Renault", "Megane", "break" };
	repo.modify(masinaModify);

	auto masinaGasita = repo.find("BC13BCG");
	assert(masinaGasita.GetProducator() == "Renault");
	assert(masinaGasita.GetModel() == "Megane");
	assert(masinaGasita.GetTip() == "break");

	Masina masinaModify1{ "SV25ABC", "Renault", "Megane", "break" };
	try {
		repo.modify(masinaModify1);
		assert(false);
	}
	catch (const CarRepoException& ex) {
		stringstream os;
		os << ex;
		assert(os.str() == "Masina inexistenta!\n");
		assert(true);
	}
}

void TestRepo::testFileLoad() const {
	try {
		CarRepoFile repo{ "inexistent.out" };
		assert(false);
	}
	catch (const CarRepoException& cx) {
		stringstream os;
		os << cx;
		assert(os.str() == "Open error: inexistent.out\n");
		assert(true);
	}

	std::string filename = "testLoad.out";
	CarRepoFile repo{ filename };

	assert(repo.getLength() == 2);
	auto const all = repo.getAll();

	assert(all.at(0).GetNrInmatriculare() == "BC12AAA");
	assert(all.at(0).GetProducator() == "da");
	assert(all.at(0).GetModel() == "da");
	assert(all.at(0).GetTip() == "da");

	assert(all.at(1).GetNrInmatriculare() == "BC22AAA");
	assert(all.at(1).GetProducator() == "nu");
	assert(all.at(1).GetModel() == "da");
	assert(all.at(1).GetTip() == "nu");
}

void TestRepo::testFileStore() const {
	std::string filename = "testIO.out";
	std::ofstream out(filename, std::ios::trunc);
	out.close();

	CarRepoFile repo{ filename };
	assert(repo.getLength() == 0);

	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
	repo.store(masina);
	assert(repo.getLength() == 1);

	Masina masinaNoua{ "BC13BCE", "Ceva", "Logan", "berlina" };
	repo.store(masinaNoua);
	assert(repo.getLength() == 2);

	CarRepoFile repo1{ filename };

	assert(repo.getLength() == 2);
	auto const all = repo.getAll();

	assert(all.at(0).GetNrInmatriculare() == "BC13BCG");
	assert(all.at(0).GetProducator() == "Dacia");
	assert(all.at(0).GetModel() == "Logan");
	assert(all.at(0).GetTip() == "berlina");

	assert(all.at(1).GetNrInmatriculare() == "BC13BCE");
	assert(all.at(1).GetProducator() == "Ceva");
	assert(all.at(1).GetModel() == "Logan");
	assert(all.at(1).GetTip() == "berlina");
}

void TestRepo::testFileErase() const {
		std::string filename = "testio.out";
		std::ofstream out(filename, std::ios::trunc);
		out.close();
	
		CarRepoFile repo{ filename };
	
		Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
		repo.store(masina);
		Masina masinaNoua{ "BC13BCE", "Ceva", "Logan", "berlina" };
		repo.store(masinaNoua);
	
		repo.erase(masina);
		assert(repo.getLength() == 1);
	
		CarRepoFile repo1{ filename };
		
		assert(repo1.getLength() == 1);
		auto const all = repo1.getAll();
	
		assert(all.at(0).GetNrInmatriculare() == "BC13BCE");
		assert(all.at(0).GetProducator() == "Ceva");
		assert(all.at(0).GetModel() == "Logan");
		assert(all.at(0).GetTip() == "berlina");

		std::ifstream in(filename, std::ios::in);
		string line;
		int number = 0;
		while (getline(in, line)) {
			number = number + 1;
		}

		assert(number == 1);
}

void TestRepo::testFileModify() const {
	std::string filename = "testio.out";
	std::ofstream out(filename, std::ios::trunc);
	out.close();

	CarRepoFile repo{ filename };

	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
	repo.store(masina);

	Masina masinaNoua{ "BC13BCE", "Ceva", "Logan", "berlina" };
	repo.store(masinaNoua);

	Masina masinaModify{ "BC13BCG", "Renault", "Megane", "break" };
	repo.modify(masinaModify);
	assert(repo.getLength() == 2);

	CarRepoFile repo1{ filename };

	assert(repo1.getLength() == 2);
	auto const all = repo1.getAll();

	assert(all.at(0).GetNrInmatriculare() == "BC13BCG");
	assert(all.at(0).GetProducator() == "Renault");
	assert(all.at(0).GetModel() == "Megane");
	assert(all.at(0).GetTip() == "break");

	assert(all.at(1).GetNrInmatriculare() == "BC13BCE");
	assert(all.at(1).GetProducator() == "Ceva");
	assert(all.at(1).GetModel() == "Logan");
	assert(all.at(1).GetTip() == "berlina");
}

void TestRepo::runAllTests() const {
	testStore();
	testErase();
	testFind();
	testGetAll();
	testPrint();
	testModify();
	testFileLoad();
	testFileStore();
	testFileErase();
	testFileModify();
}