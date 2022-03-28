#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;


/*
Caz favorabil = Caz defavorabil = Caz mediu
Complexitate: constanta - θ(1)
*/
DO::DO(Relatie r) :Order{r}{
  Array = (TElem*)malloc(INITIAL_CAPACITY * sizeof(TElem));
  Size = 0;
  Capacity = INITIAL_CAPACITY;
}

void DO::holdUp() { //theta(1) amortizat
    if (this->Size == this->Capacity)
    {
        Capacity *= RC;
        TElem* newArray = new (nothrow) TElem[Capacity];
        for (int i = 0; i < Size; ++i)
            newArray[i] = Array[i];
        delete[] Array;

        this->Array = newArray;
    }
}

void DO::holdDown() { //theta(1) amortizat
    if (Capacity > INITIAL_CAPACITY && Capacity / Size >= RM)
    {
        Capacity /= RM;
        TElem* newArray = new (nothrow) TElem[Capacity];
        for (int i = 0; i < Size; ++i)
            newArray[i] = Array[i];
        delete[] Array;
        this->Array = newArray;
    }
}

//returneaza pozitia pe care se afla sau trebuie inserata cheia in dictionar cheia in dictionar
/*
Caz favorabil: elementul de adaugat este in relatie cu primul sau ultimul este in relatie cu acesta
Complexitate caz favorabil: θ(1)

Caz defavorabil: pozitie pe care trebuie inserat elementul este in interiorul listei
Complexitate caz defavorabil: θ(logn)

Caz mediu: probabilitatea ca elementul sa se trebuiasca sa se insereze la uncapat este de 2/n, iar pentru a se insera in interior este (n-2)/n
Complexitate caz mediu: T(n) = 2/n + lognΣ(i = 1,n - 2)1/(n - 2) = logn => T(n) apartine θ(logn)

Complexitate generala: O(logn)
*/
int DO::pozitie(TCheie c) const
{
  if(this->Size == 0)
    return 0;

  int left = 0, right = Size - 1, mid, position;

  if(Order(c, Array[0].Cheie))
    position = 0;
  else if(Order(Array[Size - 1].Cheie, c))
    {
      if(c == this->Array[Size - 1].Cheie)
        position = Size - 1;
      else
        position = Size;
    }
  else
  {
    while(left <= right)
    {
      mid = left + (right - left) / 2;
      if(Order(c, Array[mid].Cheie))
        position = mid, right = mid - 1;
      else
        left = mid + 1;
    }
  }
  
  return position;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
/*
Complexitatea realocarii este de θ(1) amortizat

Caz favorabil: elementul trebuie adaugat la sfarsit
Complexitate caz favorabil: θ(1)

Caz defavorabil: elementul trebuie adaugat la inceput
Complexitate caz defavorabil: θ(n)

Caz mediu: probabilitatea de a trebui adaugat in orice pozitie este 1/n
Complexitate caz mediu: T(n) = logn + Σ(i = 1,n)i/n => T(n) apartine θ(n)

Complexitate totala: O(n)
*/
TValoare DO::adauga(TCheie c, TValoare v) { //este O(n)
  
  int position = pozitie(c);
  if(position < Size && this->Array[position].Cheie == c)
  {
    TValoare value = this->Array[position].Valoare;
    this->Array[position].Valoare = v;
    return value;
  }

  holdUp();

  position = pozitie(c);
  for(int i = Size;i > position;--i)
    Array[i] = Array[i - 1];
  ++Size;
  
  Array[position] = make_pair(c, v);

	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
/*
complexitatea de la pozitie
*/
TValoare DO::cauta(TCheie c) const { //este O(logn)
  if(Size == 0)
    return NULL_TVALOARE;

  int position = pozitie(c);
  if(position < Size && this->Array[position].Cheie == c)
    return this->Array[position].Valoare;

	return NULL_TVALOARE;	
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
/*
Complexitatea realocarii este de θ(1) amortizat

Caz favorabil: elementul trebuie sters de la sfarsit
Complexitate caz favorabil: θ(1)

Caz defavorabil: elementul trebuie sters de la inceput
Complexitate caz defavorabil: θ(n)

Caz mediu: probabilitatea de a trebui sters in orice pozitie este 1/n
Complexitate caz mediu: T(n) = logn + Σ(i = 1,n)i/n => T(n) apartine θ(n)

Complexitate totala: O(n)
*/
TValoare DO::sterge(TCheie c) { //este O(n)
    if (Size == 0) {
        return NULL_TVALOARE;
    }

    TValoare value = NULL_TVALOARE;
    int position = pozitie(c);
    if(position < Size && this->Array[position].Cheie == c) {
        value = this->Array[position].Valoare;
        Size--;
        for (int i = position; i < Size; ++i) {
            Array[i] = Array[i + 1];
        }
    }

    holdDown();

    return value;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
/*
Caz favorabil = Caz defavorabil = Caz mediu
Complexitate: constanta - θ(1)
*/
int DO::dim() const { //este theta(1)
  return Size;
}

//verifica daca dictionarul e vid
/*
Caz favorabil = Caz defavorabil = Caz mediu
Complexitate: constanta - θ(1)
*/
bool DO::vid() const { //este theta(1)
	/* de adaugat */
	return (Size == 0); 
}

/*
Caz favorabil = Caz defavorabil = Caz mediu
Complexitate: constanta - θ(1)
*/
Iterator DO::iterator() const { //este theta(1)
	return  Iterator(*this);
}

/*
Caz favorabil = Caz defavorabil = Caz mediu
Complexitate: constanta - θ(1)
*/
DO::~DO() { //este theta(1)
  if(this->Array != NULL)
  {
    delete[] Array;
  }
}

