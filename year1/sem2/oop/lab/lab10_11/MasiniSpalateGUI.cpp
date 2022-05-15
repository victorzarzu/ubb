#include "MasiniSpalateGUI.h"

MasiniSpalateGUI::MasiniSpalateGUI(CarStore& service, QWidget* parent) : service{ service }, QWidget(parent) {

	this->initMasiniSpalateComponents();
	this->connectMasiniSpalateSignalSlots();

	//this->populateListNrInmatriculare(this->mainList, this->service.getAll());
}

void MasiniSpalateGUI::populateList(QListWidget* list, const vector<Masina>& masini) {
	list->clear();

	for (const auto& masina : masini) {
		std::stringstream stream;
		stream << masina;
		new QListWidgetItem(QString::fromUtf8(stream.str().substr(0, stream.str().length() - 1)), list);
	}
}

void MasiniSpalateGUI::initMasiniSpalateComponents() {
	QHBoxLayout* masiniSpalateLayout = new QHBoxLayout;
	masiniSpalateList = new QListWidget;
	masiniSpalateLayout->addWidget(masiniSpalateList);

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	masiniSpalateNrInmatriculareLine = new QLineEdit;
	masiniSpalateNrInmatriculareButton = new QPushButton("Adauga");
	formLayout->addRow(masiniSpalateNrInmatriculareLine, masiniSpalateNrInmatriculareButton);

	masiniSpalateNrLine = new QLineEdit;
	masiniSpalateNrButton = new QPushButton("Random");
	formLayout->addRow(masiniSpalateNrLine, masiniSpalateNrButton);

	masiniSpalateExportLine = new QLineEdit;
	masiniSpalateExportButton = new QPushButton("Export");
	formLayout->addRow(masiniSpalateExportLine, masiniSpalateExportButton);

	masiniSpalateGolesteButton = new QPushButton("Goleste");
	QObject::connect(masiniSpalateGolesteButton, &QPushButton::clicked, [this]() {
		this->populateList(masiniSpalateList, vector<Masina>());
		});
	formLayout->addRow(masiniSpalateGolesteButton);

	formWidget->setLayout(formLayout);
	masiniSpalateLayout->addWidget(formWidget);

	this->setLayout(masiniSpalateLayout);
}

void MasiniSpalateGUI::connectMasiniSpalateSignalSlots() {
	QObject::connect(masiniSpalateNrInmatriculareButton, &QPushButton::clicked, [this]() {
		try {
			this->service.adaugaMasinaSpalate(masiniSpalateNrInmatriculareLine->text().toStdString());
			masiniSpalateNrInmatriculareLine->clear();
			auto masini = this->service.getAllSpalate();
			this->populateList(masiniSpalateList, masini);
		}
		catch (const SpalateException& se) {
			QMessageBox::warning(this, "Spalate Warning", QString::fromStdString(se.toString()));
		}
		catch (const CarRepoException& ce) {
			QMessageBox::warning(this, "Repository Warning", QString::fromStdString(ce.toString()));
		}
		});

	QObject::connect(masiniSpalateNrButton, &QPushButton::clicked, [this]() {
		try {
			this->service.populeazaMasiniSpalate(masiniSpalateNrLine->text().toInt());
			auto masini = this->service.getAllSpalate();
			this->populateList(masiniSpalateList, masini);
			masiniSpalateNrLine->clear();
		}
		catch (const SpalateException& se) {
			QMessageBox::warning(this, "Spalate Warning", QString::fromStdString(se.toString()));
		}
		});

	QObject::connect(masiniSpalateExportButton, &QPushButton::clicked, [this]() {
		string fisier = masiniSpalateExportLine->text().toStdString();
		if (fisier.length() <= 4 || (fisier.find(".html") == string::npos && fisier.find(".csv") == string::npos)) {
			QMessageBox::warning(this, "Fisier Warning", "Fisierul trebuie sa fie CSV sau HTML");
		}
		this->service.exportMasiniSpalate(fisier);
		masiniSpalateExportLine->clear();
		});
}