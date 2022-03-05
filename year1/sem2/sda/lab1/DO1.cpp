#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

#define INITIAL_CAPACITY 64
#define RC 2
#define RM 2

#define Cheie first
#define Valoare second

DO::DO(Relatie r) {
  Array = (TElem*)malloc(INITIAL_CAPACITY * sizeof(TElem));
  Size = 0;
  Capacity = INITIAL_CAPACITY;
  Order = r;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
  
  /*int left = 0, right = Size - 1, mid;

  while(left <= right)
  {
    mid = left + (right - left) / 2;
    if(Array[mid].Cheie == c)
      {
        TValoare value = Array[mid].Valoare;
        Array[mid].Valoare = v;
        return value;
      }
    else if(Order(c, Array[mid].Valoare))
      right = mid - 1;
    else
      left = mid + 1;
  }*/
  for(int i = 0;i < Size && Order(Array[i].Cheie, c);++i)
    if(Array[i].Cheie == c)
    {
      TValoare value = Array[i].Valoare;
      Array[i].Valoare = v;
      return value;
    }

  if(Size == Capacity)
  {
    Capacity *= RC;
    TElem* newArray = new (nothrow) TElem[Capacity];
    for(int i = 0;i < Size;++i)
      newArray[i] = Array[i];
    delete Array;
    Array = newArray;
  }


  int position = 0;
  while(position < Size && Order(Array[position].Cheie, c))
    ++position;

  for(int i = Size;i > position;--i)
    Array[i] = Array[i - 1];
  ++Size;

  Array[position] = make_pair(c, v);

	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
  int left = 0, right = Size - 1, mid;

  while(left <= right)
  {
    mid = left + (right - left) / 2;
    if(Array[mid].Cheie == c)
      return Array[mid].Valoare;
    else if(Order(Array[mid].Valoare, c))
      left = mid + 1;
    else
      right = mid - 1;
  }

  /*for(int i = 0;i < Size;++i)
    if(Array[i].Cheie == c)
      return Array[i].Valoare;*/

	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
  if(Size == 0)
    return NULL_TVALOARE;

  TValoare value = NULL_TVALOARE;
  int position = -1;

  int left = 0, right = Size - 1, mid;
  while(left <= right)
  {
    mid = left + (right - left) / 2;
    if(Array[mid].Cheie == c)
      {
        value = Array[mid].Valoare;
        position = mid;
        Size--;
        break; 
      }
    else if(Order(c, Array[mid].Valoare))
      right = mid - 1;
    else
      left = mid + 1;
  }

  if(position != -1)
  {
    for(int i = position;i < Size;++i)
      Array[i] = Array[i + 1];    
  }

  if(Capacity > INITIAL_CAPACITY && Capacity / Size >= RM)
  {
    Capacity /= RM;
    TElem* newArray = new (nothrow) TElem[Capacity];
    for(int i = 0;i < Size;++i)
      newArray[i] = Array[i];
    delete Array;
    Array = newArray;
  }

	return value;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
  return Size;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	/* de adaugat */
	return (Size == 0); 
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
  delete Array;
}

