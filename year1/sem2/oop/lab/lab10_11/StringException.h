#pragma once

#include <vector>
#include <string>
#include <sstream>

using std::vector;
using std::string;
using std::ostream;

class StringException
{
	string message;
public:
	StringException(string message) : message{ message } {};

	/**
	* Functie care returneaza un string cu eroarea
	*
	* @params: -
	*
	* @return: string;
	*/
	const string toString() const;

	/**
	* Functie generica pentru afisarea unei CarRepoException
	*
	* @params: out - o referinta la un string de tip ostream
	*		   ex - o referinta constanta la o CarRepoException
	*
	* @return: o referinta la un string de tip ostream
	*/
	friend ostream& operator<<(ostream& out, const StringException& ex);
};

