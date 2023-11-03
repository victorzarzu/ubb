#include <iostream>

using namespace std;

int main() {
  int x,y;

  cin >> x;
  cin >> y;

  if(x % y) { // in MLP conditia nu este implicita
    cout << "Da";
  } else { // in MLP nu exista else la conditionala
    cout << "Nu"; 
  }

  return 0;
}
