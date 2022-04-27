#include "MasiniSpalate.h"

void MasiniSpalate::clear() noexcept {
	this->all.clear();
}

size_t MasiniSpalate::size() const noexcept {
	return this->all.size();
}

void MasiniSpalate::exists(const string& nrInmatriculare) {
	auto it = std::find_if(this->all.begin(), this->all.end(), [&](const Masina& masina) {
		return nrInmatriculare == masina.GetNrInmatriculare();
		});
	if (it != this->all.end()) {
		throw SpalateException("Masina deja adaugata!\n");
	}
}

void MasiniSpalate::store(const Masina& masina) {
	exists(masina.GetNrInmatriculare());

	this->all.push_back(masina);
}

void MasiniSpalate::exportFisier(const string& fisier) {
	ofstream out{ fisier };

	if (out.fail()) {
		return;
	}

	for (const auto& masina : this->all) {
		out << masina;
	}

	out.close();
}

const vector<Masina> MasiniSpalate::getAll() const {
	return this->all;
}
