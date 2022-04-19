#pragma once
#include "CarRepo.h"
#include "ActiuneUndo.h"
#include <assert.h>

class TestUndo
{
private:
	void testUndoStore() const;
	void testUndoErase() const;
	void testUndoModify() const;
public:

	void runAllTests() const;
};

