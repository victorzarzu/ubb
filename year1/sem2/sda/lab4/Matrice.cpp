#include "Matrice.h"

#include <exception>
#include <iostream>

using namespace std;

/**
* Caz favorabil = Caz defavorabil = Caz Mediu
* Complexitate: theta(1)
*/
int Matrice::aloca() {
	int pozitie = this->primLiber;
	this->primLiber = this->urm[this->primLiber];

	return pozitie;
}

/**
* Caz favorabil = Caz defavorabil = Caz Mediu
* Complexitate: theta(1)
*/
void Matrice::dealoca(int pozitie) {
	this->urm[pozitie] = this->primLiber;
	this->primLiber = pozitie;
}

/**
* Caz favorabil = Caz defavorabil = Caz Mediu
* Complexitate: theta(cp)
*/
void Matrice::initSpatiuLiber() {
	for (int i = 0; i < cp - 1; ++i) {
		this->urm[i] = i + 1;
	}
	this->urm[cp - 1] = -1;
	this->primLiber = 0;
}

/**
* Caz favorabil = Caz defavorabil = Caz Mediu
* Complexitate: theta(cp * (RC - 1))
*/
void Matrice::redimSiReinitializare() {
	int* newUrm = new int[this->cp * RC];
	Celula* newE = new Celula[this->cp * RC];

	for (int i = 0; i < this->cp; ++i) {
		newUrm[i] = this->urm[i];
		newE[i] = this->e[i];
	}

	for (int i = this->cp; i < this->cp * RC - 1; ++i) {
		newUrm[i] = i + 1;
	}

	newUrm[this->cp * RC - 1] = -1;
	this->primLiber = this->cp;
	this->cp = this->cp * RC;

	delete[] this->urm;
	delete[] this->e;

	this->urm = newUrm;
	this->e = newE;
}

/**
* Caz favorabil: nu se face redimensionare
* Complexitate caz favorabil: theta(1)
* Caz defavorabil: se face redimensionare
* Complexitate caz favorabil: theta(cp * (RC - 1))
* 
* Complexitate: theta(1) amortizat
*/
int Matrice::creeazaNod(Celula e) {
	if (this->primLiber == -1) {
		redimSiReinitializare();
	}

	int pozitie = aloca();
	this->e[pozitie] = e;
	this->urm[pozitie] = -1;

	return pozitie;
}

/**
* Caz favorabil = Caz defavorabil = Caz Mediu
* Complexitate: theta(1)
*/
bool Matrice::rel(Celula c1, Celula c2) const {
	if (get<0>(c1) != get<0>(c2)) {
		return get<0>(c1) <= get<0>(c2);
	}
	return get<1>(c1) <= get<1>(c2);
}

/**
* Caz favorabil = Caz defavorabil = Caz Mediu
* Complexitate: theta(cp)
*/
Matrice::Matrice(int m, int n) {
	if (m <= 0 || n <= 0) {
		throw exception();
	}

	this->nrL = m;
	this->nrC = n;

	this->cp = INITIAL_CAPACITY;
	this->e = new Celula[cp];
	this->urm = new int[cp];

	initSpatiuLiber();
	this->prim = -1;
}


/**
* Caz favorabil = Caz defavorabil = Caz Mediu
* Complexitate: theta(1)
*/
int Matrice::nrLinii() const{
	return this->nrL;
}

/**
* Caz favorabil = Caz defavorabil = Caz Mediu
* Complexitate: theta(1)
*/
int Matrice::nrColoane() const{
	return this->nrC;
}

/**
* Caz favorabil: elementul are linia si coloana mai mici sau egale decat a primului element din lista
* Complexitate caz favorabil: theta(1)
* Caz defavorabil: elementul are linia si coloana mai mari sau egale decat a ultimului element din lista
* Complexitate caz favorabil: theta(n), n - numarul de elemente din lista
*
* Caz mediu: elementul se poate afla pe 1-a, a 2-a, ..., a n-a pozitie
* Complexitate caz mediu: theta(n)
* 
* Complexitate totala: O(n)
*/
TElem Matrice::element(int i, int j) const{
	if (i < 0 || j < 0 || i >= this->nrL || j >= this->nrC) {
		throw exception();
	}

	Celula myElem = { i, j, NULL_TELEMENT };


	int current = this->prim;
	while (current != -1 && rel(this->e[current], myElem)) {
		if (get<0>(this->e[current]) == i && get<1>(this->e[current]) == j) {
			return get<2>(this->e[current]);
		}

		current = this->urm[current];
	}

	return NULL_TELEMENT;
}


/**
* Caz favorabil: elementul are linia si coloana mai mici sau egale decat a primului element din lista
* Complexitate caz favorabil: theta(1)
* Caz defavorabil: elementul are linia si coloana mai mari sau egale decat a ultimului element din lista
* Complexitate caz favorabil: theta(n), n - numarul de elemente din lista
*
* Caz mediu: elementul trebuie inserat pe pe 1-a, a 2-a, ..., a n-a pozitie
* Complexitate caz mediu: theta(n)
*
* Complexitate totala: O(n)
*/
TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i >= this->nrL || j >= this->nrC) {
		throw exception();
	}

	Celula myElem = { i, j, e };

	if (this->prim == -1) {
		int pozitie = creeazaNod(myElem);
		this->prim = pozitie;
	}

	else {
		int current = -1;

		if (!rel(myElem, this->e[this->prim])) {
			current = this->prim;
			while (this->urm[current] != -1 && rel(this->e[this->urm[current]], myElem)) {
				current = this->urm[current];
			}
		}

		if (get<0>(this->e[current]) == i && get<1>(this->e[current]) == j) {
			TElem value = get<2>(this->e[current]);
			this->e[current] = myElem;

			return value;
		}
		else {

			int pozitie = creeazaNod(myElem);

			if (current == -1) {
				this->urm[pozitie] = this->prim;
				this->prim = pozitie;
			}
			else {
				this->urm[pozitie] = this->urm[current];
				this->urm[current] = pozitie;
			}

			return NULL_TELEMENT;
		}
	}


	return NULL_TELEMENT;
}


