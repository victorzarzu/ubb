#include <iostream>
#include <assert.h>
#include <vector>

using std::vector;
using std::pair;
using std::cout;
using std::make_pair;

class Solution {
  private:

  public:
    /*
      Metoda care returneaza elementul majoritar dintr-un vector
      @params: v - vectorul 
      @return: int - elementul majoritar
      @exceptii: "Vector gol!" daca vectorul este gol
      Complexitate timp: O(n)
      Complexitate spatiu: O(n)
    */
    static int solve(const vector<int>& v) {
      if(!v.size()) {
        throw("Vector gol!");
      }

      int count = 0, maj = v[0];

      for(const int& val : v) {
        if(val == maj) {
          count++;
        } else {
          count--;
        }

        if(count == 0) {
          maj = val;
          count = 1;
        }
      }

      return maj;
    }
};

int main() {
  
  vector<int> unu {2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2};
  vector<int> doi {6, 1, 3, 6, 2, 6, 6, 6, 2, 5, 0, 1, 6, 6, 6, 6};

  assert(Solution::solve(unu) == 2);
  assert(Solution::solve(doi) == 6);
  
  return 0;
}
