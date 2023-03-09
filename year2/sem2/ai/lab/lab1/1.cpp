#include <iostream>
#include <string>
#include <assert.h>

using std::string;
using std::cout;

class Solution {
  private:

  public:

    /*
      Metoda care retuneaza ultimul cuvant dintr-un text
      @params: sentence - textul din care se returneaza cuvantul maxim
      @return: string - cuvantul cautat
      @exceptii: "Propozitie invalida!" daca textul contine si altceva in afara de litere si spatii
      Complexitate timp: O(n)
      Complexitate spatiu: O(n + m), m - lungimea celui mai mare cuvant
    */
    static string solve(string sentence) {
      sentence.push_back(' ');

      string result = "", current_word = "";
      bool bigger = false, alph_equal = true;
      int word_start = 0;

      for(int i = 0;i < sentence.size();++i) {

        if(sentence[i] == ' ') {
          if(bigger) {
            result = current_word;
          }
          
          bigger = false;
          alph_equal = true;
          current_word = "";
          continue;
        } else if(!isalpha(sentence[i])) {
          throw("Propozitie invalida!");
        }
        if(!current_word.size()) {
          word_start = i;
        }

        current_word.push_back(sentence[i]);
        if(alph_equal && current_word.size() > result.size()) {
          bigger = true;
        } else if(alph_equal && result[i - word_start] > sentence[i]) {
          alph_equal = false;
        } else if(alph_equal && result[i - word_start] < sentence[i]) {
          bigger = true;
          alph_equal = false;
        }
      }

      return result;
    }
};


int main() {
  
  assert(Solution::solve("Ana are mere rosii si galbene") == "si");
  assert(Solution::solve("Este cel mai frumos loc") == "mai");
  assert(Solution::solve("Cineva este la usa x") == "x");
  try{
    assert(Solution::solve("Cineva. este la usa x") == "x");
    assert(false);
  } catch(char const* x) {

  };
  
  return 0;
}
