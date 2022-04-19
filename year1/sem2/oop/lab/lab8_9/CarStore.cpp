#include "CarStore.h"

void CarStore::addMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip) {
	Masina masina{ nrInmatriculare, producator, model, tip };

	validator.validate(masina);
	repo.store(masina);

	undoActions.push_back(std::make_unique<UndoStore>(repo, masina));
}

void CarStore::eraseMasina(const string& nrInmatriculare) {
	Masina const masina{ nrInmatriculare, "", "", "" };

	Masina masinaVeche = repo.find(nrInmatriculare);
	repo.erase(masina);

	undoActions.push_back(std::make_unique<UndoErase>(repo, masinaVeche));
}

void CarStore::modifyMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip) {
	Masina masina{ nrInmatriculare, producator, model, tip };

	validator.validate(masina);
	Masina masinaVeche = repo.find(nrInmatriculare);
	repo.modify(masina);

	undoActions.push_back(std::make_unique<UndoModify>(repo, masinaVeche));
}

const Masina& CarStore::findMasina(const string& nrInmatricular) {
	return repo.find(nrInmatricular);
}

const vector<Masina>& CarStore::getAll() const noexcept {
	return repo.getAll();
}

vector<Masina> CarStore::sortByNtInmatriculare() {
	auto sorted{ this->repo.getAll() };
	std::sort(sorted.begin(), sorted.end(), cmpNrInmatriculare);
	return sorted;
}

vector<Masina> CarStore::sortByTip() {
	auto sorted{ this->repo.getAll() };
	std::sort(sorted.begin(), sorted.end(), cmpTip);
	return sorted;
}

vector<Masina> CarStore::sortByProducatorAndModel() {
	auto sorted{ this->repo.getAll() };
	std::sort(sorted.begin(), sorted.end(), cmpProducatorAndModel);
	return sorted;
}

vector<Masina> CarStore::filterByProducator(string producator) {
	auto all{ this->repo.getAll() };
	vector<Masina> result(all.begin(), all.end());

	auto it = std::copy_if(all.begin(), all.end(), result.begin(), [&producator](const Masina& m) {
		return m.GetProducator() == producator;
		});
	result.resize(std::distance(result.begin(), it));

	return result;
}

vector<Masina> CarStore::filterByTip(string tip) {
	auto all{ this->repo.getAll() };
	vector<Masina> result(all.begin(), all.end());

	auto it = std::copy_if(all.begin(), all.end(), result.begin(), [&tip](const Masina& m) {
		return m.GetTip() == tip;
		});
	result.resize(std::distance(result.begin(), it));

	return result;
}

size_t CarStore::getListSize() const noexcept {
	return lista.size();
}

void CarStore::adaugaMasinaSpalate(const string& nrInmatriculare) {
	auto masina = this->repo.find(nrInmatriculare);

	lista.store(masina);
}

void CarStore::clearMasiniSpalate() noexcept {
	lista.clear();
}

void CarStore::exportMasiniSpalate(const string& fisier) {
	lista.exportFisier(fisier);
}

void CarStore::populeazaMasiniSpalate(const int& number) {
	auto all{ getAll() };

	if (number > all.size()) {
		throw SpalateException("Numar de masini prea mare!\n");
	}
	lista.clear();

	unsigned int const seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(all.begin(), all.end(), std::default_random_engine(seed));
	all.resize(number);

	for (const auto& masina : all) {
		lista.store(masina);
	}
}

const RaportItem CarStore::raportTip(const string& tip) {
	auto all{ getAll() };

	std::unordered_map<string, RaportItem> map;
	for (const auto& masina : all) {
		if (map.count(masina.GetTip()) == 0) {
			map[masina.GetTip()] = RaportItem(tip, 1);
		}
		else {
			map[masina.GetTip()].SetCount(map[masina.GetTip()].GetCount() + 1);
		}
	}

	return map[tip];
}

void CarStore::Undo() {
	if (undoActions.empty()) {
		throw CarStoreException("Nu mai exista operatii de undo!\n");
	}

	std::unique_ptr<ActiuneUndo> undo = std::move(undoActions.at(undoActions.size() - 1));
	(*undo).doUndo();
	undoActions.pop_back();
}