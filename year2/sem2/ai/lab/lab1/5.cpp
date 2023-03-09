#include <iostream>
#include <vector>
#include <assert.h>

using std::vector;
using std::pair;
using std::cout;

class Solution {
  public:
    
    /*
      Metoda care returneaza valoare duplicata din vectorul dat (stiind ca una singura este duplicate iar ca valorile sunt din {1, 2, ..., n - 1}
      @params: v - vectorul cu numere 
      @return: int - valoarea care se repeta 
      Complexitate timp: O(n)
      Complexitate spatiu: O(n)
    */
    static int solve(const vector<int>& v) {
      int sum = 0, n = v.size();
      for(const int& val : v) {
        sum += val;
      }

      return sum - n * (n - 1) / 2;
    }
};

int main() {
  vector<int> unu {1, 2, 3, 4, 2};
  vector<int> doi {1, 2, 3, 4, 7, 5, 6, 7};

  assert(Solution::solve(unu) == 2);
  assert(Solution::solve(doi) == 7);

  return 0;
}
