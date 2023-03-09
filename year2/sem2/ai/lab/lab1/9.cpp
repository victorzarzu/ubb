#include <iostream>
#include <vector>
#include <assert.h>

using std::vector;
using std::pair;
using std::cout;

#define point pair<int, int>
#define x first
#define y second


class Solution {
  private:

    /*
      Metoda care returneaza suma elementelor din submatricea determinata de punctele date
      @params: point1 - primul punct 
               point2 - al doilea punct
               matrix - al doilea punct
      @return: int - diferenta valorilor din matricea de la coordonatele specificate
      @exceptii: "Coordonate invalide!" daca punctele nu se afla in matrice
      Complexitate timp: O(1)
      Complexitate spatiu: O(1)
    */
    static int get_sum(const point& point1, const point& point2, const vector<vector<int> >& matrix) {
        int n = matrix.size();
        if(point1.x < 0 || point1.x > n) {
          throw("Coordonate invalide!");
        } else if(point1.y < 0 || point1.y > matrix[point1.x].size()) {
          throw("Coordonate invalide!");
        }

        if(point2.x < 0 || point2.x > n) {
          throw("Coordonate invalide!");
        } else if(point2.y < 0 || point2.y > matrix[point2.x].size()) {
          throw("Coordonate invalide!");
        }

        return matrix[point2.x + 1][point2.y + 1] - matrix[point1.x][point2.y + 1] - matrix[point2.x + 1][point1.y] + matrix[point1.x][point1.y];
     }

  public:
    
    /*
      Metoda care returneaza diferenta sumelor din submatricelor specificate din matrice
      @params: matrix - matricea 
               points - lista cu perechi de puncte
      @return: int - numarul liniei care contine cele mai multe elemente de 1 sau -1 daca matricea nu are randuri
      Complexitate timp: O(n * m)
      Complexitate spatiu: O(n * m + p)
    */
    static vector<int> solve(int n, int m, vector<vector<int> > matrix, const vector<pair<point, point> >& points) {
      vector<vector<int> > matrix1(n + 1);

      for(int i = 0;i <= n;++i) {
        matrix1[i].resize(m + 1);
      }

      for(int i = 2;i <= n;++i) {
        matrix1[i][1] = matrix[i - 1][0] + matrix1[i - 1][1]; 
      }

      for(int i = 2;i <= m;++i) {
        matrix1[1][i] = matrix[0][i - 1] + matrix1[1][i - 1]; 
      }

      for(int i = 2;i <= n;++i) {
        for(int j = 2;j <= m;++j) {
          matrix1[i][j] = matrix[i - 1][j - 1] + matrix1[i - 1][j] + matrix1[i][j - 1] - matrix1[i - 1][j - 1];
        }
      }

      vector<int> result; 

      for(const auto& p : points) {
        result.push_back(get_sum(p.first, p.second, matrix1));
      }

      return result;
    }
};

int main() {
  
  vector<vector<int> > unu {{0, 2, 5, 4, 1},
                              {4, 8, 2, 3, 7},
                              {6, 3, 4, 6, 2},
                              {7, 3, 1, 8, 3},
                              {1, 5, 7, 9, 4}};
  vector<pair<point, point>> points_unu {{{1, 1}, {3, 3}}, {{2, 2}, {4, 4}}};
  vector<int> true_unu {38, 44};


  vector<int> result_unu = Solution::solve(5, 5, unu, points_unu);
  for(int i = 0;i < true_unu.size();++i) {
    assert(true_unu[i] == result_unu[i]);
  }

  return 0;
}
