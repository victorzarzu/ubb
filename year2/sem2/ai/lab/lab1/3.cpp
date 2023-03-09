#include <iostream>
#include <vector>
#include <assert.h>

using std::vector;
using std::pair;
using std::make_pair;
using std::make_pair;

class Solution {
  private:

    /*
      Metoda care transforma un vector din reprezentare normala in reprezentare de tip pereche (pozitie, valoare)
      @params: v - vectorul
      @return: vector<pair<int, int>> vectorul in noua reprezentare
      Complexitate timp: O(n)
      Complexitate spatiu: O(n)
    */  
    static vector<pair<int, int>> to_rare(const vector<int>& v) {
      vector<pair<int, int>> result;

      for(int i = 0;i < v.size();++i) {
        if(v[i]) {
          result.push_back(make_pair(i, v[i]));
        }
      }

      return result;
    }

  public:
    /*
      Metoda care calculeaza produsul scalar a doi vectori rari
      @params: v1 - primul vector rar 
               v2 - al doilea vector rar
      @return: int - produsul scalar al vectorilor 
      @exceptii: "Lungime invalida!" daca cei doi vectori nu au aceeasi lungime
      Complexitate timp: O(n)
      Complexitate spatiu: O(n)
    */
    static int solve(const vector<int>& v1, const vector<int>& v2) {
      if(v1.size() - v2.size()) {
        throw("Lungime invalida!");
      }

      int result = 0;
      for(int i = 0;i < v1.size();++i) {
        result += v1[i] * v2[i];
      }

      return result;
    }

    static int solve_rare(const vector<pair<int, int>>& v1, const vector<pair<int, int>>& v2) {
      int result = 0;
      int i1 = 0, i2 = 0;

      while(i1 < v1.size() && i2 <v2.size()) {
        if(v1[i1].first == v2[i2].first) {
          result += v1[i1].second * v2[i2].second;
          i1++;
          i2++;
        } else if(v1[i1].first < v2[i2].first) {
          i1++;
        } else {
          i2++;
        }
      }
      
      return result;
    }

    static int solve1(const vector<int>& v1, const vector<int>& v2) {
      return solve_rare(to_rare(v1), to_rare(v2));
    }

};

int main() {
  
  vector<int> unu1 {1, 0, 2, 0, 3};
  vector<int> unu2 {1, 2, 0, 3, 1};

  assert(Solution::solve(unu1, unu2) == 4);
  assert(Solution::solve1(unu1, unu2) == 4);
  
  return 0;
}
