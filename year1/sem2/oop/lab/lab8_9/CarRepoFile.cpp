#include "CarRepoFile.h"

void CarRepoFile::loadFromFile() {
	std::ifstream in(this->filename,std::ios::in);

	if (!in.is_open()) {
		
		throw CarRepoException("Open error: " + this->filename + "\n");
	}

	if (in.peek() == std::ifstream::traits_type::eof()) {
		return;
	}

	while (!in.eof()) {
		if (in.peek() == std::ifstream::traits_type::eof()) {
			return;
		}
		Masina masina;
		in >> masina;
		CarRepo::store(masina);
	}
}

void CarRepoFile::writeToFile() {
	std::ofstream out(this->filename, std::ios::trunc);

	if (!out.is_open()) {
		throw CarRepoException("Open error: " + this->filename + "\n");
	}

	for (const auto& masina : getAll()) {
		out << masina;
	}
}

void CarRepoFile::store(const Masina& masina) {
	CarRepo::store(masina);
	this->writeToFile();
}

void CarRepoFile::erase(const Masina& masina) {
	CarRepo::erase(masina);
	this->writeToFile();
}

void CarRepoFile::modify(const Masina& masinaModify) {
	CarRepo::modify(masinaModify);
	this->writeToFile();
}