#include "CosMasini.h"

void CosMasini::clear() noexcept {
	this->cosMasini.clear();
	this->notify();
}

size_t CosMasini::size() const noexcept {
	return this->cosMasini.size();
}

void CosMasini::exists(const Masina& masina) {
	auto it = std::find(this->cosMasini.begin(), this->cosMasini.end(), masina);
	if (it != this->cosMasini.end()) {
		throw CosException("Masina deja adaugata in cos!\n");
	}
}

void CosMasini::adaugaMasina(const Masina& masina) {
	exists(masina);

	this->cosMasini.push_back(masina);
	this->notify();
}

void CosMasini::stergeMasina(const Masina& masina) {
	auto it = std::find(this->cosMasini.begin(), this->cosMasini.end(), masina);

	if (it == this->cosMasini.end()) {
		throw CosException("Masina nu exista in cos!\n");
	}
	this->cosMasini.erase(it);
	this->notify();
}

const vector<Masina> CosMasini::getAll() const {
	return this->cosMasini;
}