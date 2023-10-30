#include <iostream>
#include <fstream>

using namespace std;

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

int get_mat_value(const int& i, const int& j, const int& row, const int& column, const int& n_mat, const int& m_mat, int** mat, int **temp) {
    if(row < i) {
        return temp[0][min(m_mat - 1, max(0, column))];
    } 
    if(row == i && column < j) {
        return temp[1][min(m_mat - 1, max(0, column))];
    }
    if(row > n_mat - 1 && column < j) {
        return temp[1][min(m_mat - 1, max(0, column))];
    }
    return mat[min(n_mat - 1, max(0, row))][min(m_mat - 1, max(0, column))];
}

// Aplica operatia de convolutie pe matricea mat in locatia data de i si j cu matricea de convolutie conv_mat
int conv(const int& i, const int& j, const int& n_mat, const int& m_mat, const int& n_conv, const int& m_conv, int** mat, int** conv_mat, int **temp) {
    int sum = 0;
    for(int row = i - (n_conv / 2);row <= i + (n_conv / 2);++row) {
        for(int column = j - (m_conv / 2);column <= j + (m_conv / 2);++column) {
            int conv_val = conv_mat[row - i + (n_conv / 2)][column - j + (m_conv / 2)];
            int mat_val = get_mat_value(i, j, row, column, n_mat, m_mat, mat, temp);
            sum += mat_val * conv_val;
        }
    }

    return sum;
}

// Aplica operatia de convolutia pe intreaga matrice mat
void apply_conv(const int& n_mat, const int& m_mat, const int& n_conv, const int& m_conv, int** mat, int** conv_mat, int** temp) {
    for(int i = 0;i < n_mat;++i) {
        for(int j = 0;j < m_mat;++j) {
            temp[1][j] = mat[i][j];
            mat[i][j] = conv(i, j, n_mat, m_mat, n_conv, m_conv, mat, conv_mat, temp);
        }
        memcpy(temp[0], temp[1], sizeof(int) * m_mat);
    }
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
    if(argc != 4) {
        cout<<"Incorect call: <input_file> <conv_mat_file> <output_file>\n";
        return 0;
    }

    ifstream input_mat(argv[1]);
    ifstream input_conv(argv[2]);

    int n_mat, m_mat, n_conv, m_conv;
    input_mat>>n_mat>>m_mat;
    input_conv>>n_conv>>m_conv;
    int** mat = create_mat(n_mat, m_mat);
    int** conv_mat = create_mat(n_conv, m_conv);
    int** temp = create_mat(2, m_mat);

    read_mat(n_mat, m_mat, mat, input_mat);
    read_mat(n_conv, m_conv, conv_mat, input_conv);
    input_mat.close();
    input_conv.close();

    memcpy(temp[0], mat[0], sizeof(int) * m_mat);

    std::clock_t start = std::clock();
    apply_conv(n_mat, m_mat, n_conv, m_conv, mat, conv_mat, temp);
    cout<<long((std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000))<<'\n';

    print_mat(n_mat, m_mat, mat, argv[3]);

    delete_mat(n_mat, m_mat, mat);
    delete_mat(n_conv, m_conv, conv_mat);
    delete_mat(2, m_mat, temp);

    return 0;
}