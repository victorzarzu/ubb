#include <iostream>
#include <fstream>

using namespace std;

int** create_mat(const int& n, const int& m) {
    int** mat = new int*[n + 1];
    for(int i = 0 ;i <= n;++i) {
        mat[i] = new int[m + 1];
    }
    return mat;
}

void delete_mat(const int& n, const int& m, int** mat) {
    for(int i = 0;i < n;++i) {
        delete[] mat[i];
    }
    delete[] mat;
}

void read_mat(const int& n, const int& m, int** mat, ifstream& f) {
    for(int i = 1;i <= n;++i) {
        for(int j = 1;j <= m;++j) {
            f>>mat[i][j];
        }
    }
}

int conv(const int& i, const int& j, const int& n_mat, const int& m_mat, const int& n_conv, const int& m_conv, int** mat, int** conv_mat) {
    int sum = 0;
    for(int row = i - (n_conv / 2);row <= i + (n_conv / 2);++row) {
        for(int column = j - (m_conv / 2);column <= j + (m_conv / 2);++column) {
            sum += mat[min(n_mat, max(1, row))][min(m_mat, max(1, column))] * conv_mat[row - i + (n_conv / 2) + 1][column - j + (m_conv / 2) + 1];
        }
    }

    return sum;
}

void apply_conv(const int& n_mat, const int& m_mat, const int& n_conv, const int& m_conv, int** mat, int** conv_mat, int** result) {
    for(int i = 1;i <= n_mat;++i) {
        for(int j = 1;j <= m_mat;++j) {
            result[i][j] = conv(i, j, n_mat, m_mat, n_conv, m_conv, mat, conv_mat);
            cout<<result[i][j]<<'\n';
        }
    }
}

void print_mat(const int& n, const int& m, int** mat, const char* filename) {
    ofstream output(filename);

    output<<n<<" "<<m<<'\n';
    for(int i = 1;i <= n;++i, output<<'\n') {
        for(int j = 1;j <= m;++j) {
            output<<mat[i][j]<<" ";
        }
    }
    output.close() ;
}

int main(int argc, char* argv[]) {
    if(argc != 4) {
        cout<<"Incorect call: <input_file> <conv_mat_file> <output_file>\n";
        return 0;
    }

    ifstream input_mat(argv[1]);
    ifstream input_conv(argv[2]);

    int n_mat, m_mat, n_conv, m_conv;
    input_mat>>n_mat>>m_mat;
    input_conv>>n_conv>>m_conv;
    int** mat = create_mat(n_mat + 1, m_mat + 1);
    int** conv_mat = create_mat(n_conv + 1, m_conv + 1);
    int** result_mat = create_mat(n_mat + 1, m_mat + 1);

    read_mat(n_mat, m_mat, mat, input_mat);
    read_mat(n_conv, m_conv, conv_mat, input_conv);
    input_mat.close();
    input_conv.close();

    apply_conv(n_mat, m_mat, n_conv, m_conv, mat, conv_mat, result_mat);
    print_mat(n_mat, m_mat, result_mat, argv[3]);

    delete_mat(n_mat + 1, m_mat + 1, mat);
    delete_mat(n_conv + 1, m_conv + 1, conv_mat);
    delete_mat(n_mat + 1, m_mat + 1, result_mat);

    return 0;
}