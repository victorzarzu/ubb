#include "Raport.h"

void Raport::add(const Masina& masina) {
	if (map.count(masina.GetTip()) == 0) {
		map[masina.GetTip()] = RaportItem(masina.GetTip(), 1);
	}
	else {
		map[masina.GetTip()].SetCount(map[masina.GetTip()].GetCount() + 1);
	}
}

const RaportItem Raport::getTip(const string& tip) const {
	if (this->map.count(tip) == 0) {
		return RaportItem{"", 0 };
	}
	return this->map.at(tip);
}