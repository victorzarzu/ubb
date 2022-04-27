#pragma once
#include "CarRepo.h"
#include <string>
#include <fstream>

class CarRepoFile : public CarRepo {
	std::string filename;

	/**
	* Functie care populeazare repo-ul cu informatii din fisierul cu numele filename
	* 
	* @params: -
	* 
	* @return -
	*/
	void loadFromFile();

	/**
	* Functie care scrie repo-ul in fisierul cu numele filename
	*
	* @params: -
	*
	* @return -
	*/
	void writeToFile();
	
public:
	CarRepoFile(const string& filename) : CarRepo(), filename{ filename }{
		this->loadFromFile();
	};

	/**
	* Functie care adauga o masina in repo
	* 
	* @params: masina - o referinta constanta la o masina
	* 
	* @return: -
	*/
	void store(const Masina& masina) override;

	/**
	* Functie care sterge o masina din repo
	*
	* @params: masina - o referinta constanta la o masina
	*
	* @return: -
*/
	void erase(const Masina& masina) override;

	/**
	* Functie care modifica o atributele unei masini pe baza numarului de inmatriculare
	*
	* @params: masinaModify - o referinta constanta la o masina
	*
	* @return: -
	*/
	void modify(const Masina& masinaModify) override;
};

