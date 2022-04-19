#include "Console.h"

void ConsoleUI::printUIMenu() {
	cout << "0 - iesire\n";
	cout << "1 - adauga\n";
	cout << "2 - sterge\n";
	cout << "3 - modifica\n";
	cout << "4 - afisare\n";
	cout << "5 - cauta masina\n";
	cout << "6 - filtrare\n";
	cout << "7 - sortare\n";
	cout << "8 - lista masini spalate\n";
	cout << "9 - undo\n";
}

void ConsoleUI::printUIMenuMasiniSpalate() {
	cout << "0 - iesire\n";
	cout << "1 - goleste lista\n";
	cout << "2 - adauga\n";
	cout << "3 - genereaza lista\n";
	cout << "4 - export\n";
}

void ConsoleUI::tipareste(const vector<Masina>& masini) {
	if (masini.size() == 0) {
		cout << "Nu exista masini!\n";
	}
	else {
		for (auto const& masina : masini) {
			cout << masina;
		}
	}
}

void ConsoleUI::adaugaUI() {
	string nrInmatriculare, producator, model, tip;

	cout << "Numar inmatriculare: ";
	cin >> nrInmatriculare;

	cout << "Producator: ";
	cin >> producator;

	cout << "Model:";
	cin >> model;

	cout << "Tip: ";
	cin >> tip;

	service.addMasina(nrInmatriculare, producator, model, tip);
}

void ConsoleUI::stergeUI() {
	string nrInmatriculare;

	cout << "Numar inmatriculare: ";
	cin >> nrInmatriculare;

	service.eraseMasina(nrInmatriculare);
}

void ConsoleUI::modificaUI() {
	string nrInmatriculare, producatorNou, modelNou, tipNou;

	cout << "Numar inmatriculare: ";
	cin >> nrInmatriculare;

	cout << "Producator nou: ";
	cin >> producatorNou;

	cout << "Model nou: ";
	cin >> modelNou;

	cout << "Tip nou: ";
	cin >> tipNou;

	service.modifyMasina(nrInmatriculare, producatorNou, modelNou, tipNou);
}

void ConsoleUI::afisareUI() {
	tipareste(service.getAll());
}

void ConsoleUI::cautaUI() {
	string nrInmatriculare;

	cout << "Numar inmatriculare: ";
	cin >> nrInmatriculare;

	Masina masina = service.findMasina(nrInmatriculare);

	cout << masina;
}

void ConsoleUI::filtrareUI() {
	string filterString;
	int tip{ 0 };
	cout << "1 - producator\n2 - tip\n";
	cin >> tip;

	if (tip == 1) {
		cout << "Producator: ";
		cin >> filterString;

		tipareste(service.filterByProducator(filterString));
	}
	else if (tip == 2) {
		cout << "Tip: ";
		cin >> filterString;

		tipareste(service.filterByTip(filterString));
	}
	else {
		cout << "Mod invalid!";
	}
}

void ConsoleUI::sortareUI() {
	int tip{ 0 };
	cout << "1 - numar inmatriculare\n2 - tip\n3 - producator + model\n";
	cin >> tip;

	switch (tip)
	{
		case 1:
			tipareste(service.sortByNtInmatriculare());
			break;
		case 2:
			tipareste(service.sortByTip());
		case 3:
			tipareste(service.sortByProducatorAndModel());
		default:
			cout << "Mod invalid!\n";
			break;
	}
}

void ConsoleUI::runMasiniSpalate() {
	while (true) {
		printUIMenuMasiniSpalate();

		int cmd;
		cin >> cmd;

		try {
			switch (cmd) {
			case 0:
				return;
			case 1:
				golesteMasiniSpalateUI();
				break;
			case 2:
				adaugaMasiniSpalateUI();
				break;
			case 3:
				populeazaMasiniSpalateUI();
				break;
			case 4:
				exportMasiniSpalateUI();
				break;
			default:
				cout << "Comanda invalida!\n";
			}
		}
		catch (const SpalateException& se) {
			cout << se << '\n';
		}
		catch (const CarRepoException& re) {
			cout << re << '\n';
		}
	}
}

void ConsoleUI::adaugaMasiniSpalateUI() {
	string nrInmatriculare;
	cout << "Numar inmatriculare: ";
	cin >> nrInmatriculare;

	service.adaugaMasinaSpalate(nrInmatriculare);

	cout << "Numar masini in lista: " << service.getListSize() << '\n';
}

void ConsoleUI::golesteMasiniSpalateUI() {
	service.clearMasiniSpalate();
	cout << "Numar masini in lista: " << service.getListSize() << '\n';
}
void ConsoleUI::populeazaMasiniSpalateUI() {
	int number;
	cout << "Numar masini: ";
	cin >> number;

	service.populeazaMasiniSpalate(number);
	cout << "Numar masini in lista: " << service.getListSize() << '\n';
}

void ConsoleUI::exportMasiniSpalateUI() {
	string fisier;
	cout << "Fisier export: ";
	cin >> fisier;
	if (fisier.length() <= 4 || (fisier.find(".html") == string::npos && fisier.find(".csv") == string::npos)) {
		cout << "Nume fisier invalid!\n";
		return;
	}

	service.exportMasiniSpalate(fisier);
	cout << "Numar masini in lista: " << service.getListSize() << '\n';
}

void ConsoleUI::raportTipUI() {
	string tip;
	cout << "Tip: ";
	cin >> tip;

	auto raport = service.raportTip(tip);

	cout << "Exista " << raport.GetCount() << " masini de tipul " << raport.GetTip() << '\n';
}

void ConsoleUI::undoUI() {
	service.Undo();
}

void ConsoleUI::run() {
	while (true) {
		printUIMenu();

		int cmd;
		cin >> cmd;

		try {
			switch (cmd) {
			case 1:
				adaugaUI();
				break;
			case 2:
				stergeUI();
				break;
			case 3:
				modificaUI();
				break;
			case 4:
				afisareUI();
				break;
			case 5:
				cautaUI();
				break;
			case 6:
				filtrareUI();
				break;
			case 7:
				sortareUI();
				break;
			case 8:
				runMasiniSpalate();
				break;
			case 9:
				undoUI();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida!\n";
			}
		}
		catch (const CarRepoException& re) {
			cout << re << '\n';
		}
		catch (const ValidateException& ve) {
			cout << ve << '\n';
		}
		catch (const CarStoreException& ce) {
			cout << ce << '\n';
		}
	}
}
