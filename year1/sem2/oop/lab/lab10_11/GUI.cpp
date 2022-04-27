#include "GUI.h"

GUI::GUI(CarStore& service, const ValidatorMasina& validator, QWidget* parent) : service{ service }, validator{ validator }, QMainWindow(parent) {
    ui.setupUi(this);

	QVBoxLayout* vLayout = new QVBoxLayout;

	QHBoxLayout* hLayout1 = new QHBoxLayout;
	QHBoxLayout* hLayout2 = new QHBoxLayout;
	QHBoxLayout* hLayout3 = new QHBoxLayout;

	QWidget* widget1 = new QWidget;
	QPushButton* adauga = new QPushButton("Adauga");
	QObject::connect(adauga, &QPushButton::clicked, [=]() { this->adaugaUI(); });

	QPushButton* sterge = new QPushButton("Sterge");
	QObject::connect(sterge, &QPushButton::clicked, [=]() { this->stergeUI(); });
	hLayout1->addWidget(adauga);
	hLayout1->addWidget(sterge);
	widget1->setLayout(hLayout1);
	vLayout->addWidget(widget1);

	QWidget* widget2 = new QWidget;
	QPushButton* modifica = new QPushButton("Modifica");
	QObject::connect(modifica, &QPushButton::clicked, [this]() { this->modificaUI(); });

	QPushButton* stats = new QPushButton("Stats");
	QObject::connect(stats, &QPushButton::clicked, [this]() { this->statsUI(); });
	hLayout2->addWidget(modifica);
	hLayout2->addWidget(stats);
	widget2->setLayout(hLayout2);
	vLayout->addWidget(widget2);

	QWidget* widget3 = new QWidget;
	QPushButton* masiniSpalate = new QPushButton("Masini spalate");
	QObject::connect(masiniSpalate, &QPushButton::clicked, [this]() {this->runMasiniSpalateUI(); });

	QPushButton* undo = new QPushButton("Undo");
	QObject::connect(undo, &QPushButton::clicked, [&]() {
		try {
			service.Undo();
		}
		catch (const CarStoreException& se) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare undo");
			msgBox.setText(QString::fromUtf8(se.toString()));
			msgBox.exec();
		}
		});

	hLayout3->addWidget(masiniSpalate);
	hLayout3->addWidget(undo);
	widget3->setLayout(hLayout3);
	vLayout->addWidget(widget3);

	QPushButton* inchide = new QPushButton("Inchide");
	QObject::connect(inchide, &QPushButton::clicked, [=]() {this->close(); });
	vLayout->addWidget(inchide);

	QWidget* window = new QWidget;
	window->setLayout(vLayout);

	this->setCentralWidget(window);
}

void GUI::adaugaUI() {
	QWidget* adaugaWindow = new QWidget;

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLabel* nrLabel = new QLabel("Numar inmatriculare: ");
	QLineEdit* nrLine = new QLineEdit;
	formLayout->addRow(nrLabel, nrLine);

	QLabel* producatorLabel = new QLabel("Producator: ");
	QLineEdit* producatorLine = new QLineEdit;
	formLayout->addRow(producatorLabel, producatorLine);

	QLabel* modelLabel = new QLabel("Model: ");
	QLineEdit* modelLine = new QLineEdit;
	formLayout->addRow(modelLabel, modelLine);

	QLabel* tipLabel = new QLabel("Tip: ");
	QLineEdit* tipLine = new QLineEdit;
	formLayout->addRow(tipLabel, tipLine);

	formWidget->setLayout(formLayout);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(formWidget);

	QPushButton* adauga = new QPushButton("&Adauga");
	QObject::connect(adauga, &QPushButton::clicked, [=]() {
		try {
			this->service.addMasina(nrLine->text().toStdString(), producatorLine->text().toStdString(), modelLine->text().toStdString(), tipLine->text().toStdString());
			adaugaWindow->close();
		}
		catch (const ValidateException& ve) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare validare");
			msgBox.setText(QString::fromUtf8(ve.toString()));
			msgBox.exec();
		}
		catch (const CarRepoException& re) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare repo");
			msgBox.setText(QString::fromUtf8(re.toString()));
			msgBox.exec();
		}
		catch (const CarStoreException& se) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare store");
			msgBox.setText(QString::fromUtf8(se.toString()));
			msgBox.exec();
		}
		});
	vLayout->addWidget(adauga);

	adaugaWindow->setLayout(vLayout);
	adaugaWindow->show();
}

void GUI::modificaUI() {
	QWidget* modificaWindow = new QWidget;

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLabel* nrLabel = new QLabel("Numar inmatriculare: ");
	QLineEdit* nrLine = new QLineEdit;
	formLayout->addRow(nrLabel, nrLine);

	QLabel* producatorLabel = new QLabel("Producator: ");
	QLineEdit* producatorLine = new QLineEdit;
	formLayout->addRow(producatorLabel, producatorLine);

	QLabel* modelLabel = new QLabel("Model: ");
	QLineEdit* modelLine = new QLineEdit;
	formLayout->addRow(modelLabel, modelLine);

	QLabel* tipLabel = new QLabel("Tip: ");
	QLineEdit* tipLine = new QLineEdit;
	formLayout->addRow(tipLabel, tipLine);

	formWidget->setLayout(formLayout);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(formWidget);

	QPushButton* adauga = new QPushButton("&Modifica");
	QObject::connect(adauga, &QPushButton::clicked, [=]() {
		try {
			this->service.modifyMasina(nrLine->text().toStdString(), producatorLine->text().toStdString(), modelLine->text().toStdString(), tipLine->text().toStdString());
			modificaWindow->close();
		}
		catch (const ValidateException& ve) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare validare");
			msgBox.setText(QString::fromUtf8(ve.toString()));
			msgBox.exec();
		}
		catch (const CarRepoException& re) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare repo");
			msgBox.setText(QString::fromUtf8(re.toString()));
			msgBox.exec();
		}
		catch (const CarStoreException& se) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare store");
			msgBox.setText(QString::fromUtf8(se.toString()));
			msgBox.exec();
		}
		});
	vLayout->addWidget(adauga);

	modificaWindow->setLayout(vLayout);
	modificaWindow->show();
}

void GUI::stergeUI() {
	QWidget* stergeWindow = new QWidget;

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLabel* nrLabel = new QLabel("Numar inmatriculare: ");
	QLineEdit* nrLine = new QLineEdit;
	formLayout->addRow(nrLabel, nrLine);

	formWidget->setLayout(formLayout);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(formWidget);

	QPushButton* sterge = new QPushButton("&Sterge");
	QObject::connect(sterge, &QPushButton::clicked, [=]() {
		try {
			this->service.eraseMasina(nrLine->text().toStdString());
			stergeWindow->close();
		}
		catch (const CarRepoException& re) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare repo");
			msgBox.setText(QString::fromUtf8(re.toString()));
			msgBox.exec();
		}
		catch (const CarStoreException& se) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare store");
			msgBox.setText(QString::fromUtf8(se.toString()));
			msgBox.exec();
		}
		});
	vLayout->addWidget(sterge);

	stergeWindow->setLayout(vLayout);
	stergeWindow->show();
}

void GUI::statsUI() {
	QWidget* statsWindow = new QWidget;

	//Lista
	QHBoxLayout* topLayout = new QHBoxLayout;
	QListWidget* list = new QListWidget;
	topLayout->addWidget(list);

	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	//Buton filtrare
	QMenu* filterMenu = new QMenu;

	QLineEdit* filterLine = new QLineEdit;

	QAction* filterProducatorA = new QAction("Producator");
	QObject::connect(filterProducatorA, &QAction::triggered, [this, list, filterLine]() {
		const string producator = filterLine->text().toStdString();
		auto masini = this->service.filterByProducator(producator);
		this->populateList(list, masini);
		});
	filterMenu->addAction(filterProducatorA);

	QAction* filterTipA = new QAction("Tip");
	QObject::connect(filterTipA, &QAction::triggered, [this, list, filterLine]() {
		const string tip = filterLine->text().toStdString();
		auto masini = this->service.filterByTip(tip);
		this->populateList(list, masini);
		});
	filterMenu->addAction(filterTipA);

	QPushButton* filterButton = new QPushButton("Filtrare");
	filterButton->setMenu(filterMenu);

	QWidget* filterWidget = new QWidget;
	QFormLayout* filterLayout = new QFormLayout;
	filterLayout->addRow(filterLine, filterButton);
	filterWidget->setLayout(filterLayout);

	buttonsLayout->addWidget(filterWidget);

	//Buton sortare
	QMenu* sortMenu = new QMenu;

	QAction* sortnrA = new QAction("Numar");
	QObject::connect(sortnrA, &QAction::triggered, [this, list]() {
		auto masini = this->service.sortByNtInmatriculare();
		this->populateList(list, masini);
		});
	sortMenu->addAction(sortnrA);

	QAction* sortTipA = new QAction("Tip");
	QObject::connect(sortTipA, &QAction::triggered, [this, list]() {
		auto masini = this->service.sortByTip();
		this->populateList(list, masini);
		});
	sortMenu->addAction(sortTipA);

	QAction* sortProducatorAndModelA = new QAction("Producator si model");
	QObject::connect(sortProducatorAndModelA, &QAction::triggered, [this, list]() {
		auto masini = this->service.sortByProducatorAndModel();
		this->populateList(list, masini);
		});
	sortMenu->addAction(sortProducatorAndModelA);

	QPushButton* sortButton = new QPushButton("Sortare");
	sortButton->setMenu(sortMenu);
	buttonsLayout->addWidget(sortButton);

	//Buton afisare
	QPushButton* showButton = new QPushButton("Afisare");
	QObject::connect(showButton, &QPushButton::clicked, [this, list]() {
			auto masini = this->service.getAll();
			this->populateList(list, masini);
		});
	buttonsLayout->addWidget(showButton);

	QWidget* buttonsWidget = new QWidget;
	buttonsWidget->setLayout(buttonsLayout);

	topLayout->addWidget(buttonsWidget);

	QWidget* topWidget = new QWidget;
	topWidget->setLayout(topLayout);

	QWidget* searchWidget = new QWidget;
	QFormLayout* searchLayout = new QFormLayout;
	QLineEdit* searchLine = new QLineEdit;
	QPushButton* searchButton = new QPushButton("&Cauta");
	QObject::connect(searchButton, &QPushButton::clicked, [this, list, searchLine]() {
		try {
			auto masina = this->service.findMasina(searchLine->text().toStdString());
			this->populateList(list, vector<Masina>(1, masina));
		}
		catch (const CarRepoException& se) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare repo");
			msgBox.setText(QString::fromUtf8(se.toString()));
			msgBox.exec();
		}
		});
	
	searchLayout->addRow(searchLine, searchButton);
	searchWidget->setLayout(searchLayout);

	QVBoxLayout* statsLayout = new QVBoxLayout;
	statsLayout->addWidget(topWidget);
	statsLayout->addWidget(searchWidget);

	statsWindow->setLayout(statsLayout);
	statsWindow->show();
}

void GUI::populateList(QListWidget* list, const vector<Masina>& masini) {
	list->clear();
	
	for (const auto& masina : masini) {
		std::stringstream stream;
		stream << masina;
		new QListWidgetItem(QString::fromUtf8(stream.str().substr(0, stream.str().length() - 1)), list);
	}
}

void GUI::runMasiniSpalateUI() {
	QHBoxLayout* spalateLayout = new QHBoxLayout;
	QListWidget* list = new QListWidget;
	spalateLayout->addWidget(list);

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLineEdit* nrInmatriculareLine = new QLineEdit;
	QPushButton* nrInmatriculareButton = new QPushButton("Adauga");
	QObject::connect(nrInmatriculareButton, &QPushButton::clicked, [this, nrInmatriculareLine, list]() {
		try {
			this->service.adaugaMasinaSpalate(nrInmatriculareLine->text().toStdString());
			nrInmatriculareLine->clear();
			auto masini = this->service.getAllSpalate();
			this->populateList(list, masini);
		}
		catch (const SpalateException& se) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare masini spalate");
			msgBox.setText(QString::fromUtf8(se.toString()));
			msgBox.exec();
		}
		catch (const CarRepoException& ce) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare repo");
			msgBox.setText(QString::fromUtf8(ce.toString()));
			msgBox.exec();
		}
		});
	formLayout->addRow(nrInmatriculareLine, nrInmatriculareButton);

	QLineEdit* nrLine = new QLineEdit;
	QPushButton* nrButton = new QPushButton("Random");
	QObject::connect(nrButton, &QPushButton::clicked, [this, nrLine, list]() {
		try {
			this->service.populeazaMasiniSpalate(nrLine->text().toInt());
			auto masini = this->service.getAllSpalate();
			this->populateList(list, masini);
		}
		catch (const SpalateException& se) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare masini spalate");
			msgBox.setText(QString::fromUtf8(se.toString()));
			msgBox.exec();
		}
		});
	formLayout->addRow(nrLine, nrButton);

	QLineEdit* exportLine = new QLineEdit;
	QPushButton* exportButton = new QPushButton("Export");
	QObject::connect(exportButton, &QPushButton::clicked, [this, exportLine, list]() {
		string fisier = exportLine->text().toStdString();
		if (fisier.length() <= 4 || (fisier.find(".html") == string::npos && fisier.find(".csv") == string::npos)) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Eroare fisier");
			msgBox.setText("Fisierul trebuie sa fie CSV sau HTML");
			msgBox.exec();
		}
		this->service.exportMasiniSpalate(fisier);
		});
	formLayout->addRow(exportLine, exportButton);

	QPushButton* golesteButton = new QPushButton("Goleste");
	QObject::connect(golesteButton, &QPushButton::clicked, [this, list]() {
		this->populateList(list, vector<Masina>());
		});
	formLayout->addRow(golesteButton);

	formWidget->setLayout(formLayout);
	spalateLayout->addWidget(formWidget);
	
	QWidget* spalateWindow = new QWidget;
	spalateWindow->setLayout(spalateLayout);
	spalateWindow->show();
}

void GUI::run() {
	this->show();
}
