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
        int *v1 = nullptr, *v2 = nullptr;
        read(n, v1, v2, argv[1]);
        auto start = std::chrono::high_resolution_clock::now();
        int* result = new int[n];
        elements_per_process = n / world_size;
        for (int i = 1; i < world_size; ++i) {
            int no_sent = elements_per_process;
            if (i == world_size - 1) {
                no_sent = n - i * elements_per_process;
            }
            MPI_Send(&no_sent, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
            MPI_Send(v1 + i * elements_per_process, no_sent, MPI_INT, i, tag, MPI_COMM_WORLD);
            MPI_Send(v2 + i * elements_per_process, no_sent, MPI_INT, i, tag, MPI_COMM_WORLD);
        }
        int local_sum = 0;
        for (int i = 0; i < elements_per_process; ++i) {
            result[i] = v1[i] + v2[i];
        }

        int receive_index = elements_per_process;
        for(int i = 1;i < world_size;++i) {
            int no_received = elements_per_process;
            if (i == world_size - 1) {
                no_received = n - i * elements_per_process;
            }
            MPI_Recv(result + receive_index, no_received, MPI_INT, i, tag, MPI_COMM_WORLD, &stat);
            receive_index += no_received;
        }    
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        cout << "Execution Time: " << duration.count() << " milliseconds" << '\n' << std::flush;

        write_to_file(n, result, argv[2]);


        delete[] v1;
        delete[] v2;
        delete[] result;
    } else {
        int count, sum = 0;
        MPI_Recv(&count, 1, MPI_INT, root, tag, MPI_COMM_WORLD, &stat);
        int *v1 = new int[count], *v2 = new int[count], *result = new int[count];
        MPI_Recv(v1, count, MPI_INT, root, tag, MPI_COMM_WORLD, &stat);
        MPI_Recv(v2, count, MPI_INT, root, tag, MPI_COMM_WORLD, &stat);
        for (int i = 0; i < count; ++i) {
            result[i] = v1[i] + v2[i];
        }
        MPI_Send(result, count, MPI_INT, root, tag, MPI_COMM_WORLD);

        delete[] v1;
        delete[] v2;
        delete[] result;
    }

    MPI_Finalize();

    return 0;
}
