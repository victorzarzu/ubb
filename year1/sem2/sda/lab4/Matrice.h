#pragma once
#include <tuple>

typedef int TElem;


#define NULL_TELEMENT 0

#define INITIAL_CAPACITY 100000
#define RC 2
#define RM 2

using std::tuple;

typedef tuple<int, int, TElem> Celula;

class Matrice {

private:
	int nrL;
	int nrC;

	int cp;
	int prim, primLiber;
	Celula* e;
	int* urm;

	//functie care aloca un spatiu liber in lista
	//returneaza un indice spre elementul eliberat din lista inlantuita a spatiului liber
	int aloca();

	//functie care elibereaza spatiul de la indicele indicat de pozitie
	void dealoca(int pozitie);

	//functie care initializeaza lista spatiului liber spatiul liber
	void initSpatiuLiber();

	//functie care redimensioneaza lista si reinitializeaza lista inlantuita a spatiului liber
	void redimSiReinitializare();

	//functie care creeaza un nod cu informatia utila oferita si returneaza pozitia acestuia in lista
	int creeazaNod(Celula e);

	//verifica daca doua elemente din lista se afla in relatie, returneaza true daca c1relc2 si false altfel
	bool rel(Celula c1, Celula c2) const;

	//verifica daca doua celule sunt pe aceeasi pozitie
	bool eq(Celula c1, Celula c2) const;

	//functie care adauga un element in matrice
	TElem adauga(int i, int j, TElem e);

	//functie care sterge un element in matrice
	TElem sterge(int i, int j);

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice(){};

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;

	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem);

};







