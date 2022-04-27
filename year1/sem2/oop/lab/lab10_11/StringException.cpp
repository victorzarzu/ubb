#include "StringException.h"

ostream& operator<<(ostream& out, const StringException& exception) {
	for (const auto& error : exception.message) {
		out << error;
	}
	return out;
}

const string StringException::toString() const {
	return this->message;
}