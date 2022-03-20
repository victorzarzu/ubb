#include "Iterator.h"
#include "DO.h"
#include <iostream>

using namespace std;

/*
Caz favorabil = Caz defavorabil = Caz mediu
Complexitate: constanta - θ(1)
*/
Iterator::Iterator(const DO& d) : dict{d}, position{0}{ //este theta(1)
  //position = 0;
}

/*
Caz favorabil = Caz defavorabil = Caz mediu
Complexitate: constanta - θ(1)
*/
void Iterator::prim(){ 
  position = 0;
}

/*
Caz favorabil = Caz defavorabil = Caz mediu
Complexitate: constanta - θ(1)
*/
void Iterator::urmator(){ 
  if(!valid())
  {
    throw exception();
  }
  position = position + 1;
}

/*
Caz favorabil = Caz defavorabil = Caz mediu
Complexitate: constanta - θ(1)
*/
bool Iterator::valid() const{ 
  return (position < dict.Size);
}

/*
Caz favorabil = Caz defavorabil = Caz mediu
Complexitate: constanta - θ(1)
*/
TElem Iterator::element() const{   
  if(!valid())
  {
    throw exception();
  }

  return dict.Array[position];
}

