#include "RaportItem.h"

const string& RaportItem::GetTip() noexcept{
	return this->tip;
}

const int& RaportItem::GetCount() noexcept{
	return this->count;
}

const int& RaportItem::SetCount(const int& count) noexcept {
	return this->count = count;
}

RaportItem& RaportItem::operator++() noexcept{
	this->count++;
	return *this;
}