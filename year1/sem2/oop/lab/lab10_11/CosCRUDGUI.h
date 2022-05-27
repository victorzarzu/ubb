#pragma once
#include "CosMasini.h"
#include "Masina.h"
#include "Observer.h"
#include "CarStore.h"
#include <qwidget.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qslider.h>
#include <qlayout>
#include <vector>

using std::vector;

class CosCRUDGUI : public QWidget, public Observer {
private:
	CarStore& service;

	QTableWidget* table;
	QSlider* slider;
	QPushButton* genereazaButton;
	QPushButton* golireButton;

	void initComponents();
	void connectSignals();

	void populateTable(QTableWidget* table, const vector<Masina>& all);

public:
	CosCRUDGUI(CarStore& service);

	void update() override;

	~CosCRUDGUI() {
		this->service.getCosMasini().removeObserver(this);
	}
};

