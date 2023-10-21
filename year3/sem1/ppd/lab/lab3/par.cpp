#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <functional>

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

void run_secv(int* a, int* b, int* c, const int& start, const int& end, function<int(const int&, const int&)> f) {
  for(int i = start;i <= end;++i) {
    c[i] = f(a[i], b[i]);
  } 
}

void run_cycl(int *a, int* b, int* c, const int& start, const int& end, const int& step, function<int(const int&, const int&)> f) {
  for(int i = start;i <= end;i += step) {
    c[i] = f(a[i], b[i]);
  }
}

int main(int argc, char* argv[]) {
  if(argc != 4) {
    cout<<"Incorect call: <input_file> <output_file> <no_threads>\n";
    return 0;
  }
  ifstream f(argv[1]);

  int n, no_threads = stoi(argv[3]);
  f>>n;
  int *a = new int[n], *b = new int[n], *c = new int[n];

  for(int i = 0;i < n;++i) {
    f>>a[i];
  }
  for(int i = 0;i < n;++i) {
    f>>b[i];
  }
  f.close();

  int chunk_size = n / no_threads;
  vector<thread> threads;
  for(int i = 0;i < no_threads;++i) {
    int start = i * chunk_size;
    int end = (i == no_threads - 1 ? n : (i + 1) * chunk_size) - 1;
    threads.push_back(thread(run_secv, a, b, c, start, end, op));
    //threads.push_back(thread(run_cycl, a, b, c, i, n, no_threads, op));
  }

  for(auto& thread : threads) {
    thread.join();
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
