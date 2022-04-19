#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include "Masina.h"
#include "StringException.h"

using std::vector;
using std::ostream;
using std::ofstream;

class MasiniSpalate
{
private:
	vector<Masina> all;

	/**
	* Functie care verifica daca exista o masina cu numarul de inmatriculare dat
	* 
	* @params: o referinta constanta la un string
	* 
	* @return: -
	* 
	* @exceptii: SpalateException cu textul "Masina deja adaugata!\n" in cazul in care masina este deja in lista
	*/
	void exists(const string& nrInmatriculare);

public:
	/**
	* Functie care goleste lista de masini care trebuie spalate
	* 
	* @params: -
	* 
	* @return: -
	*/
	void clear() noexcept;

	/**
	* Functie care returneaza numarul de masini care trebuie spalate
	* 
	* @params: -
	* 
	* @return: integer
	*/
	size_t size() const noexcept;

	/**
	* Functie care adauga o masina in lista de masini care trebuie spalate
	* 
	* @params: masina - o referinta constanta la o masina
	* 
	* @return: -
	* 
	*/
	void store(const Masina& masina);

	/**
	* Functie care salveaza lista de masini in fisier
	* 
	* @params: fisier - o referinta constanta la un sting
	* 
	* @return: -
	*/
	void exportFisier(const string& fisier);
};

class SpalateException : public StringException {
public:
	SpalateException(const string& message) : StringException(message) {};
};

