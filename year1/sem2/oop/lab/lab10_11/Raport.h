#pragma once

#include <unordered_map>
#include "RaportItem.h"
#include "Masina.h"

using std::unordered_map;

class Raport {
private:
	unordered_map<string, RaportItem> map;

public:
	Raport() = default;
	Raport(const Raport& ot) = delete;

	void add(const Masina& masina);

	const RaportItem getTip(const string& tip) const;
};