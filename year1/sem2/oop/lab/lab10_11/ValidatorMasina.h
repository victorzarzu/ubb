#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Masina.h"
#include "MultiStringException.h"

using std::string;
using std::vector;
using std::ostream;

class ValidateException : public MultiStringException {
	vector<string> errors;

public:
	ValidateException(const vector<string>& errors) : MultiStringException{ errors } {};
};

class ValidatorMasina {
private:
	const bool esteNrInmatriculare(const string& nrInmatriculare) const;
public:
	void validate(const Masina& masina) const;
};

