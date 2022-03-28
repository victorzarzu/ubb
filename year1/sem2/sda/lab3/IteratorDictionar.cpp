#include "IteratorDictionar.h"
#include "Dictionar.h"

using namespace std;

/*
* Complexitate constanta: theta(1)
*/
IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d), current{d.Prim}{
	/* de adaugat */
}

/*
* Complexitate constanta: theta(1)
*/
void IteratorDictionar::prim() {
	this->current = this->dict.Prim;
}

/*
* Complexitate constanta: theta(1)
*/
void IteratorDictionar::urmator() {
	if (!valid()) {
		throw exception();
	}

	this->current = this->current->GetUrm();
}

/*
* Complexitate constanta: theta(1)
*/
TElem IteratorDictionar::element() const{
	if (!valid()) {
		throw exception();
	}
	
	return pair <TCheie, TValoare>  (this->current->GetValue().first, this->current->GetValue().second);
}

/*
* Complexitate constanta: theta(1)
*/
bool IteratorDictionar::valid() const {
	return (this->current != NULL);
}

