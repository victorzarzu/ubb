#pragma once
#include "Observer.h"
#include "Masina.h"
#include "StringException.h"
#include <vector>

using std::vector;

class CosMasini : public Observable {
private:
	vector<Masina> cosMasini;
	
	/**
	* Functie care verifica daca exista deja masina in cos
	*
	* @params: o referinta constanta la o masina
	*
	* @return: -
	*
	* @exceptii: SpalateException cu textul "Masina deja adaugata!\n" in cazul in care masina este deja in lista
	*/
	void exists(const Masina& masina);

public:
	/**
	* Functie care goleste cosul
	*
	* @params: -
	*
	* @return: -
	*/
	void clear() noexcept;

	/**
	* Functie care returneaza numarul de masini din cos
	*
	* @params: -
	*
	* @return: integer
	*/
	size_t size() const noexcept;

	/**
	* Functie care adauga o masina in cos
	*
	* @params: masina - o referinta constanta la o masina
	*
	* @return: -
	*
	*/
	void adaugaMasina(const Masina& masina);

	/*
	* Functie care sterge o masina
	* 
	* @params: masina - o masina
	* 
	* @return: -
	*/
	void stergeMasina(const Masina& masina);

	/**
	* Functie care returneaza toate masinile care trebuie spalate
	*
	* @params: -
	*
	* @return: un vector de masini
	*/
	const vector<Masina> getAll() const;
};

class CosException : public StringException {
public:
	CosException(const string& message) : StringException(message) {};
};

