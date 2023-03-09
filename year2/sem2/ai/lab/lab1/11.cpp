#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>

using std::vector;
using std::stack;
using std::pair;
using std::make_pair;
using std::cout;

#define point pair<int, int>
#define x first
#define y second

class Solution {
  private:
    static constexpr int x_dir[] = {0, 0, -1, 1};
    static constexpr int y_dir[] = {1, -1, 0, 0};

    /*
      Metoda care verifica daca coordonatele sunt in matrice si se afla un zero acolo
      @params: n - numarul de randuri din matrice
               m - numarul de coloane din matrice
               x - numarul randului
               y - numarul coloanei
               matrix - matricea
      @return: bool - true daca coornonatele se afla in interiorul matricei si false altfel
      Complexitate timp: O(1)
      Complexitate spatiu: O(1)
    */
    static bool is_zero_inside(const int& n, const int& m, const int& x, const int& y, int** matrix) {
      return x >= 0 && x < n && y >= 0 && y < m && matrix[x][y] == 0; 
    }

  public:
    
    /*
      Metoda care inlocuieste toate aparitiile de 0 dintr-o matrice care nu sunt inconjurate complet de 1 cu -1
      @params: n - numarul de randuri din matricei
               m - numarul de coloane din matrice
               matrix - matricea
      @return: -
      Complexitate timp: Caz favorabil => O(1)
                         Caz defavorabil => O(n * m)
                         Caz mediu => O(n * m)
      Complexitate spatiu: O(n * m)
    */  
    static void fill(const int& n, const int& m, int** matrix) {
      stack<point> s; 

      for(int i = 0;i < n;i += n - 1) {
        for(int j = 0;j < m;++j) {
          if(!matrix[i][j]) {
            s.push(make_pair(i, j));
          }
        }
      }

      for(int j = 0;j < m;j += m - 1) {
        for(int i = 1;i < n - 1;++i) {
          if(!matrix[i][j]) {
            s.push(make_pair(i, j));
          }
        }
      }

      while(!s.empty()) {
        point p = s.top();
        s.pop();

        matrix[p.x][p.y] = -1;

        for(int i = 0;i < 4;++i) {
          int x_new = p.x + x_dir[i];
          int y_new = p.y + y_dir[i];

          if(is_zero_inside(n, m, x_new, y_new, matrix)) {
            s.push(make_pair(x_new, y_new));
          }
        }
      }
    }

    /*
      Metoda care inlocuieste toate aparitiile de 0 dintr-o matrice care nu sunt inconjurate complet de 1 cu 1
      @params: n - numarul de randuri din matricei
               m - numarul de coloane din matrice
               matrix - matricea
      @return: -
      Complexitate timp: O(n * m)
      Complexitate spatiu: O(n * m)
    */  
    static void solve(int n, int m, int** matrix) {
      fill(n, m, matrix);

      for(int i = 0;i < n;++i) {
        for(int j = 0;j < m;++j) {
          matrix[i][j] = matrix[i][j] == -1 ? 0 : 1;
        }
      }
    }
};

int main() {
  
  int **unu = new int*[8];
  for(int i = 0;i < 8;++i) {
    unu[i] = new int[10];
  }

  int unu_m[8][10] = {{1,1,1,1,0,0,1,1,0,1},
       {1,0,0,1,1,0,1,1,1,1},
       {1,0,0,1,1,1,1,1,1,1},
       {1,1,1,1,0,0,1,1,0,1},
       {1,0,0,1,1,0,1,1,0,0},
       {1,1,0,1,1,0,0,1,0,1},
       {1,1,1,0,1,0,1,0,0,1},
       {1,1,1,0,1,1,1,1,1,1}};

  for(int i = 0;i < 8;++i) {
    for(int j = 0;j < 10;++j) {
      unu[i][j] = unu_m[i][j];
    }
  }


    int sol_unu[8][10] = {{1,1,1,1,0,0,1,1,0,1},
        {1,1,1,1,1,0,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,0,1},
        {1,1,1,1,1,1,1,1,0,0},
        {1,1,1,1,1,1,1,1,0,1},
        {1,1,1,0,1,1,1,0,0,1},
        {1,1,1,0,1,1,1,1,1,1}};
  Solution::solve(8, 10, unu);

  for(int i = 0;i < 8;++i) {
    for(int j = 0;j < 10;++j) {
      assert(unu[i][j] == sol_unu[i][j]);
    }
  }

  for(int i = 0;i < 8;++i) {
    delete[] unu[i];
  }
  delete[] unu;

  return 0;
}
