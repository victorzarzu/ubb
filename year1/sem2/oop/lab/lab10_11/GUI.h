#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "CarStore.h"
#include "ValidatorMasina.h"
#include "CarRepo.h"
#include "MasiniSpalate.h"
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

    void adaugaUI();
    void modificaUI();
    void stergeUI();
    void statsUI();
    void runMasiniSpalateUI();
    void populateList(QListWidget* list, const vector<Masina>& masini);
};
