#include "MultiStringException.h"

ostream& operator<<(ostream& out, const MultiStringException& exception) {
	for (const auto& error : exception.errors) {
		out << error;
	}
	return out;
}
