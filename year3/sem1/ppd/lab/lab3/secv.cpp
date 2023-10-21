#include <iostream>
#include <fstream>

using namespace std;
#define mod 666013

int op(const int& x, const int& y) {
  int result = 1;
  for(int i = 1;i <= y;++i) {
    result = ((long)result * x) % mod;
  }
  return result;
  //return x + y;
}

int main(int argc, char* argv[]) {
  if(argc != 3) {
    cout<<"Incorect call: <input_file> <output_file>\n";
    return 0;
  }
  ifstream f(argv[1]);

  int n;
  f>>n;
  int *a = new int[n], *b = new int[n], *c = new int[n];

  for(int i = 0;i < n;++i) {
    f>>a[i];
  }
  for(int i = 0;i < n;++i) {
    f>>b[i];
  }
  f.close();

  for(int i = 0;i < n;++i) {
    c[i] = op(a[i], b[i]);
  }
  delete[] a;
  delete[] b;

  ofstream g(argv[2]);
  for(int i = 0;i < n;++i) {
    g<<c[i]<<" ";
  }
  g.close();
  delete[] c;

  return 0;
}
