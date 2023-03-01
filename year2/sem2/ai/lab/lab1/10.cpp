#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::cout;

class Solution {
  private:
    int n, m;
    bool **matrix;

    int find_first_one(int m, int one_start, bool* row) {
      int left = 1, right = one_start - 1, mid, response = m + 1;

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
    
    Solution(string filename) {
      ifstream f(filename);
      
      f>>n>>m;

      matrix = new bool*[n];
      for(int i = 0;i < n;++i) {
        matrix[i] = new bool[m + 1];
      }

      for(int i = 0;i < n;++i) {
        for(int j = 1;j <= m;++j) {
          f>>matrix[i][j];
        }
      }

      f.close();
    }

    int solve() {
      int response = -1;
      int one_start = m + 1;

      for(int i = 0;i < n;++i) {
        if(one_start <= m && !matrix[i][one_start]) {
          continue; 
        }
      
        int one = find_first_one(m, one_start, matrix[i]);

        if(one < one_start) {
          one_start = one;
          response = i;
        }

      }

      return response + 1;
    }

    ~Solution() {
      for(int i = 0;i < n;++i) {
        delete[] matrix[i];
      }
      delete[] matrix;
    }
};

int main() {
  
  Solution sol("10.in");
  cout<<sol.solve();

  return 0;
}
