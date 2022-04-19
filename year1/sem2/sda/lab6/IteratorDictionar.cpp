#include "IteratorDictionar.h"
#include "Dictionar.h"

using namespace std;

/**
* Caz favorabil = in locatia curenta este stocata o pereche cheie valoare
* Complexitate caz favorabil = theta(1) 
* 
* Caz defavorabil = tabela este goala
* Complexitate caz defavorabil = theta(m)
* 
* Caz mediu = o locatie ocupata poate fi in 1,2,...,m pozitii fata de cea curenta
* Complexitate caz mediu = theta(m)
* 
* Complexitate: O(m)
*/
void IteratorDictionar::deplasare() {
	while (this->position < this->dict.m && (this->dict.e[position].first == NIL || this->dict.e[position].first == STERS)) {
		this->position = this->position + 1;
	}
}

/**
* Caz favorabil = in locatia curenta este stocata o pereche cheie valoare
* Complexitate caz favorabil = theta(1)
*
* Caz defavorabil = tabela este goala
* Complexitate caz defavorabil = theta(m)
*
* Caz mediu = o locatie ocupata poate fi in 1,2,...,m pozitii fata de cea curenta
* Complexitate caz mediu = theta(m)
*
* Complexitate: O(m)
*/
IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
	this->position = 0;
	deplasare();
}

/**
* Caz favorabil = in locatia curenta este stocata o pereche cheie valoare
* Complexitate caz favorabil = theta(1)
*
* Caz defavorabil = tabela este goala
* Complexitate caz defavorabil = theta(m)
*
* Caz mediu = o locatie ocupata poate fi in 1,2,...,m pozitii fata de cea curenta
* Complexitate caz mediu = theta(m)
*
* Complexitate: O(m)
*/
void IteratorDictionar::prim() {
	this->position = 0;
	deplasare();
}

/**
* Caz favorabil = in locatia curenta este stocata o pereche cheie valoare
* Complexitate caz favorabil = theta(1)
*
* Caz defavorabil = tabela este goala
* Complexitate caz defavorabil = theta(m)
*
* Caz mediu = o locatie ocupata poate fi in 1,2,...,m pozitii fata de cea curenta
* Complexitate caz mediu = theta(m)
*
* Complexitate: O(m)
*/
void IteratorDictionar::urmator() {
	if (this->position >= this->dict.m) {
		throw exception();
	}
	this->position = this->position + 1;
	deplasare();
}

/**
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate: theta(1)
*/
TElem IteratorDictionar::element() const{
	if (this->position >= this->dict.m) {
		throw exception();
	}

	return this->dict.e[this->position];
}

/**
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate: theta(1)
*/
bool IteratorDictionar::valid() const {
	return this->position < this->dict.m;
}

