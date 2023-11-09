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

void write_to_file(const int& val, char* filename) {
    ofstream g(filename);
    g<<val;
    g.close();
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int tag = 1, root = 0;
    int n;
    MPI_Status stat;
    int elements_per_process;

    if (rank == root) {
        if(argc != 3) {
            cout<<"Invalid number of arguments: <input_file>, <output_file>";
            MPI_Abort(MPI_COMM_WORLD, 1);
            return 0;
        }
        int *v = nullptr;
        read(n, v, argv[1]);
        auto start = std::chrono::high_resolution_clock::now();
        int* result = new int[n];
        elements_per_process = n / world_size;
        for (int i = 1; i < world_size; ++i) {
            int no_sent = elements_per_process;
            if (i == world_size - 1) {
                no_sent = n - i * elements_per_process;
            }
            MPI_Send(&no_sent, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
            MPI_Send(v + i * elements_per_process, no_sent, MPI_INT, i, tag, MPI_COMM_WORLD);
        }
        int local_sum = 0;
        for (int i = 0; i < elements_per_process; ++i) {
            local_sum += v[i];
        }

        int total_sum = local_sum, ext_sum;
        for(int i = 1;i < world_size;++i) {
            MPI_Recv(&ext_sum, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &stat);
            total_sum += ext_sum;
        }

        write_to_file(total_sum, argv[2]);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        cout << "Execution Time: " << duration.count() << " milliseconds" << '\n' << std::flush;

        delete[] v;
        delete[] result;
    } else {
        int count, sum = 0;
        MPI_Recv(&count, 1, MPI_INT, root, tag, MPI_COMM_WORLD, &stat);
        int* recv = new int[count];
        MPI_Recv(recv, count, MPI_INT, root, tag, MPI_COMM_WORLD, &stat);
        for (int i = 0; i < count; ++i) {
            sum += recv[i];
        }
        MPI_Send(&sum, 1, MPI_INT, root, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
