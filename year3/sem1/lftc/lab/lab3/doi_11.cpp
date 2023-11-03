#include <iostream>

using namespace std;

int main() {
  float raza,perimetru,arie,pi;
  pi = 3.14;
  cin>> raza;
  perimetru = 2 * pi * raza;
  arie = pi * raza * raza;
  cout<< perimetru;
  cout<<"\n";
  cout<< arie;

  return 0;
}
