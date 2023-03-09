#include <iostream>
#include <assert.h>
#include <vector>
#include <set>

using std::vector;
using std::set;

class Solution {
  private:

  public:
    /*
      Metoda care returneaza al k-lea cel mai mare element al unui vector 
      @params: v - vectorul 
      @return: int - al k-lea cel mai mare element
      @exceptii: "k prea mare!" daca k >= n
      Complexitate timp: Caz favorabil => O(n + k * logk)
                         Caz defavorabil => O((n + k) * logk)
                         Caz mediu => O((n + k) * logk)
      Complexitate spatiu: O(n + k)
    */
    static int solve(const vector<int>& v, const int& k) {
      int n = v.size();

      if(n <= k) {
        throw("k prea mare!");
      }

      set<int> s;

      for(int i = 0;i < k;++i) {
        s.insert(v[i]);
      }

      for(int i = k;i < n;++i) {
        if(v[i] > *s.begin()) {
          s.erase(s.begin());
          s.insert(v[i]);
        }
      }

      return *s.begin();
    }
};

int main() {
  
  vector<int> unu {7, 4, 6, 3, 9, 1};
  vector<int> doi {6, 1, 2, 10, 8, 1, 234, 4, 1, 2, 6};

  assert(Solution::solve(unu, 2) == 7);
  assert(Solution::solve(doi, 4) == 6);
  
  return 0;
}
