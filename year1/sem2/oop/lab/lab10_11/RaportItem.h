#pragma once
#include <string>

using std::string;

class RaportItem
{
private:
	string tip;
	int count;

public:
	RaportItem() = default;
	RaportItem(const string& tip, const int& count) : tip{ tip }, count{ count }{};

	/**
	* Functie care returneaza tipul
	*/
	const string& GetTip() noexcept;

	/**
	* Functie care returneaza count-ul
	*/
	const int& GetCount() noexcept;
	
	/**
	* Functie care seteaza count-ul la count-ul dat
	*/
	const int& SetCount(const int& count) noexcept;

	/**
	* Functie care incrementeaza count-ul
	*/
	RaportItem& operator++() noexcept;
};

