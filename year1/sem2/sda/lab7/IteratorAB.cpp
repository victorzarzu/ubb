#include "AB.h"
#include "IteratorAB.h"

/*
* Caz favorabil = stiva este goala
* Complexitate caz favorabil = theta(1)
*
* Caz defaborabil = stiva poate contine n elemente
* Complexitate caz defavorabil = theta(n)
*
* Caz mediu = stiva poate contine 0, 1, 2, ..., n elemente
* Complexitate caz mediu = theta(n)
*
* Complexitate totala = O(n)
*/
IteratorInordine::IteratorInordine(const AB& _ab) :ab{ _ab }, st(), curent{ NULL } {
	prim();
}

/*
* Caz favorabil = stiva este goala
* Complexitate caz favorabil = theta(1)
*
* Caz defaborabil = stiva poate contine n elemente
* Complexitate caz defavorabil = theta(n)
*
* Caz mediu = stiva poate contine 0, 1, 2, ..., n elemente
* Complexitate caz mediu = theta(n)
*
* Complexitate totala = O(n)
*/
void IteratorInordine::prim(){
	while (!this->st.empty()) {
		this->st.pop();
	}

	this->curent = this->ab.radacina;
	while (this->curent != NULL) {
		st.push(this->curent);
		this->curent = this->curent->stanga;
	}

	if (!this->st.empty()) {
		this->curent = this->st.top();
	}
}

/*
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate = theta(1)
*/
bool IteratorInordine::valid(){
	return this->curent != NULL;
}

/*
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate = theta(1)
*/
TElem IteratorInordine::element() {
	if (!valid()) {
		throw exception();
	}
	return this->curent->e;
}

/*
* Caz favorabil = nodul din capul stivei nu are subarbore drept
* Complexitate caz favorabil = theta(1)
*
* Caz defaborabil = subarborele drept al nodului curent poate contine n - 1 noduri
* Complexitate caz defavorabil = theta(n)
*
* Caz mediu = in subarborele drept al nodului curent se pot parcurge 0, 1, ... , n - 1 alte noduri
* Complexitate caz mediu = theta(n)
*
* Complexitate totala = O(n)
*/
void IteratorInordine::urmator(){
	this->curent = this->st.top();
	this->st.pop();

	if (this->curent->dreapta != NULL) {
		this->curent = this->curent->dreapta;
		while(this->curent != NULL)
		{
			this->st.push(this->curent);
			this->curent = this->curent->stanga;
		}
	}

	if (!this->st.empty()) {
		this->curent = this->st.top();
	}
	else {
		this->curent = NULL;
	}
}

/* 
* Caz favorabil = stiva este goala
* Complexitate caz favorabil = theta(1)
* 
* Caz defaborabil = stiva poate contine n/2 elemente
* Complexitate caz defavorabil = theta(n)
*
* Caz mediu = stiva poate contine 0, 1, 2, ..., n / 2 elemente
* Complexitate caz mediu = theta(n)
*
* Complexitate totala = O(n)
*/
IteratorPreordine::IteratorPreordine(const AB& _ab) :ab{ _ab }, st(), curent{ ab.radacina } {
	this->prim();
};

/* 
* Caz favorabil = stiva este goala
* Complexitate caz favorabil = theta(1)
* 
* Caz defaborabil = stiva poate contine n/2 elemente
* Complexitate caz defavorabil = theta(n)
* 
* Caz mediu = stiva poate contine 0, 1, 2, ..., n / 2 elemente
* Complexitate caz mediu = theta(n)
* 
* Complexitate totala = O(n)
*/
void IteratorPreordine::prim(){
	while (!this->st.empty()) {
		this->st.pop();
	}
	this->curent = this->ab.radacina;
}

/*
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate = theta(1)
*/
bool IteratorPreordine::valid(){
	return this->curent != NULL;
}

/*
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate = theta(1)
*/
TElem IteratorPreordine::element(){
	if (!valid()) {
		throw exception();
	}
	return this->curent->e;
}

/*
* Caz favorabil = nu exista subarbore drept
* Complexitate favorabil = theta(1)
*
* Caz defavorabil = exista subarbore drept
* Complexitate defavorabil = theta(1)
* 
* Caz mediu = poate exista sau nu subarbore drept
* Complexitate caz mediu = theta(1)
* 
* Complexitate = theta(1)
*/
void IteratorPreordine::urmator(){
	if (!valid()) {
		throw exception();
	}
	if (this->curent->dreapta != NULL) {
		this->st.push(this->curent->dreapta);
	}

	if (this->curent->stanga != NULL) {
		this->curent = this->curent->stanga;
	}
	else if(!this->st.empty()) {
		this->curent = this->st.top();
		this->st.pop();
	}
	else {
		this->curent = NULL;
	}

}

/*
* Caz faborabil = stiva este vida si radacina are doar un nod arborele stang
* Complexitate caz favorabil = theta(1)
*
* Caz defavorabil = stiva este plina si arborele este degenerat (are o structura de lista de valori de exemplu)
* Complexitate caz defavorabil = 2 * theta(n) = theta(n)
*
* Caz mediu = stiva poate sa aiba 0, 1, 2, ..., n elemente, iar while-ul se poate executa de 1, 2, ..., n ori
* Complexitate caz mediu = 2 * theta(n / 2) = theta(n)
*
* Complexitate totala = O(n)
*/
IteratorPostordine::IteratorPostordine(const AB& _ab) :ab{ _ab }, curent{ NULL }, st() {
	prim();
}

/* 
* Caz faborabil = stiva este vida si radacina are doar un nod arborele stang
* Complexitate caz favorabil = theta(1)
* 
* Caz defavorabil = stiva este plina si arborele este degenerat (are o structura de lista de valori de exemplu)
* Complexitate caz defavorabil = 2 * theta(n) = theta(n)
* 
* Caz mediu = stiva poate sa aiba 0, 1, 2, ..., n elemente, iar while-ul se poate executa de 1, 2, ..., n ori
* Complexitate caz mediu = 2 * theta(n / 2) = theta(n)
* 
* Complexitate totala = O(n)
*/
void IteratorPostordine::prim(){
	while (!this->st.empty()) {
		this->st.pop();
	}

	this->curent = ab.radacina;
	while (this->curent != NULL) {
		this->st.push(make_pair(this->curent, false));
		while (this->curent->stanga != NULL) {
			this->curent = this->curent->stanga;
			this->st.push(make_pair(this->curent, false));
		}

		this->st.pop();
		this->st.push(make_pair(this->curent, true));

		this->curent = this->curent->dreapta;
		while (this->curent != NULL && this->curent->stanga == NULL) {
			this->st.push(make_pair(this->curent, true));
			this->curent = this->curent->dreapta;
		}
	}

	if (!this->st.empty()) {
		this->curent = this->st.top().first;
		urmator();
	}


}

/*
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate = theta(1)
*/
bool IteratorPostordine::valid(){
	return this->curent != NULL;
}

/*
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate = theta(1)
*/
TElem IteratorPostordine::element(){
	if (!valid()) {
		throw exception();
	}
	return this->curent->e;
}

/*
* Caz favorabil - stiva este goala sau in varful stivei avem un element a caruti subarbore drept l-am vizitat
* Complexitate caz defavorabil = theta(1)
* 
* Caz defavorabil - am apelat prim imediat anterior, iar arborele are de exemplu forma 
    //       1
    //      / \
    //     2   3
    //    / \   
	//   5   6
	//      /
	//     ...
	//     /
	//    n
*/
void IteratorPostordine::urmator(){
	if (!valid()) {
		throw exception();
	}
	if (this->st.empty()) {
		this->curent = NULL;
		return;
	}

	while (true) {
		auto top = this->st.top();
		this->st.pop();

		if (top.second) {
			this->curent = top.first;
			break;
		}
		else {
			this->curent = top.first;
			this->st.push(make_pair(this->curent, true));
			this->curent = this->curent->dreapta;

			while (this->curent != NULL) {
				this->st.push(make_pair(this->curent, false));
				this->curent = this->curent->stanga;
			}
		}
	}
}

/*
* Caz favorabil = coada este goala
* Complexitate caz favorabil = theta(1)
*
* Caz defaborabil = coada poate contine n elemente
* Complexitate caz defavorabil = theta(n)
*
* Caz mediu = coada poate contine 0, 1, 2, ..., n elemente
* Complexitate caz mediu = theta(n)
*
* Complexitate totala = O(n)
*/
IteratorLatime::IteratorLatime(const AB& _ab) :ab{ _ab }, curent{ NULL }, q(){
	prim();
}

/*
* Caz favorabil = coada este goala
* Complexitate caz favorabil = theta(1)
*
* Caz defaborabil = coada poate contine n elemente
* Complexitate caz defavorabil = theta(n)
*
* Caz mediu = coada poate contine 0, 1, 2, ..., n elemente
* Complexitate caz mediu = theta(n)
*
* Complexitate totala = O(n)
*/
void IteratorLatime::prim(){
	while (!this->q.empty()) {
		q.pop();
	}
	this->curent = this->ab.radacina;
}

/*
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate = theta(1)
*/
bool IteratorLatime::valid(){
	return this->curent != NULL;
}

/*
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate = theta(1)
*/
TElem IteratorLatime::element(){
	if (!valid()) {
		throw exception();
	}
	return this->curent->e;
}

/*
* Caz favorabil = Caz defavorabil = Caz mediu
* Complexitate = theta(1)
*/
void IteratorLatime::urmator(){
	if (!valid()) {
		throw exception();
	}

	if (this->curent->stanga != NULL) {
		this->q.push(this->curent->stanga);
	}
	if (this->curent->dreapta != NULL) {
		this->q.push(this->curent->dreapta);
	}

	if (!this->q.empty()) {
		this->curent = this->q.front();
		this->q.pop();
	}
	else {
		this->curent = NULL;
	}
}
