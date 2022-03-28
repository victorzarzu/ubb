#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"
#include <utility>

using std::make_pair;

TElem NodLSI::GetValue() const { //theta(1)
	return this->val;
}

NodLSI* NodLSI::GetUrm() const { //theta(1)
	return this->urm;
}

void NodLSI::setUrm(NodLSI* nod) { //theta(1)
	this->urm = nod;
}

void NodLSI::setValue(TValoare value) { //theta(1)
	this->val.second = value;
}

Dictionar::Dictionar() : Prim{ NULL }, Size{ 0 }{};

/*
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate: theta(n)
*/
Dictionar::~Dictionar() {
	while (Prim != NULL) {
		sterge(Prim->GetValue().first);
	}
}

/*
* Caz favorabil: exista cheia de intrare in dictionar pe prima pozitie
* Complexitate caz favorabil: theta(1)
* 
* Caz defavorabil: cheia nu exista in dictionar
* Complexitate caz defavorabil: theta(n)
* 
* Caz mediu: avem n + 1 cazuri: cheia nu se afla in lista sau se afla se poate afla pe pozitiile 1, 2, 3, ... , n
* Complexitate caz mediu: sum(i/(n + 1)) => T(n) apartine theta(n)
* 
* Complexitate totala: O(n)
*/
TValoare Dictionar::adauga(TCheie c, TValoare v){

	if (this->Prim == NULL) {
		NodLSI* nou = new NodLSI(make_pair(c, v));
		this->Prim = nou;
		this->Size = 1;

		return NULL_TVALOARE;
	}

	NodLSI* current = this->Prim;

	while (current != NULL && current->GetValue().first != c) {
		current = current->GetUrm();
	}

	if (current != NULL) {
		TValoare value = current->GetValue().second;
		current->setValue(v);
		return value;
	}

	NodLSI* nou = new NodLSI(make_pair(c, v));
	nou->setUrm(this->Prim);
	this->Prim = nou;
	this->Size += 1;

	return NULL_TVALOARE;
}



//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
/*
* Caz favorabil: exista cheia de intrare in dictionar pe prima pozitie
* Complexitate caz favorabil: theta(1)
*
* Caz defavorabil: cheia nu exista in dictionar
* Complexitate caz defavorabil: theta(n)
*
* Caz mediu: avem n + 1 cazuri: cheia nu se afla in lista sau se afla se poate afla pe pozitiile 1, 2, 3, ... , n
* Complexitate caz mediu: sum(i/(n + 1)) => T(n) apartine theta(n)
*
* Complexitate totala: O(n)
*/
TValoare Dictionar::cauta(TCheie c) const{
	NodLSI* current = this->Prim;
	while (current != NULL && current->GetValue().first != c) {
		current = current->GetUrm();
	}

	if (current != NULL) {
		return current->GetValue().second;
	}

	return NULL_TVALOARE;
}

/*
* Caz favorabil: exista cheia de intrare in dictionar pe prima pozitie
* Complexitate caz favorabil: theta(1)
*
* Caz defavorabil: cheia nu exista in dictionar
* Complexitate caz defavorabil: theta(n)
*
* Caz mediu: avem n + 1 cazuri: cheia nu se afla in lista sau se afla se poate afla pe pozitiile 1, 2, 3, ... , n
* Complexitate caz mediu: sum(i/(n + 1)) => T(n) apartine theta(n)
*
* Complexitate totala: O(n)
*/
TValoare Dictionar::sterge(TCheie c){
	if (this->Prim == NULL) {
		return NULL_TVALOARE;
	}

	NodLSI* current = this->Prim;

	if (this->Prim->GetValue().first == c) {
		TValoare value = this->Prim->GetValue().second;
		this->Prim = this->Prim->GetUrm();

		this->Size--;
		delete current;


		return value;
	}
	else {
		while (current->GetUrm() != NULL && current->GetUrm()->GetValue().first != c) {
			current = current->GetUrm();
		}
		
		if (current->GetUrm() != NULL) {
			NodLSI* sters = current->GetUrm();
			NodLSI* con = sters->GetUrm();
			current->setUrm(con);
			
			TValoare value = sters->GetValue().second;

			this->Size--;
			delete sters;
			return value;
		}
	}

	return NULL_TVALOARE;
}

/*
* Complexitate constanta: theta(1)
*/
int Dictionar::dim() const {
	return this->Size;
}

/*
* Complexitate constanta: theta(1)
*/
bool Dictionar::vid() const{
	return this->Size == 0;
}

/*
* Complexitate constanta: theta(1)
*/
IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}


