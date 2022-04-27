#pragma once
#include "Masina.h"
#include "CarRepo.h"

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;

	virtual ~ActiuneUndo() {};
};

class UndoStore : public ActiuneUndo {
	Masina masina;
	CarRepo& repo;

public:
	UndoStore(CarRepo& repo, const Masina& masina) : masina{ masina }, repo{ repo }{};

	/**
	* Functie care face opearatia de undo pentru adaugare
	* 
	* @params: -
	* 
	* @return: -
	*/
	void doUndo() override;
};

class UndoErase : public ActiuneUndo {
	Masina masina;
	CarRepo& repo;

public:
	UndoErase(CarRepo& repo, const Masina& masina) : masina{ masina }, repo{ repo }{};

	/**
	* Functie care face opearatia de undo pentru stergere
	*
	* @params: -
	*
	* @return: -
	*/
	void doUndo() override;
};

class UndoModify : public ActiuneUndo {
	Masina masina;
	CarRepo& repo;

public:
	UndoModify(CarRepo& repo, const Masina& masina) : masina{ masina }, repo{ repo }{};

	/**
	* Functie care face opearatia de undo pentru modificare
	*
	* @params: -
	*
	* @return: -
	*/
	void doUndo() override;
};

