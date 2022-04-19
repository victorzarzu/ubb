#pragma once
#include "Masina.h"
#include "CarStore.h"
#include "RaportItem.h"
#include <iostream>

using std::cin;
using std::cout;

class ConsoleUI
{
private:
	CarStore& service;

	void printUIMenu();
	void printUIMenuMasiniSpalate();

	void adaugaUI();
	void stergeUI();
	void modificaUI();
	void afisareUI();
	void cautaUI();
	void filtrareUI();
	void sortareUI();
	void undoUI();

	void runMasiniSpalate();
	void adaugaMasiniSpalateUI();
	void golesteMasiniSpalateUI();
	void populeazaMasiniSpalateUI();
	void exportMasiniSpalateUI();
	
	void raportTipUI();

	void tipareste(const vector<Masina>& masini);
public:
	ConsoleUI() = delete;
	ConsoleUI(CarStore& service) noexcept : service{ service } {};

	void run();
};

