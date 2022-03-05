#include "Iterator.h"
#include "DO.h"
#include <iostream>

using namespace std;

Iterator::Iterator(const DO& d) : dict(d){
  position = 0;
}

void Iterator::prim(){
  position = 0;
}

void Iterator::urmator(){
  position = position + 1;
}

bool Iterator::valid() const{
  return (position < dict.Size);
}

TElem Iterator::element() const{
  return dict.Array[position];
}


