#include "Masina.h"


string Masina::GetNrInmatriculare() const {
	return this->nrInmatriculare;
}

string Masina::GetProducator() const {
	return this->producator;
}

string Masina::GetModel() const {
	return this->model;
}

string Masina::GetTip() const {
	return this->tip;
}

void Masina::SetNrInmatriculare(const string& nrInmatriculare) {
	this->nrInmatriculare = nrInmatriculare;
}

void Masina::SetProducator(const string& producator) {
	this->producator = producator;
}

void Masina::SetModel(const string& model) {
	this->model = model;
}

void Masina::SetTip(const string& tip) {
	this->tip = tip;
}

Masina& Masina::operator=(const Masina& ot) {
	if (this == &ot) {
		return *this;
	}

	this->nrInmatriculare = ot.nrInmatriculare;
	this->model = ot.model;
	this->producator = ot.producator;
	this->tip = ot.tip;

	return *this;
}

bool Masina::operator==(const Masina& ot) const noexcept{
	return this->nrInmatriculare == ot.nrInmatriculare;
}

ostream& operator<<(ostream& out, const Masina& masina) {
	out << masina.GetNrInmatriculare() << " | " << masina.GetProducator() << " | " << masina.GetModel() << " | " << masina.GetTip() << std::endl;
	return out;
}

istream& operator>>(istream& in, Masina& masina) {
	string line, now;
	//getline(in, line);
	//in >> masina.nrInmatriculare; in >> now;
	//in >> masina.producator; in >> now;
	//in >> masina.model; in >> now;
	//in >> masina.tip;
	getline(in, line);
	std::istringstream input(line);
	input >> masina.nrInmatriculare; input >> now;
	input >> masina.producator; input >> now;
	input >> masina.model; input >> now;
	input >> masina.tip;

	
	return in;
}

bool cmpNrInmatriculare(const Masina& m1, const Masina& m2) {
	return m1.GetNrInmatriculare() < m2.GetNrInmatriculare();
}

bool cmpTip(const Masina& m1, const Masina& m2) {
	return m1.GetTip() < m2.GetTip();
}

bool cmpProducatorAndModel(const Masina& m1, const Masina& m2) {
	auto producator1 = m1.GetProducator();
	auto producator2 = m2.GetProducator();

	if (producator1 != producator2) {
		return producator1 < producator2;
	}

	return m1.GetModel() < m2.GetModel();
}