#include "TestMasina.h"

void TestMasina::testGetAndSet() const {
	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
	assert(masina.GetNrInmatriculare() == "BC13BCG");
	assert(masina.GetProducator() == "Dacia");
	assert(masina.GetModel() == "Logan");
	assert(masina.GetTip() == "berlina");

	masina.SetNrInmatriculare("B234REJ");
	masina.SetProducator("Renault");
	masina.SetModel("Megane");
	masina.SetTip("break");
}

void TestMasina::testCopy() const {
	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };
	auto masinaCopy = masina;

	assert(masinaCopy.GetNrInmatriculare() == "BC13BCG");
	assert(masinaCopy.GetProducator() == "Dacia");
	assert(masinaCopy.GetModel() == "Logan");
	assert(masinaCopy.GetTip() == "berlina");

	masinaCopy = masinaCopy;

	assert(masinaCopy.GetNrInmatriculare() == "BC13BCG");
	assert(masinaCopy.GetProducator() == "Dacia");
	assert(masinaCopy.GetModel() == "Logan");
	assert(masinaCopy.GetTip() == "berlina");
}

void TestMasina::testCompare() const {
	Masina masina1{ "BC13BCG", "Dacia", "Logan", "berlina" };
	Masina masina2{ "AG23BCG", "Renault", "Megane", "break" };
	
	Masina masina3{ "AG23BCG", "Renault", "Megane", "break" };
	assert(masina2 == masina3);

	assert(cmpNrInmatriculare(masina1, masina2) == false);
	masina2.SetNrInmatriculare("SV12TYU");
	assert(cmpNrInmatriculare(masina1, masina2) == true);

	assert(cmpTip(masina1, masina2) == true);
	masina1.SetTip("suv");
	assert(cmpTip(masina1, masina2) == false);

	assert(cmpProducatorAndModel(masina1, masina2) == true);
	masina1.SetProducator("Volvo");
	assert(cmpProducatorAndModel(masina1, masina2) == false);
	masina1.SetProducator("Renault");

	assert(cmpProducatorAndModel(masina1, masina2) == true);
	masina1.SetModel("Spring");
	assert(cmpProducatorAndModel(masina1, masina2) == false);
}

void TestMasina::testPrint() const {
	Masina masina{ "BC13BCG", "Dacia", "Logan", "berlina" };

	stringstream os;
	os << masina;
	assert(os.str() == "BC13BCG | Dacia | Logan | berlina\n");
}

void TestMasina::testIO() const {
	Masina masina{};

	ofstream out;
	out.open("testIO.out", ios::out | ios::trunc);
	if (!out.is_open()) {
		return;
	}
	Masina masina1{ "BC13BCG", "Dacia", "Logan", "berlina" };
	out << masina1;
	Masina masina2{ "AG23BCG", "Renault", "Megane", "break" };
	out << masina2;
	out.close();

	ifstream in("testIO.out", ios::in);
	if (!in.is_open()) {
		return;
	}

	Masina m{"", "", "", ""};
	in >> m;
	assert(m.GetNrInmatriculare() == "BC13BCG");
	assert(m.GetProducator() == "Dacia");
	assert(m.GetModel() == "Logan");
	assert(m.GetTip() == "berlina");

	Masina m1{ "", "", "", "" };
	in >> m1;
	assert(m1.GetNrInmatriculare() == "AG23BCG");
	assert(m1.GetProducator() == "Renault");
	assert(m1.GetModel() == "Megane");
	assert(m1.GetTip() == "break");

}

void TestMasina::runAllTests() const {
	testGetAndSet();
	testCopy();
	testCompare();
	testPrint();
	testIO();
}
