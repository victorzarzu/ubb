#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "CarStore.h"
#include "ValidatorMasina.h"
#include "CarRepo.h"
#include "MasiniSpalate.h"
#include "MasiniSpalateGUI.h"
#include "CosReadOnlyGUI.h"
#include "CosCRUDGUI.h"
#include <qkeysequence.h>
#include <qshortcut.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qformlayout.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qexception.h>
#include <qlistwidget.h>
#include <qaction.h>
#include <sstream>
#include <qtablewidget.h>

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(CarStore& service, const ValidatorMasina& validator, QWidget *parent = Q_NULLPTR);

    void run();

private:
    Ui::GUIClass ui;
    CarStore& service;
    const ValidatorMasina& validator;

    QWidget* mainWindow = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout;
    QListWidget* mainList;
    QPushButton* adaugaUIButton;
    QPushButton* stergeUIButton;
    QPushButton* modificaUIButton;
    QPushButton* statsUIButton;
    QPushButton* masiniSpalateUIButton;
    QPushButton* undoButton;
    QPushButton* inchideButton;
    QPushButton* CosReadOnlyButton;
    QPushButton* CosCRUDButton;

    QLabel* nrInmatriculareInfo;
    QLabel* producatorInfo;
    QLabel* modelInfo;
    QLabel* tipInfo;

    QWidget* adaugaWindow = new QWidget;
    QLineEdit* adaugaNrInmatriculareLine;
    QLineEdit* adaugaProducatorLine;
    QLineEdit* adaugaModelLine;
    QLineEdit* adaugaTipLine;
    QPushButton* adaugaButton;

    QWidget* stergeWindow = new QWidget;
    QLineEdit* stergeNrInmatriculareLine;
    QPushButton* stergeButton;

    QWidget* modificaWindow = new QWidget;
    QLineEdit* modificaNrInmatriculareLine;
    QLineEdit* modificaProducatorLine;
    QLineEdit* modificaModelLine;
    QLineEdit* modificaTipLine;
    QPushButton* modificaButton;

    QTableWidget* statsList;
    QWidget* statsWindow = new QWidget;
    QLineEdit* filterLine;
    QAction* filterProducatorAction;
    QAction* filterTipAction;
    QAction* sortNrAction;
    QAction* sortTipAction;
    QAction* sortProducatorAndModelAction;
    QPushButton* afisareButton;
    QLineEdit* cautaLine;
    QPushButton* cautaButton;

    MasiniSpalateGUI* masiniSpalateWindow;

    QLineEdit* adaugaCosLine;
    QLineEdit* stergeCosLine;
    QLineEdit* genereazaCosLine;

    QPushButton* adaugaCosButton;
    QPushButton* stergeCosButton;
    QPushButton* genereazaCosButton;

    void initComponents();
    void connectSignalSlots();

    void initAdaugaComponents();
    void adaugaMasina();

    void initStergeComponents();
    void stergeMasina();

    void initModificaComponents();
    void modificaMasina();

    void initStatsComponents();
    void connectStatsSignalSlots();

    void adaugaUI();
    void modificaUI();
    void stergeUI();
    void statsUI();
    void runMasiniSpalateUI();
    void populateTable(QTableWidget* list, const vector<Masina>& masini);
    void populateList(QListWidget* list, const vector<Masina>& masini);
    void populateListNrInmatriculare(QListWidget* list, const vector<Masina>& masini);
};
