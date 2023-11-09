#include <iostream>
#include <mpi.h>
#include <fstream>

using namespace std;

void read(int& n, int*& v1, int*& v2, char* filename) {
    ifstream f(filename);
    f >> n;
    v1 = new int[n];
    v2 = new int[n];
    for (int i = 0; i < n; ++i) {
        f >> v1[i];
    }
    for (int i = 0; i < n; ++i) {
        f >> v2[i];
    }
    f.close();
}

void write_to_file(const int& n, int* v, char* filename) {
    ofstream g(filename);
    for(int i = 0;i < n;++i) {
        g<<v[i]<<" ";
    }
    g.close();
}

void compute_sum(const int* v1, const int* v2, int* sum, const int& n)  {
    for(int i = 0;i < n;++i) {
        sum[i] = v1[i] + v2[i];
    }
}

int main(int argc, char** argv) {
    if(argc != 3) {
        cout<<"Invalid number of arguments: <input_file>, <output_file>";
        return 0;
    }
    int *v1 = nullptr, *v2 = nullptr, n;
    read(n, v1, v2, argv[1]);
    int *sum = new int[n];

    auto start = std::chrono::high_resolution_clock::now();
    compute_sum(v1, v2, sum, n);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Execution Time: " << duration.count() << " milliseconds" << '\n' << std::flush;

    write_to_file(n, sum, argv[2]);

    delete[] v1;
    delete[] v2;
    delete[] sum;


    return 0;
}
