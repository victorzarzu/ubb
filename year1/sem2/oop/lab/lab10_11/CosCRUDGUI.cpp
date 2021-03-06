#include "CosCRUDGUI.h"

CosCRUDGUI::CosCRUDGUI( CarStore& service) : service{ service } {
	this->service.getCosMasini().addObserver(this);

	this->initComponents();
	this->connectSignals();
	this->update();
}

void CosCRUDGUI::initComponents() {
	QVBoxLayout* mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);

	table = new QTableWidget(0, 4);
	table->setSelectionMode(QAbstractItemView::SingleSelection);
	mainLayout->addWidget(table);

	slider = new QSlider;
	slider->setMinimum(0);
	slider->setMaximum(this->service.getStoreSize());
	slider->setOrientation(Qt::Horizontal);
	slider->setTickPosition(QSlider::TicksBelow);
	mainLayout->addWidget(slider);

	genereazaButton = new QPushButton("Genereaza");
	mainLayout->addWidget(genereazaButton);

	golireButton = new QPushButton("Golire");
	mainLayout->addWidget(golireButton);
}

void CosCRUDGUI::connectSignals() {
	QObject::connect(genereazaButton, &QPushButton::clicked, [this]() {
		int number = slider->value();
		this->service.genereazaCos(number);
		this->service.getCosMasini().notify();
		});
	QObject::connect(golireButton, &QPushButton::clicked, [this]() {
		this->service.getCosMasini().clear();
		this->service.getCosMasini().notify();
		});
}

void CosCRUDGUI::populateTable(QTableWidget* table, const vector<Masina>& all) {
	table->clear();
	table->setRowCount(0);
	int nr = 0;

	for (const auto& masina : all) {
		++nr;
		table->insertRow(nr - 1);
		table->setItem(nr - 1, 0, new QTableWidgetItem(QString::fromStdString(masina.GetNrInmatriculare())));
		table->setItem(nr - 1, 1, new QTableWidgetItem(QString::fromStdString(masina.GetProducator())));
		table->setItem(nr - 1, 2, new QTableWidgetItem(QString::fromStdString(masina.GetModel())));
		table->setItem(nr - 1, 3, new QTableWidgetItem(QString::fromStdString(masina.GetTip())));
	}
}

void CosCRUDGUI::update() {
	this->populateTable(table, this->service.getCosMasini().getAll());
}