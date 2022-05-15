#pragma once
#include <vector>
#include <algorithm>

using std::vector;

class Observer {
public:
	virtual void update() = 0;

	virtual ~Observer() {};
};

class Observable {
private:
	vector<Observer*> observers;

public:

	/*
	* Functie care adauga un observer
	* 
	* @params: obs - un pointer spre un observer
	* 
	* @return: -
	*/
	void addObserver(Observer* obs);
	
	/*
	* Functie care sterge un observer
	*
	* @params: obs - un pointer spre un observer
	*
	* @return: -
	*/
	void removeObserver(Observer* obs);

	/*
	* Functie care notifica observerii
	* 
	* @params: -
	* 
	* @return: -
	*/
	void notify() const;
};

