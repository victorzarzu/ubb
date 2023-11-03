#include <iostream>

using namespace std;

int main() {
  int n,x,suma ;
  suma = 0 ;
  cin>> n ;

  while( n > 0 ) {
    cin>> x ;
    suma = suma + x ;
    n = n - 1 ;
  }

  cout<< suma ;

  return 0 ;
}
