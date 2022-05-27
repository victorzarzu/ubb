#include "GUI.h"

GUI::GUI(CarStore& service, const ValidatorMasina& validator, QWidget* parent) : service{ service }, validator{ validator }, QMainWindow(parent) {
    ui.setupUi(this);

	this->masiniSpalateWindow = new MasiniSpalateGUI(this->service);

	this->initComponents();
	this->connectSignalSlots();

	this->initAdaugaComponents();
	this->initStergeComponents();
	this->initModificaComponents();
	
	this->initStatsComponents();
	this->connectStatsSignalSlots();

	//this->populateListNrInmatriculare(this->mainList, this->service.getAll());
}

void GUI::initComponents() {
	mainLayout = new QHBoxLayout;
	QVBoxLayout* buttonsLayout = new QVBoxLayout;
	QWidget* buttonsWidget = new QWidget;
	//mainList = new QListWidget;
	//mainList->setSelectionMode(QListWidget::SingleSelection);

	adaugaUIButton = new QPushButton("Adauga");
	stergeUIButton = new QPushButton("Sterge");
	buttonsLayout->addWidget(adaugaUIButton);
	buttonsLayout->addWidget(stergeUIButton);

	modificaUIButton = new QPushButton("Modifica");
	statsUIButton = new QPushButton("Stats");
	buttonsLayout->addWidget(modificaUIButton);
	buttonsLayout->addWidget(statsUIButton);

	masiniSpalateUIButton = new QPushButton("Masini spalate");
	undoButton = new QPushButton("Undo");
	buttonsLayout->addWidget(masiniSpalateUIButton);
	buttonsLayout->addWidget(undoButton);

	CosReadOnlyButton = new QPushButton("Cos Read Only");
	CosCRUDButton = new QPushButton("Cos CRUD");
	buttonsLayout->addWidget(CosReadOnlyButton);
	buttonsLayout->addWidget(CosCRUDButton);
	
	inchideButton = new QPushButton("Inchide");
	buttonsLayout->addWidget(inchideButton);

	buttonsWidget->setLayout(buttonsLayout);
	mainLayout->addWidget(buttonsWidget);

	QVBoxLayout* rightLayout = new QVBoxLayout;
	QWidget* rightWidget = new QWidget;
	
	mainListModel = new MainListModel{ this->service.getAll() };
	mainListView->setModel(mainListModel);
	mainListView->setUniformItemSizes(true);

	rightLayout->addWidget(mainListView);

	rightWidget->setLayout(rightLayout);
	mainLayout->addWidget(rightWidget);

	QFormLayout* cosLayout = new QFormLayout;
	QWidget* cosWidget= new QWidget;
	cosWidget->setLayout(cosLayout);

	adaugaCosLine = new QLineEdit;
	adaugaCosButton = new QPushButton("Adauga in cos");
	cosLayout->addRow(adaugaCosLine, adaugaCosButton);

	stergeCosLine = new QLineEdit;
	stergeCosButton = new QPushButton("Sterge din cos");
	cosLayout->addRow(stergeCosLine, stergeCosButton);

	genereazaCosLine = new QLineEdit;
	genereazaCosButton = new QPushButton("Generaza cos");
	cosLayout->addRow(genereazaCosLine, genereazaCosButton);

	rightLayout->addWidget(cosWidget);

	this->mainWindow->setLayout(mainLayout);
	this->setCentralWidget(this->mainWindow);
	
	this->mainWindow->setLayout(mainLayout);
	this->setCentralWidget(this->mainWindow);
}

void GUI::connectSignalSlots() {
	QObject::connect(adaugaUIButton, &QPushButton::clicked, this, &GUI::adaugaUI);
	QObject::connect(stergeUIButton, &QPushButton::clicked, this, &GUI::stergeUI);
	QObject::connect(modificaUIButton, &QPushButton::clicked, this, &GUI::modificaUI);
	QObject::connect(statsUIButton, &QPushButton::clicked, this, &GUI::statsUI);
	QObject::connect(masiniSpalateUIButton, &QPushButton::clicked, this, &GUI::runMasiniSpalateUI);

	QObject::connect(undoButton, &QPushButton::clicked, [&]() {
		try {
			service.Undo();
			mainListModel->setMasini(service.getAll());
			//this->populateListNrInmatriculare(this->mainList, this->service.getAll());
		}
		catch (const CarStoreException& se) {
			QMessageBox::warning(this, "Undo Warning", QString::fromStdString(se.toString()));
		}
		});
	QObject::connect(inchideButton, &QPushButton::clicked, this, &GUI::close);
	QObject::connect(CosReadOnlyButton, &QPushButton::clicked, [this]() {
		auto cosReadOnly = new CosReadOnlyGUI(this->service.getCosMasini());
		cosReadOnly->show();
		});
	QObject::connect(CosCRUDButton, &QPushButton::clicked, [this]() {
		auto cosCRUD = new CosCRUDGUI(this->service);
		cosCRUD->show();
		});

	QObject::connect(adaugaCosButton, &QPushButton::clicked, [this]() {
		try {
			this->service.adaugaCos(adaugaCosLine->text().toStdString());
			adaugaCosLine->clear();
		}
		catch (const CarRepoException& se) {
			QMessageBox::warning(this, "Repo Warning", QString::fromStdString(se.toString()));
		}
		catch (const CosException& ce) {
			QMessageBox::warning(this, "Cos Warning", QString::fromStdString(ce.toString()));
		}
		});

	QObject::connect(stergeCosButton, &QPushButton::clicked, [this]() {
		try {
			this->service.stergeCos(stergeCosLine->text().toStdString());
			stergeCosLine->clear();
		}
		catch (const CarRepoException& se) {
			QMessageBox::warning(this, "Repo Warning", QString::fromStdString(se.toString()));
		}
		catch (const CosException& ce) {
			QMessageBox::warning(this, "Cos Warning", QString::fromStdString(ce.toString()));
		}
		});

	QObject::connect(genereazaCosButton, &QPushButton::clicked, [this]() {
		try {
			bool ok = true;
			int number = genereazaCosLine->text().toInt(&ok);
			if (!ok) {
				QMessageBox::warning(this, "Valoare Warning", "Valoare invalida!");
				return;
			}

			this->service.genereazaCos(number);
			genereazaCosLine->clear();
		}
		catch (const CarStoreException& se) {
			QMessageBox::warning(this, "Repo Warning", QString::fromStdString(se.toString()));
		}
		});

	QShortcut* shortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
	QObject::connect(shortcut, &QShortcut::activated, this->adaugaCosButton, &QPushButton::click);
}

void GUI::initAdaugaComponents() {
	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLabel* nrLabel = new QLabel("Numar inmatriculare: ");
	adaugaNrInmatriculareLine = new QLineEdit;
	formLayout->addRow(nrLabel, adaugaNrInmatriculareLine);

	QLabel* producatorLabel = new QLabel("Producator: ");
	adaugaProducatorLine = new QLineEdit;
	formLayout->addRow(producatorLabel, adaugaProducatorLine);

	QLabel* modelLabel = new QLabel("Model: ");
	adaugaModelLine = new QLineEdit;
	formLayout->addRow(modelLabel, adaugaModelLine);

	QLabel* tipLabel = new QLabel("Tip: ");
	adaugaTipLine = new QLineEdit;
	formLayout->addRow(tipLabel, adaugaTipLine);

	formWidget->setLayout(formLayout);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(formWidget);

	adaugaButton = new QPushButton("&Adauga");
	QObject::connect(adaugaButton, &QPushButton::clicked, this, &GUI::adaugaMasina);

	vLayout->addWidget(adaugaButton);

	adaugaWindow->setLayout(vLayout);
}

void GUI::adaugaMasina() {
	try {
		this->service.addMasina(adaugaNrInmatriculareLine->text().toStdString(), adaugaProducatorLine->text().toStdString(), adaugaModelLine->text().toStdString(), adaugaTipLine->text().toStdString());
		adaugaNrInmatriculareLine->clear();
		adaugaProducatorLine->clear();
		adaugaModelLine->clear();
		adaugaTipLine->clear();
		adaugaWindow->close();
		reloadList(service.getAll());		
		//this->populateListNrInmatriculare(this->mainList, this->service.getAll());
	}
	catch (const ValidateException& ve) {
		QMessageBox::warning(this, "Validation Warning", QString::fromStdString(ve.toString()));
	}
	catch (const CarRepoException& re) {
		QMessageBox::warning(this, "Repository Warning", QString::fromStdString(re.toString()));
	}
	catch (const CarStoreException& se) {
		QMessageBox::warning(this, "Service Warning", QString::fromStdString(se.toString()));
	}
}

void GUI::adaugaUI() {
	adaugaWindow->show();
}

void GUI::initStergeComponents() {

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLabel* nrLabel = new QLabel("Numar inmatriculare: ");
	stergeNrInmatriculareLine = new QLineEdit;
	formLayout->addRow(nrLabel, stergeNrInmatriculareLine);

	formWidget->setLayout(formLayout);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(formWidget);

	stergeButton = new QPushButton("&Sterge");
	QObject::connect(stergeButton, &QPushButton::clicked, this, &GUI::stergeMasina);

	vLayout->addWidget(stergeButton);

	stergeWindow->setLayout(vLayout);
}

void GUI::stergeMasina() {
	try {
		this->service.eraseMasina(stergeNrInmatriculareLine->text().toStdString());
		stergeNrInmatriculareLine->clear();
		stergeWindow->close();
		reloadList(service.getAll());
		//this->populateListNrInmatriculare(this->mainList, this->service.getAll());
	}
	catch (const CarRepoException& re) {
		QMessageBox::warning(this, "Repository Warining", QString::fromStdString(re.toString()));
	}
}

void GUI::stergeUI() {
	stergeWindow->show();
}

void GUI::initModificaComponents() {

	QWidget* formWidget = new QWidget;
	QFormLayout* formLayout = new QFormLayout;

	QLabel* nrLabel = new QLabel("Numar inmatriculare: ");
	modificaNrInmatriculareLine = new QLineEdit;
	formLayout->addRow(nrLabel, modificaNrInmatriculareLine);

	QLabel* producatorLabel = new QLabel("Producator: ");
	modificaProducatorLine = new QLineEdit;
	formLayout->addRow(producatorLabel, modificaProducatorLine);

	QLabel* modelLabel = new QLabel("Model: ");
	modificaModelLine = new QLineEdit;
	formLayout->addRow(modelLabel, modificaModelLine);

	QLabel* tipLabel = new QLabel("Tip: ");
	modificaTipLine = new QLineEdit;
	formLayout->addRow(tipLabel, modificaTipLine);

	formWidget->setLayout(formLayout);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(formWidget);

	QPushButton* adauga = new QPushButton("&Modifica");
	QObject::connect(adauga, &QPushButton::clicked, this, &GUI::modificaMasina);
	vLayout->addWidget(adauga);

	modificaWindow->setLayout(vLayout);
}

void GUI::modificaMasina() {
	try {
		this->service.modifyMasina(modificaNrInmatriculareLine->text().toStdString(), modificaProducatorLine->text().toStdString(), modificaModelLine->text().toStdString(), modificaTipLine->text().toStdString());
		modificaNrInmatriculareLine->clear();
		modificaProducatorLine->clear();
		modificaModelLine->clear();
		modificaTipLine->clear();
		modificaWindow->close();
		mainListModel->setMasini(service.getAll());
		//this->populateListNrInmatriculare(this->mainList, this->service.getAll());
	}
	catch (const ValidateException& ve) {
		QMessageBox::warning(this, "Validation Warining", QString::fromStdString(ve.toString()));
	}
	catch (const CarRepoException& re) {
		QMessageBox::warning(this, "Repository Warining", QString::fromStdString(re.toString()));
	}
	catch (const CarStoreException& se) {
		QMessageBox::warning(this, "Service Warining", QString::fromStdString(se.toString()));
	}
}

void GUI::modificaUI() {
	modificaWindow->show();
}

void GUI::initStatsComponents() {
	//Lista
	QHBoxLayout* topLayout = new QHBoxLayout;
	statsList = new QTableWidget(1, 4);
	statsList->setItem(0, 0, new QTableWidgetItem("Numar inmatriculare"));
	statsList->setItem(0, 1, new QTableWidgetItem("Producator"));
	statsList->setItem(0, 2, new QTableWidgetItem("Model"));
	statsList->setItem(0, 3, new QTableWidgetItem("Tip"));

	topLayout->addWidget(statsList);

	QVBoxLayout* buttonsLayout = new QVBoxLayout;

	//Buton filtrare
	QMenu* filterMenu = new QMenu;
	filterLine = new QLineEdit;

	filterProducatorAction = new QAction("Producator");
	filterMenu->addAction(filterProducatorAction);

	filterTipAction = new QAction("Tip");
	filterMenu->addAction(filterTipAction);

	QPushButton* filterButton = new QPushButton("Filtrare");
	filterButton->setMenu(filterMenu);

	QWidget* filterWidget = new QWidget;
	QFormLayout* filterLayout = new QFormLayout;
	filterLayout->addRow(filterLine, filterButton);
	filterWidget->setLayout(filterLayout);

	buttonsLayout->addWidget(filterWidget);

	//Buton sortare
	QMenu* sortMenu = new QMenu;

	sortNrAction = new QAction("Numar");
	sortMenu->addAction(sortNrAction);

	sortTipAction = new QAction("Tip");
	sortMenu->addAction(sortTipAction);

	sortProducatorAndModelAction = new QAction("Producator si model");
	sortMenu->addAction(sortProducatorAndModelAction);

	QPushButton* sortButton = new QPushButton("Sortare");
	sortButton->setMenu(sortMenu);
	buttonsLayout->addWidget(sortButton);

	//Buton afisare
	afisareButton = new QPushButton("Afisare");
	buttonsLayout->addWidget(afisareButton);

	QWidget* buttonsWidget = new QWidget;
	buttonsWidget->setLayout(buttonsLayout);

	topLayout->addWidget(buttonsWidget);

	QWidget* topWidget = new QWidget;
	topWidget->setLayout(topLayout);

	QWidget* searchWidget = new QWidget;
	QFormLayout* searchLayout = new QFormLayout;
	cautaLine = new QLineEdit;
	cautaButton = new QPushButton("&Cauta");


	searchLayout->addRow(cautaLine, cautaButton);
	searchWidget->setLayout(searchLayout);

	QVBoxLayout* statsLayout = new QVBoxLayout;
	statsLayout->addWidget(topWidget);
	statsLayout->addWidget(searchWidget);

	statsWindow->setLayout(statsLayout);
}

void GUI::connectStatsSignalSlots() {
	QObject::connect(filterProducatorAction, &QAction::triggered, [this]() {
		auto masini = this->service.filterByProducator(this->filterLine->text().toStdString());
		this->filterLine->clear();
		this->populateTable(this->statsList, masini);
		});
	QObject::connect(filterTipAction, &QAction::triggered, [this]() {
		auto masini = this->service.filterByTip(this->filterLine->text().toStdString());
		this->filterLine->clear();
		this->populateTable(this->statsList, masini);
		});

	QObject::connect(sortNrAction, &QAction::triggered, [this]() {
		auto masini = this->service.sortByNtInmatriculare();
		this->populateTable(this->statsList, masini);
		});
	QObject::connect(sortTipAction, &QAction::triggered, [this]() {
		auto masini = this->service.sortByTip();
		this->populateTable(this->statsList, masini);
		});
	QObject::connect(sortProducatorAndModelAction, &QAction::triggered, [this]() {
		auto masini = this->service.sortByProducatorAndModel();
		this->populateTable(this->statsList, masini);
		});

	QObject::connect(afisareButton, &QPushButton::clicked, [this]() {
		auto masini = this->service.getAll();
		this->populateTable(this->statsList, masini);
		});

	QObject::connect(cautaButton, &QPushButton::clicked, [this]() {
		try {
			auto masina = this->service.findMasina(this->cautaLine->text().toStdString());
			this->populateTable(this->statsList, vector<Masina>(1, masina));
		}
		catch (const CarRepoException& se) {
			QMessageBox::warning(this, "Repository Warning", QString::fromStdString(se.toString()));
		}
		});
}

void GUI::statsUI() {
	statsWindow->show();
}

void GUI::populateListNrInmatriculare(QListWidget* list, const vector<Masina>& masini) {
	list->clear();

	for (const auto& masina : masini) {
		new QListWidgetItem(QString::fromStdString(masina.GetNrInmatriculare()), list);
	}
}

void GUI::populateTable(QTableWidget* table, const vector<Masina>& masini) {
	table->setRowCount(1);

	for (const auto& masina : masini) {
		std::stringstream stream;
		stream << masina;
		int const rows = table->rowCount();
		table->insertRow(rows);
		statsList->setItem(rows, 0, new QTableWidgetItem(QString::fromStdString(masina.GetNrInmatriculare())));
		statsList->setItem(rows, 1, new QTableWidgetItem(QString::fromStdString(masina.GetProducator())));
		statsList->setItem(rows, 2, new QTableWidgetItem(QString::fromStdString(masina.GetModel())));
		statsList->setItem(rows, 3, new QTableWidgetItem(QString::fromStdString(masina.GetTip())));
	}
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
	masiniSpalateWindow->show();
}

void GUI::run() {
	this->show();
}

void GUI::reloadList(const vector<Masina>& masini) {
	this->mainListModel->setMasini(masini);
}
