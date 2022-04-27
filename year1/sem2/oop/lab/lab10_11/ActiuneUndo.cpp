#include "ActiuneUndo.h"

void UndoStore::doUndo() {
	this->repo.erase(masina);
}

void UndoErase::doUndo() {
	this->repo.store(masina);
}

void UndoModify::doUndo() {
	this->repo.modify(masina);
}