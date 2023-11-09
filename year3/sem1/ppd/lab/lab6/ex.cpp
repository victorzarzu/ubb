#include <iostream>
#include <mpi.h>
#include <fstream>

using namespace std;

void read(int& n, int*& v, char* filename) {
    ifstream f(filename);
    f >> n;
    v = new int[n];
    for (int i = 0; i < n; ++i) {
        f >> v[i];
    }
    f.close();
}

int compute_sum(const int& n, const int* v) {
    int sum = 0;
    for(int i = 0;i < n;++i) {
        sum += v[i];
    }
    return sum;
}

void write_to_file(const int& val, char* filename) {
    ofstream g(filename);
    g<<val;
    g.close();
}

int main(int argc, char** argv) {
    if(argc != 3) {
        cout<<"Invalid number of arguments: <input_file>, <output_file>";
        return 0;
    }
    int *v = nullptr, n;
    read(n, v, argv[1]);

    auto start = std::chrono::high_resolution_clock::now();
    int sum = compute_sum(n, v);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Execution Time: " << duration.count() << " milliseconds" << '\n' << std::flush;
    
    write_to_file(sum, argv[2]);
    delete[] v;

    return 0;
}
