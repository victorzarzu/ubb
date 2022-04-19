#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

/**
* Complexitate timp constant: theta(1)
*/
int Dictionar::hashCode(TCheie c) const {
	if (c < 0) {
		return -c;
	}
	return c;
}
/**
* Complexitate timp constant: theta(1)
*/
int Dictionar::hash(TCheie c) const {
	return hashCode(c) % this->m;
}

/**
* Complexitate timp constant: theta(1)
*/
int Dictionar::d(TCheie c, int i) const {
	float c1 = 0.5, c2 = 0.5;
	return ((int)(hash(c) + i * c1 + i * i * c2)) % this->m;
}

void Dictionar::redimAndRehashing() {
	TElem* newE = new TElem[this->m * 2];
	for (int i = 0; i < this->m * 2; ++i) {
		newE[i] = std::make_pair(NIL, NIL);
	}

	TElem* oldE = this->e;
	this->e = newE;
	this->m = this->m * 2;
	this->size = 0;

	for (int i = 0; i < this->m / 2; ++i) {
		if (oldE[i].first != NIL) {
			this->adauga(oldE[i].first, oldE[i].second);
		}

	}


	delete[] oldE;
}

/**
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate: theta(m)
*/
Dictionar::Dictionar() {
	this->m = INITIAL_SIZE;
	this->e = new TElem[INITIAL_SIZE];
	for (int i = 0; i < this->m; ++i) {
		this->e[i] = std::make_pair(NIL, NIL);
	}
	this->size = 0;
}

/**
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate: theta(1)
*/
Dictionar::~Dictionar() {
	delete[] this->e;
}

/**
* Caz favorabil = locatia de dispersie este libera
* Complexitate caz favorabil = theta(1)
*
* Caz defavorabil = perechea de poate insera la sfarsitul secventei de dispersie sau tabela este plina
* Complexitate caz favorabil = theta(m)
*
* Complexitate caz mediu = theta(1)
*/
TValoare Dictionar::adauga(TCheie c, TValoare v) {

	bool gasit = false;
	int i = 0;
	do {
		int j = d(c, i);

		if (this->e[j].first == NIL || this->e[j].first == STERS) {
			gasit = true;
			this->e[j] = std::make_pair(c, v);
			this->size = this->size + 1;
		}
		else if (this->e[j].first == c) {
			TValoare value = this->e[j].second;
			this->e[j] = std::make_pair(c, v);
			return value;
		}
		else {
			i = i + 1;
		}

	} while (i < this->m && !gasit);

	if (i == this->m) {
		redimAndRehashing();
		return adauga(c, v);
	}

	return NULL_TVALOARE;
}


/**
* Caz favorabil = cheia se afla in locatia ei de dispersie
* Complexitate caz favorabil = theta(1)
*
* Caz defavorabil = cheia nu exista si in fiecare locatie a secventei ei de cautare este stocat ceva
* Complexitate caz favorabil = theta(m)
*
* Complexitate caz mediu = theta(1)
*/
TValoare Dictionar::cauta(TCheie c) const {
	int i = 0, j = 0;

	do {
		j = d(c, i);
		if (this->e[j].first == c) {
			return this->e[j].second;
		}
		else {
			++i;
		}
	} while (i < this->m && this->e[j].first != NIL);


	return NULL_TVALOARE;
}

/**
* Caz favorabil = cheia se afla in locatia ei de dispersie
* Complexitate caz favorabil = theta(1)
*
* Caz defavorabil = cheia nu exista si in fiecare locatie a secventei ei de cautare este stocata o pereche cheia valoare
* Complexitate caz favorabil = theta(m)
*
* Complexitate caz mediu = theta(1)
*/
TValoare Dictionar::sterge(TCheie c) {
	int position = 0, i = 0;
	bool gasit = false;
	TValoare value = NULL_TVALOARE;

	do {
		position = d(c, i);
		if (this->e[position].first == c) {
			gasit = true;
			value = this->e[position].second;
			this->e[position] = std::make_pair(STERS, STERS);
			this->size = this->size - 1;
		}
		else {
			i++;
		}
	} while (this->e[position].first != NIL && !gasit && i < this->m);

	return value;

	//i++;
	//int j = d(c, i);
	//while (i < this->m && this->e[j].first != NIL) {
	//	int p = hash(this->e[j].first);
	//	if (position < j) {
	//		if (0 <= p && p <= position) {
	//			this->e[position] = this->e[j];
	//			position = j;
	//		}
	//		else if (j < p && p < this->m){
	//			this->e[position] = this->e[j];
	//			position = j;
	//		}
	//	}
	//	else if (j < position) {
	//		if (j < p && p <= position) {
	//			this->e[position] = this->e[j];
	//			position = j;
	//		}
	//	}

	//	i++;
	//	j = d(c, i);
	//}

	//this->e[position] = std::make_pair(NIL, NIL);
	//return value;
}

/**
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate: theta(1)
*/
int Dictionar::dim() const {
	return this->size;
}

/**
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate: theta(1)
*/
bool Dictionar::vid() const {
	return this->size == 0;
}

/**
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate: theta(1)
*/
IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}


