#include <iostream>

using namespace std;

int main() {
  int 0x; // nu are voia sa fie cifra ca prim caracter al unui ID
  int y;

  cin >> 0x;

  if(0x > 0) {
    cin >> y;
    cout << 2 ** y; // nu exista operatorul **
  }

  return 0;
}
