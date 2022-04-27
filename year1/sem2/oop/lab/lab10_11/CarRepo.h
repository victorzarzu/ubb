#pragma once
#include "Masina.h"
#include "StringException.h"
#include <vector>
#include <ostream>

using std::vector;
using std::ostream;

class CarRepo
{
private:
	vector<Masina> storage;

	/**
	* Functie care verifica daca masina se afla deja in repo
	* 
	* @params: masina - o referinta constanta la o masina
	* 
	* @return: true - daca masina este in repo
	*		   false - altfel
	*/
	bool exista(const Masina& masina) const;
public:
	CarRepo() = default;
	CarRepo(const CarRepo& ot) = delete;

	/**
	* Functie care adauga o masina in repo
	* 
	* @params: masina - o referinta constanta la o adresa
	* 
	* @return: -
	* 
	* @exceptii: CarRepoException cu textul "Masina deja existenta!\n" daca masina deja exista in repo
	*/
	virtual void store(const Masina& masina);

	/**
	* Functie care sterge o masina din repo pe baza numarului de inmatriculare
	*
	* @params: masina - o referinta constanta la o masina
	*
	* @return: -
	*
	* @exceptii: CarRepoException cu textul "Masina inexistenta!\n" daca masina nu exista in repo
	*/
	virtual void erase(const Masina& masina);

	/**
	* Functie care cauta o masina avand numarul de inmatriculare dat
	* 
	* @params: nrInmatriculare - o referinta constanta la un string
	* 
	* @return: o referinta constanta la masina care are parametrii dati
	* 
	* @exceptii: CarRepoException cu textul "Masina inexistenta!\n" daca masina nu exista in repo
	*/
	const Masina& find(const string& nrInmatriculare) const;

	/**
	* Functie care modifica o atributele unei masini pe baza numarului de inmatriculare
	* 
	* @params: masinaModify - o referinta constanta la o masina
	* 
	* @return: -
	*/
	virtual void modify(const Masina& masinaModify);

	/**
	* Functie care returneaza o lista imutabila cu masini
	* 
	* @params: -
	* 
	* @return: o lista cu referinte constante spre masini
	*/
	const vector<Masina>& getAll() const noexcept;

	/**
	* Functie care returneaza numarul de obiecte din repo
	* 
	* @params: -
	* 
	* @return: intreg
	*/
	const unsigned int getLength() const noexcept;

	/**
	* Functie care goleste repo-ul
	* 
	* @params: -
	* 
	* @return: -
	*/
	void clear() noexcept;

	/**
	* Functie generica pentru afisarea unui repo
	*
	* @params: out - o referinta la un string de tip ostream
	*		   ex - o referinta un repo de produse
	*
	* @return: o referinta la un string de tip ostream
	*/
	friend ostream& operator<<(ostream& out, const CarRepo& repo);
};

class CarRepoException : public StringException {
public:
	CarRepoException(const string& message) : StringException(message) {};
};

