#pragma once
#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::ostream;

class MultiStringException
{
	vector<string> errors;

public:
	MultiStringException(const vector<string>& errors) : errors{ errors } {};

	friend ostream& operator<<(ostream& out, const MultiStringException& val);
};

