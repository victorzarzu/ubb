#include "TestMasiniSpalate.h"

void TestMasiniSpalate::testAddDelete() const {
	MasiniSpalate mSpalate{};
	Masina const masina{ "BC56TRE", "Dacia", "Sprint", "cross-over" };
	
	mSpalate.store(masina);
	assert(mSpalate.size() == 1);

	try {
		mSpalate.store(masina);
		assert(false);
	}
	catch (const SpalateException& ex) {
		std::stringstream out;
		out << ex;
		assert(out.str() == "Masina deja adaugata!\n");
	}

	Masina const masinaNoua{ "SV56TRE", "Renault", "Megane", "berlina" };

	mSpalate.store(masinaNoua);
	assert(mSpalate.size() == 2);

	auto all = mSpalate.getAll();
	assert(all.size() == 2);

	mSpalate.clear();
	assert(mSpalate.size() == 0);

	mSpalate.store(masina);
	assert(mSpalate.size() == 1);

	all = mSpalate.getAll();
	assert(all.size() == 1);
}

void TestMasiniSpalate::testExport() const {
	MasiniSpalate mSpalate{};

	Masina const masina{ "BC56TRE", "Dacia", "Sprint", "cross-over" };
	mSpalate.store(masina);

	Masina const masinaNoua{ "SV56TRE", "Renault", "Megane", "berlina" };
	mSpalate.store(masinaNoua);

	mSpalate.exportFisier("masina.csv");

	std::ifstream in{ "masina.csv" };
	string format;
	int number = 0;

	while (getline(in, format)) {
		if (number == 0) {
			assert(format == "BC56TRE | Dacia | Sprint | cross-over");
		}
		else {
			assert(format == "SV56TRE | Renault | Megane | berlina");
		}
		number++;
	}

	assert(number == 2);
	in.close();
}

void testCosMasina() {
	CosMasini cos{};

	assert(cos.size() == 0);

	Masina const masina{ "BC56TRE", "Dacia", "Sprint", "cross-over" };
	cos.adaugaMasina(masina);

	Masina const masinaNoua{ "SV56TRE", "Renault", "Megane", "berlina" };
	cos.adaugaMasina(masinaNoua);

	assert(cos.size() == 2);

	try {
		cos.adaugaMasina(masinaNoua);
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.toString() == "Masina deja adaugata in cos!\n");
		assert(true);
	}

	Masina const masinaInexistenta{ "SV56TE", "Renault", "Megane", "berlina" };
	try {
		cos.stergeMasina(masinaInexistenta);
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.toString() == "Masina nu exista in cos!\n");
		assert(true);
	}

	cos.stergeMasina(masinaNoua);
	assert(cos.size() == 1);

	cos.adaugaMasina(masinaNoua);
	assert(cos.size() == 2);

	auto all = cos.getAll();
	assert(all.at(0) == masina);
	assert(all.at(1) == masinaNoua);

	cos.clear();
	assert(cos.size() == 0);
}

void TestMasiniSpalate::runAllTests() const {
	testAddDelete();
	testExport();
	testCosMasina();
}
