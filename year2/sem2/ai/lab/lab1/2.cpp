#include <iostream>
#include <assert.h>

using std::vector;
using std::pair;
using std::cout;
using std::make_pair;

#define point pair<int, int>
#define x first
#define y second
#define epsilon 1e-3

class Solution {

  public:
    /*
      Metoda care calculeaza radicalul unui numar 
      @params: x - numarul caruia i se extrace radicalul 
      @return: float - valorea radicalului numarului 
      Complexitate timp: O(1)
      Complexitate spatiu: O(1)
    */
    static float fast_sqrt(const float x) {
      union {
        int i;
        float x;
      } u;

      u.x = x;
      u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

      u.x = u.x + x / u.x;
      u.x = 0.25f * u.x + x / u.x;

      return u.x;
    }

    /*
      Metoda care calculeaza distanta euclidiana dintre 2 puncte
      @params: point1 - primul punct
               point2 - al doilea punct
      @return: int - distanta dintre cele 2 puncte 
      Complexitate timp: O(1)
      Complexitate spatiu: O(1)
    */
    static float solve(const point& point1, const point& point2) {

      return fast_sqrt((point2.x - point1.x) * (point2.x - point1.x) +  (point2.y - point1.y) * (point2.y - point1.y));
    }
};

int main() {
  
  assert(Solution::solve(make_pair(1, 5), make_pair(4, 1)) - 5.0 < epsilon);
  assert(Solution::solve(make_pair(15, 4), make_pair(3, 11)) - 13.89244 < epsilon);

  std::cout<<Solution::fast_sqrt(169);
  
  return 0;
}
