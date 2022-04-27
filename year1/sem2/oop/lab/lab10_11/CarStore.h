#pragma once
#include "CarRepo.h"
#include "MasiniSpalate.h"
#include "Masina.h"
#include "ValidatorMasina.h"
#include "RaportItem.h"
#include "ActiuneUndo.h"
#include "Raport.h"
#include <functional>
#include <algorithm>
#include <random>
#include <chrono>
#include <unordered_map>
#include <map>

using std::function;

class CarStore
{
private:
	CarRepo& repo;
	MasiniSpalate lista;
	const ValidatorMasina& validator;
	vector<std::unique_ptr<ActiuneUndo>> undoActions;

public:
	CarStore() = delete;
	CarStore(const CarStore& ot) = delete;
	CarStore(CarRepo& repo, const ValidatorMasina& validator) noexcept : repo{ repo }, validator{ validator }, lista{} {};

	/**
	* Functie care adauga o masina cu proprietatile specificate
	* 
	* @params: nrInmatriculare - o referinta constanta la un string
	*		   producator - o referinta constanta la un string
	*          model - o referinta constanta la un string
	*		   tip - o referinta constanta la un string
	* 
	*@exceptii: ValidateException - daca atributele sunt invalide
	*			CarRepoException - daca exista deja masina
	*/
	void addMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);

	/**
	* Functie care sterge o masina pe baza numarului de inmatriculare
	* 
	* @params: nrInmatriculare - o referinta constanta la un string
	* 
	@exceptii: CarRepoException - daca nu exista masina
	*/
	void eraseMasina(const string& nrInmatriculare);

	/**
	* Functie care modifica atributele unei masini pe baza numarului de inmatriculare
	* 
	* @params: nrInmatriculare - o referinta constanta la un string
	*		   producator - o referinta constanta la un string
	*          model - o referinta constanta la un string
	*		   tip - o referinta constanta la un string
	* 
	*@exceptii: ValidateException - daca atributele sunt invalide
	*			CarRepoException - daca nu exista o masina cu numarul de inmatriculare dat
	*/
	void modifyMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);

	/**
	* Functie care cauta o masina avand numarul de inmatriculare dat
	*
	* @params: nrInmatriculare - o referinta constanta la un string
	*
	* @return: o referinta constanta la masina care are parametrii dati
	*
	* @exceptii: CarRepoException cu textul "Masina inexistenta!\n" daca masina nu exista in repo
	*/
	const Masina& findMasina(const string& nrInmatricular);

	/**
	* Functie care returneaza o lista de masini ordonate in ordine crescatoare in functie de numarul de inmatriculare
	* 
	* @params: -
	* 
	* @return: o lista de masini
	*/
	vector<Masina> sortByNtInmatriculare();

	/**
	* Functie care returneaza o lista de masini ordonate in ordine crescatoare in functie de tip
	*
	* @params: -
	*
	* @return: o lista de masini
	*/
	vector<Masina> sortByTip();

	/**
	* Functie care returneaza o lista de masini ordonate in ordine crescatoare in functie de producator si model
	*
	* @params: -
	*
	* @return: o lista de masini
	*/
	vector<Masina> sortByProducatorAndModel();

	/**
	* Functie pentru filtrarea masinilor in functie de producator
	*
	* @params: producator - un string
	*
	* @return: lista masinilor care au producatorul oferit ca producator
	*/
	vector<Masina> filterByProducator(string producator);

	/**
	* Functie pentru filtrarea masinilor in functie de tip
	*
	* @params: tip - un string
	*
	* @return: lista masinilor care au tipul oferit ca tip
	*/
	vector<Masina> filterByTip(string tip);

	/**
	* Functie care retuneaza o lista imutabila cu toate masinile
	* 
	* @params: -
	* 
	* @return: o lista imutabila de masini
	*/
	const vector<Masina>& getAll() const noexcept;

	/**
	* Functie care returneaza numarul de masini din lista pentru masini spalate
	* 
	* @params:
	* 
	* @return: size_t
	*/
	size_t getListSize() const noexcept;

	/**
	* Functie care adauga o masina in lista de masini spalate
	* 
	* @params: nrInmatriculare - o referinta constanta la string
	* 
	* @return: -
	*/
	void adaugaMasinaSpalate(const string& nrInmatriculare);

	/**
	* Functie care goleste lista de masini care trebuie spalate
	* 
	* @params: -
	* 
	* @return: -
	*/
	void clearMasiniSpalate() noexcept;

	/**
	* Functie care exporta masinile in fisierul dat argument
	*
	* @params: fisier - o referinta constanta la un string
	*
	* @return: -
	*/
	void exportMasiniSpalate(const string& fisier);

	/**
	* Functie care populeaza lista de masini care trebuie spalate aleator in masinile existente
	* 
	* @params: number - integer
	* 
	* @return: -
	* 
	* @exceptii: SpalateException cu textul "Numar de masini prea mare!\n" in daca numarul dorit este mai mare decat numarul actual de masini din repo
	*/
	void populeazaMasiniSpalate(const int& number);

	/**
	* Functie care face undo la ultima operatie efectuata
	* 
	* @params: -
	* 
	* @return: -
	*/
	void Undo();

	/**
	* Functie care returneaza toate masinile care trebuie spalate
	*
	* @params: -
	*
	* @return: un vector de masini
	*/
	const vector<Masina> getAllSpalate() const;

	const RaportItem raportTip(const string& tip);
};

class CarStoreException : public StringException {
public:
	CarStoreException(const string& message) : StringException(message) {};
};

