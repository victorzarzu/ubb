#pragma once
#include "Masina.h"
#include "CarRepo.h"
#include "CarRepoFile.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

class TestRepo
{
	void testStore() const;
	void testErase() const;
	void testFind() const;
	void testGetAll() const;
	void testPrint() const;
	void testModify() const;
	
	void testFileLoad() const;
	void testFileStore() const;
	void testFileErase() const;
	void testFileModify() const;

public:
	void runAllTests() const;
};

