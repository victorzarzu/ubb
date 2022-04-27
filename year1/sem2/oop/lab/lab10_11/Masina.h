#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <sstream>

using std::string;
using std::ostream;
using std::istream;
using std::cout;

class Masina
{
	
private:
	string nrInmatriculare;
	string producator;
	string model;
	string tip;

	
public:
	Masina() = default;
	Masina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip) : nrInmatriculare{ nrInmatriculare }, producator{ producator }, model{ model }, tip{ tip }{};
	Masina(const Masina& ot) : nrInmatriculare{ ot.nrInmatriculare }, producator{ ot.producator }, model{ ot.model }, tip{ ot.tip }{ 
		//cout << "Copy\n";
	};

	~Masina() noexcept {
		nrInmatriculare.clear();
		producator.clear();
		model.clear();
		tip.clear();
	}

	Masina& operator=(const Masina& ot);
	/**
	* Functie care returneaza numarul de inmatricluare al masinii
	* 
	* @params: -
	* 
	* @return string
	*/
	string GetNrInmatriculare() const;

	/**
	* Functie care returneaza producatorul masinii
	*
	* @params: -
	*
	* @return string
	*/
	string GetProducator() const;

	/**
	* Functie care returneaza modelul masinii
	*
	* @params: -
	*
	* @return string
	*/
	string GetModel() const;

	/**
	* Functie care returneaza tipul masinii
	*
	* @params: -
	*
	* @return string
	*/
	string GetTip() const;

	/**
	* Functie care returneaza numarul de inmatriculare al masinii
	*
	* @params: o referinta const la un string
	*
	* @return -
	*/
	void SetNrInmatriculare(const string& nrInmatriculare);

	/**
	* Functie care seteaza producatorul masinii
	*
	* @params: o referinta const la un string
	*
	* @return -
	*/
	void SetProducator(const string& producator);


	/**
	* Functie care seteaza modelul masinii
	*
	* @params: o referinta const la un string
	*
	* @return -
	*/
	void SetModel(const string& model);

	/**
	* Functie care seteaza tipul masinii
	*
	* @params: tip - o referinta const la un string
	*
	* @return -
	*/
	void SetTip(const string& tip);

	/**
	* Functie care verifica daca doua masini sunt egale, pe baza numarului de inmatriculare
	* 
	* @params: ot - o referinta constanta la o masina
	* 
	* @return: true - daca au numerele de inmatriculare la fel, false altfel
	*/
	bool operator==(const Masina& ot) const noexcept;

	/**
	* Functie generica pentru afisarea unei masini
	* 
	* @params: out - o referinta la un string de tip ostream
	*		   masina - o referinta constanta la o masina
	* 
	* @return: o referinta la un string de tip ostream
	*/
	friend ostream& operator<<(ostream& out, const Masina& masina);

	/**
	* Functie generica pentru citirea unei masini
	* 
	* @params: in - o referinta la un string de tip istream
	*		   masina - o referinta la o masina
	*
	* @return: o referinta la un string de tip istream
	*/
	friend istream& operator>>(istream& in, Masina& masina);
};

/**
* Funcie care compara 2 masini pe baza numarului de inmatriculare
* 
* @params: m1 - o referinta de tip const la o masina
*		   m2 - o referinta de tip const la o masina
* 
* @return: true - daca numarul de inmatriculare al primei masini este mai mic lexicografic decat al celei de a doua
*		   false - altfel
*/
bool cmpNrInmatriculare(const Masina& m1, const Masina& m2);

/**
* Funcie care compara 2 masini pe baza tipului
*
* @params: m1 - o referinta de tip const la o masina
*		   m2 - o referinta de tip const la o masina
*
* @return: true - daca tipul primei masini este mai mic lexicografic decat al celei de a doua
*		   false - altfel
*/
bool cmpTip(const Masina& m1, const Masina& m2);

/**
* Funcie care compara 2 masini pe baza producatorului si al modelului
*
* @params: m1 - o referinta de tip const la o masina
*		   m2 - o referinta de tip const la o masina
*
* @return: true - daca sirul obtinut prin concatenarea producatorului si modelului primei masini este mai mic lexicografic decat al celei de a doua
*		   false - altfel
*/
bool cmpProducatorAndModel(const Masina& m1, const Masina& m2);

