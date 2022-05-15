#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <vector>
#include <qpushbutton.h>
#include <qaction.h>
#include <qlayout.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include "Masina.h"
#include "CarStore.h"

using std::vector;

class MasiniSpalateGUI : public QWidget
{
private:
    CarStore& service;

	void populateList(QListWidget* list, const vector<Masina>& masini);
	void initMasiniSpalateComponents();
	void connectMasiniSpalateSignalSlots();

    QListWidget* masiniSpalateList;
    QLineEdit* masiniSpalateNrInmatriculareLine;
    QPushButton* masiniSpalateNrInmatriculareButton;
    QLineEdit* masiniSpalateNrLine;
    QPushButton* masiniSpalateNrButton;
    QLineEdit* masiniSpalateExportLine;
    QPushButton* masiniSpalateExportButton;
    QPushButton* masiniSpalateGolesteButton;

public:
    MasiniSpalateGUI(CarStore& service, QWidget* parent = Q_NULLPTR);
};

