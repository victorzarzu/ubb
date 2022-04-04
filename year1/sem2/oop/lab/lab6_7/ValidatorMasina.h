#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Masina.h"

using std::string;
using std::vector;
using std::ostream;

class ValidateException
{
	vector<string> errors;

public:
	ValidateException(const vector<string>& errors) : errors{ errors } {};

	friend ostream& operator<<(ostream& out, const ValidateException& val);
};

class ValidatorMasina
{
private:
	const bool esteNrInmatriculare(const string& nrInmatriculare) const;
public:
	void validate(const Masina& masina) const;
};

