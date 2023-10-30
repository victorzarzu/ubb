#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <time.h>

using namespace std;

class MyBarrier {
public:
    MyBarrier(const int& count) : thread_count(count), counter(0), waiting(0) {}

    void wait() {
        std::unique_lock<std::mutex> lk(m);
        ++waiting;
        ++counter;
        cv.wait(lk, [&]{ return counter >= thread_count; });
        cv.notify_one();
        --waiting;
        if(!waiting) {
            counter = 0;
        }
        lk.unlock();
    }

private:
    std::mutex m;
    std::condition_variable cv;
    int counter;
    int waiting;
    int thread_count;
};

// Creeaza o matrice alocata dinamicayy cu n linii si m coloane
int** create_mat(const int& n, const int& m) {
    int** mat = new int*[n];
    for(int i = 0 ;i < n;++i) {
        mat[i] = new int[m];
    }
    return mat;
}

// Dealoca o matrice alocata dinamic cu n linii si m coloane
void delete_mat(const int& n, const int& m, int** mat) {
    for(int i = 0;i < n;++i) {
        delete[] mat[i];
    }
    delete[] mat;
}

// Citeste o matrice cu n linii si n coloane dintr-un stream dat
void read_mat(const int& n, const int& m, int** mat, ifstream& f) {
    for(int i = 0;i < n;++i) {
        for(int j = 0;j < m;++j) {
            f>>mat[i][j];
        }
    }
}

// Aplica operatia de convolutie pe matricea mat in locatia data de i si j cu matricea de convolutie conv_mat
int conv(const int& i, const int& j, const int& n_mat, const int& m_mat, const int& n_conv, const int& m_conv, int** mat, int** conv_mat, int** temp) {
    int sum = 0;
    for(int row = 0;row < n_conv;++row) {
        for(int column = j - (m_conv / 2);column <= j + (m_conv / 2);++column) {
            int conv_val = conv_mat[row][column - j + (m_conv / 2)];
            sum += temp[row][min(m_mat - 1, max(0, column))] * conv_val;
        }
    }

    return sum;
}

// Aplica operatia de convolutie intre liniile start_line si end_line inclusiv pe matricea mat, cu matricea de convolutie conv_mat si salveaza rezultatele in matricea result
void apply_conv_lines(const int& start_line, const int& end_line, const int& n_mat, const int& m_mat, const int& n_conv, const int& m_conv, MyBarrier* barrier, int** mat, int** conv_mat) {
    int* below = new int[m_mat];
    int** temp = create_mat(3, m_mat);

    memcpy(below, mat[min(n_mat - 1, end_line + 1)], sizeof(int) * m_mat);
    memcpy(temp[0], mat[max(0, start_line - 1)], sizeof(int) * m_mat);
    memcpy(temp[1], mat[start_line], sizeof(int) * m_mat);

    barrier->wait();

    for(int i = start_line;i <= end_line;++i) {
        if(i == end_line) {
            memcpy(temp[2], below, sizeof(int) * m_mat);
        } else {
            memcpy(temp[2], mat[i + 1], sizeof(int) * m_mat);
        }
        for(int j = 0;j < m_mat;++j) {
            mat[i][j] = conv(i, j, n_mat, m_mat, n_conv, m_conv, mat, conv_mat, temp);
        }
        memcpy(temp[0], temp[1], sizeof(int) * m_mat);
        memcpy(temp[1], temp[2], sizeof(int) * m_mat);
    }
}

// Aplica operatia de convolutie pe intreaga matrice mat, avang matricea de convolutie conv_mat, impartind coloanele matricei thread-urilor
void apply_conv(const int& n_mat, const int& m_mat, const int& n_conv, const int& m_conv, const int& no_threads, int** mat, int** conv_mat) {
    vector<thread> threads;
    MyBarrier* barrier = new MyBarrier(no_threads);
    
    if(n_mat >= no_threads) {
        int lines_per_thread = n_mat / no_threads;
        for(int i = 0;i < no_threads;++i) {
            int start_line = i * lines_per_thread;
            int end_line = (i + 1) * lines_per_thread - 1;
            if(i == no_threads - 1) {
                end_line = n_mat - 1;
            }
            threads.push_back(thread(apply_conv_lines, start_line, end_line, n_mat, m_mat, n_conv, m_conv, barrier, mat, conv_mat));
        }
    } else {
        for(int i = 1;i <= n_mat;++i) {
            threads.push_back(thread(apply_conv_lines, i, i, n_mat, m_mat, n_conv, m_conv, barrier, mat, conv_mat));
        }
    }

    for(auto& thread : threads) {
        thread.join();
    }
    delete barrier;
}

// Printeaza matricea mat in fisierul dat de variabila filename
void print_mat(const int& n, const int& m, int** mat, const char* filename) {
    ofstream output(filename);

    output<<n<<" "<<m<<'\n';
    for(int i = 0;i < n;++i, output<<'\n') {
        for(int j = 0;j < m;++j) {
            output<<mat[i][j]<<" ";
        }
    }
    output.close() ;
}

int main(int argc, char* argv[]) {
    if(argc != 5) {
        cout<<"Incorect call: <input_file> <conv_mat_file> <output_file> <no_threads>\n";
        return 0;
    }

    ifstream input_mat(argv[1]);
    ifstream input_conv(argv[2]);
    int no_threads = stoi(argv[4]);

    int n_mat, m_mat, n_conv, m_conv;
    input_mat>>n_mat>>m_mat;
    input_conv>>n_conv>>m_conv;
    int** mat = create_mat(n_mat, m_mat);
    int** conv_mat = create_mat(n_conv, m_conv);

    read_mat(n_mat, m_mat, mat, input_mat);
    read_mat(n_conv, n_conv, conv_mat, input_conv);
    input_mat.close();
    input_conv.close();


    std::clock_t start = std::clock();
    apply_conv(n_mat, m_mat, n_conv, m_conv, no_threads, mat, conv_mat);
    cout<<(std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);

    print_mat(n_mat, m_mat, mat, argv[3]);

    delete_mat(n_mat, m_mat, mat);
    delete_mat(n_conv, m_conv, conv_mat);

    return 0;
}