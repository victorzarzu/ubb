#pragma once
#include "Masina.h"
#include "CarStore.h"
#include "DynamicArray.h"
#include <iostream>

using std::cin;
using std::cout;

class ConsoleUI
{
private:
	CarStore& service;

	void adaugaUI() const;
	void stergeUI() const;
	void modificaUI() const;
	void afisareUI() const;
	void cautaUI() const;
	void filtrareUI() const;
	void sortareUI() const;

	void tipareste(const DynamicArray<Masina>& masini) const;
public:
	ConsoleUI() = delete;
	ConsoleUI(CarStore& service) noexcept : service{ service } {};

	void run() const;
};

