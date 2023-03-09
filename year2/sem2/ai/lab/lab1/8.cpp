#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <assert.h>

using std::vector;
using std::queue;
using std::string;

class Solution {
  public:
    /*
      Metoda care intoarce reprezantarea binara a numerelor de la 1 la n
      @params: n - limita superioara a intervalului
      @return: vector<string> - reprezentarile binare ale numerelor 
      @exceptii: "Valoare incorecta!" daca n < 1
      Complexitate timp: O(n)
      Complexitate spatiu: O(n)
    */
    static vector<string> solve(int n) {
      if(n < 1) {
        throw("Valoare incorecta!");
      }

      vector<string> result;
      queue<string> q;
      q.push("1");

      while(n--) {
        string front = q.front();
        q.pop();

        result.push_back(front);

        string one = front;
        front.push_back('0');
        one.push_back('1');

        q.push(front);
        q.push(one);
      }

      return result;
    }
};

int main() {
  
  vector<string> unu {"1", "10", "11", "100"};
  vector<string> doi {"1"};

  vector<string> res_unu = Solution::solve(4);

  assert(res_unu.size() == 4);
  for(int i = 0;i < 4;++i) {
    assert(unu[i] == res_unu[i]);
  }

  vector<string> res_doi = Solution::solve(1);

  assert(res_doi.size() == 1);
  for(int i = 0;i < 1;++i) {
    assert(doi[i] == res_doi[i]);
  }
  
  return 0;
}
