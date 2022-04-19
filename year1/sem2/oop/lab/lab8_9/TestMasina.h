#pragma once
#include "Masina.h"
#include <assert.h>
#include <sstream>
#include <fstream>
#include <iostream>

using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::ios;

class TestMasina
{
private:
	void testGetAndSet() const;
	void testCopy() const;
	void testCompare() const;
	void testPrint() const;
	void testIO() const;

public:
	void runAllTests() const;
};

