#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(n), n - numarul de noduri din arbore
*/
void AB::distruge(Nod* nod) {
	if (nod != NULL) {
		distruge(nod->stanga);
		distruge(nod->dreapta);
		delete nod;
	}
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(n), n - numarul de noduri din arbore
*/
void AB::distrugeSubarbori(Nod* nod) {
	if (nod != NULL) {
		distruge(nod->stanga);
		distruge(nod->dreapta);
	}
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(n), n - numarul de noduri din arbore
*/
Nod* AB::copiere(Nod* nod) const {
	if (nod != NULL) {
		Nod* nodNew = new Nod(nod->e, NULL, NULL);
		nodNew->stanga = copiere(nod->stanga);
		nodNew->dreapta = copiere(nod->dreapta);
		return nodNew;
	}
	return NULL;
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(1)
*/
AB::AB() {
	this->radacina = NULL;
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(n), n - numarul de noduri din arbore
*/
AB::AB(const AB& ab) {
	this->radacina = copiere(ab.radacina);
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(1)
*/
AB::AB(TElem e){
	this->radacina = new Nod(e, NULL, NULL);
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(n + m), n - numarul de noduri din arborele stang, m - numarul de noduri din arborele drept
*/
AB::AB(const AB& st, TElem e, const AB& dr){
	distruge(this->radacina);

	this->radacina = new Nod(e, NULL, NULL);
	this->radacina->stanga = copiere(st.radacina);
	this->radacina->dreapta = copiere(dr.radacina);
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(n + m), n - numarul de noduri din subarborele stang vechi, m - numarul de noduri din subarborele stang nou
*/
void AB::adaugaSubSt(const AB& st){
	if (this->radacina == NULL) {
		throw exception();
	}

	distruge(this->radacina->stanga);
	this->radacina->stanga = copiere(st.radacina);
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(n + m), n - numarul de noduri din subarborele drept vechi, m - numarul de noduri din subarborele drept nou
*/
void AB::adaugaSubDr(const AB& dr){
	if (this->radacina == NULL) {
		throw exception();
	}

	distruge(this->radacina->dreapta);
	this->radacina->dreapta = copiere(dr.radacina);
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(1)
*/
TElem AB::element() const{
	if (this->radacina == NULL) {
		throw exception();
	}
	return this->radacina->e;
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(n), n - numarul de noduri din subarborele stang
*/
AB AB::stang() const{
	if (this->radacina == NULL) {
		throw exception();
	}

	AB ab;
	ab.radacina = copiere(this->radacina->stanga);
	return ab;
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(n), n - numarul de noduri din subarborele drept
*/
AB AB::drept() const{
	if (this->radacina == NULL) {
		throw exception();
	}

	AB ab;
	ab.radacina = copiere(this->radacina->dreapta);
	return ab;
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(n), n - numarul de noduri din arbore
*/
AB::~AB() {
	distruge(this->radacina);
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = theta(1)
*/
bool AB::vid() const{
	return this->radacina == NULL;
}

/*
* Caz favorabil = Caz devavorabil = Caz mediu
* Complexitate = O(timp constructor iterator)
*/
IteratorAB* AB::iterator(string s) const {
	if (s=="preordine")
		return new IteratorPreordine(*this);
	if (s=="inordine")
		return new IteratorInordine(*this);
	if (s=="postordine")
		return new IteratorPostordine(*this);
	if (s=="latime")
		return new IteratorLatime(*this);
	return nullptr;
};
