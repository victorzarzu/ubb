#include <iostream>
#include <vector>
#include <assert.h>

using std::vector;

class Solution {
  private:

    /*
      Metoda care returneaza indicele primului 1 pana la valoarea one_start din vectorul row
      @params: m - numarul de elemente din vector
               one_start - indicele maxim din spatiul de cautare
               row - vectorul in care se cauta primul 1
      @return: int - indicele unde se afla primul 1 in intervalul [1, one_start] daca exista un 1 in acest interval si m altfel
      Complexitate timp: O(logm)
      Complexitate spatiu: O(m)
    */
    static int find_first_one(int m, int one_start, const vector<bool>& row) {
      int left = 0, right = one_start - 1, mid, response = m;

      while(left <= right) {
        mid = left + ((right - left) >> 1);

        if(row[mid]) {
          response = mid;
          right = mid - 1;
        } else {
          left = mid + 1;
        }
      }

      return response;
    }

  public:
    
    /*
      Metoda care returneaza numarul liniei cu cei mai multi 1 dintr-o matrice
      @params: n - numarul de randuri din matrice
               m - numarul de coloane din matrice
               matrix - matricea
      @return: int - numarul liniei care contine cele mai multe elemente de 1 sau -1 daca matricea nu are randuri
      Complexi
      Complexitate timp: Caz favorabil: O(logm)
                         Caz defavorabil: O(n * logm)
                         Caz mediu: O(n * logm)
      Complexitate spatiu: O(n * m)
    */
    static int solve(int n, int m, const vector<vector<bool> >& matrix) {
      int response = -1;
      int one_start = m;

      for(int i = 0;i < n;++i) {
        if(one_start < m && !matrix[i][one_start]) {
          continue; 
        }
        if(one_start == 0) {
          break;
        }
      
        int one = find_first_one(m, one_start, matrix[i]);

        if(one < one_start) {
          one_start = one;
          response = i;
        }
      }

      return response + 1;
    }
};

int main() {
  
  vector<vector<bool> > unu {{0, 0, 0, 1, 1},
                              {0, 0, 0, 1, 1},
                              {0, 0, 0, 0, 1},
                              {0, 0, 1, 1, 1},
                              {0, 0, 0, 1, 1}};

  vector<vector<bool> > doi {{0, 1, 1, 1, 1},
                              {1, 1, 1, 1, 1},
                              {0, 0, 0, 0, 1},
                              {0, 0, 1, 1, 1},
                              {0, 0, 0, 1, 1}};

  vector<vector<bool> > trei {{0, 1, 1, 1},
                              {0, 0, 1, 1},
                              {0, 1, 1, 1},
                              {0, 0, 1, 1},
                              {0, 0, 0, 1}};

  vector<vector<bool> > patru {{0, 0, 0, 0, 1, 1, 1},
                              {0, 0, 0, 0, 0, 1, 1},
                              {0, 0, 0, 0, 0, 1, 1},
                              {0, 0, 1, 1, 1, 1, 1},
                              {0, 1, 1, 1, 1, 1, 1},
                              {0, 0, 0, 1, 1, 1, 1}};

  assert(Solution::solve(5, 5, unu) == 4);
  assert(Solution::solve(5, 5, doi) == 2);
  assert(Solution::solve(5, 4, trei) == 1);
  assert(Solution::solve(6, 7, patru) == 5);

  return 0;
}
