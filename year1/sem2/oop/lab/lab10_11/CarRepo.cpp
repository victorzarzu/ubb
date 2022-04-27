#include "CarRepo.h"

void CarRepo::store(const Masina& masina) {
	if (exista(masina)) {
		throw CarRepoException("Masina deja existenta!\n");
	}
	storage.push_back(masina);
}

void CarRepo::erase(const Masina& masina) {
	auto it = std::find_if(this->storage.begin(), this->storage.end(),
		[&masina](const Masina& masina1) noexcept{return masina == masina1; });
	if (it != this->storage.end()) {
		this->storage.erase(it);
	}
	else {
		throw CarRepoException("Masina inexistenta!\n");
	}
}

const Masina& CarRepo::find(const string& nrInmatriculare) const {
	auto it = std::find_if(this->storage.begin(), this->storage.end(), 
		[&nrInmatriculare](const Masina& masina) {return masina.GetNrInmatriculare() == nrInmatriculare; });

	if (it != this->storage.end()) {
		return *it;
	}

	throw CarRepoException("Masina inexistenta!\n");
}

bool CarRepo::exista(const Masina& masina) const {
	try {
		find(masina.GetNrInmatriculare());
		return true;
	}
	catch (const CarRepoException&) {
		return false;
	}
}

void CarRepo::modify(const Masina& masinaModify) {
	vector<Masina>::iterator it = std::find_if(this->storage.begin(), this->storage.end(),
		[&masinaModify](const Masina& masina) { return masina.GetNrInmatriculare() == masinaModify.GetNrInmatriculare(); });

	if (it != this->storage.end()) {
		*it = masinaModify;
	}
	else {
		throw CarRepoException("Masina inexistenta!\n");
	}
}

void CarRepo::clear() noexcept {
	storage.clear();
}


ostream& operator<<(ostream& out, const CarRepo& repo) {
	for (const auto& masina : repo.storage) {
		out << masina;
	}
	return out;
}

const vector<Masina>& CarRepo::getAll() const noexcept {
	return storage;
}

const unsigned int CarRepo::getLength() const noexcept{
	return static_cast<unsigned int>(storage.size());
}