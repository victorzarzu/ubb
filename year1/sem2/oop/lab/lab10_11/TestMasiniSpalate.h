#pragma once
#include "Masina.h"
#include "MasiniSpalate.h"
#include "CosMasini.h"
#include <assert.h>

class TestMasiniSpalate
{
private:
	void testAddDelete() const;
	void testExport() const;
public:
	void runAllTests() const;
};

