#include "MultiStringException.h"

ostream& operator<<(ostream& out, const MultiStringException& exception) {
	for (const auto& error : exception.errors) {
		out << error;
	}
	return out;
}

const string MultiStringException::toString() const {
	string result = "";
	for (const auto& str : errors) {
		result += str + "\n";
	}

	return result;
}
