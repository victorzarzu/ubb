#include <iostream>
#include <set>
#include <unordered_map>
#include <string>
#include <stack>
#include <assert.h>

using std::cout;
using std::set;
using std::string;
using std::unordered_map;
using std::pair;
using std::stack;
using std::make_pair;

#define point pair<int, int>
#define x first
#define y second
#define epsilon 1e-3

class Solution {
  private:
    
    struct Trie {
      int number;
      unordered_map<char, Trie*> children;

      Trie() {
        number = 0;
      }
    };

  public:
    /*
      Metoda care insereaza un cuvant in trie
      @params: node - nodul de unde trebuie inserat cuvantul
               word - cuvantul care trebuie inserat
      @return: -
      Complexitate timp: O(n)
      Complexitate spatiu: O(n)
    */
    static void insert(Trie *node, string word) {
      if(!word.size()) {
        node->number++;
        return;
      }

      char next = word[0];
      if(!(node->children.count(next))) {
        node->children[next] = new Trie;
      }

      insert(node->children[next], word.substr(1));
    }

    /*
      Metoda care insereaza cuvintele dintr-o propozitie in trie
      @params: root - radacina trie-ului
               sentence - propozitia cu cuvinte 
      @return: -
      Complexitate timp: O(n)
      Complexitate spatiu: O(n)
    */
    static void insert_words(Trie* root, string sentence) {
      sentence.push_back(' ');
      string current_word = "";

      for(const auto& ch : sentence) {
        if(ch == ' ') {
          insert(root, current_word);
          current_word = "";
        } else {
          current_word.push_back(ch);
        }
      }
    }

    /*
      Metoda care returneaza cuvintele care apar o singura data in trie
      @params: root - radacina trie-ului
      @return: set<string> - o multime de string-uri care contine cuvintele unice din propozitie
      Complexitate timp: O(n)
      Complexitate spatiu: O(n)
    */
    static set<string> get_unique(Trie* root) {
      set<string> result;
      stack<pair<Trie*, string>> st;

      st.push(make_pair(root, ""));

      while(!st.empty()) {
        pair<Trie*, string> pr = st.top();
        st.pop();
        Trie *node = pr.first;
        string word = pr.second;

        if(node->number == 1) {
          result.insert(word);
        }
        for(const auto& p : node->children) {
          string new_word = word;
          new_word.push_back(p.first);
          st.push(make_pair(p.second, new_word));
        }
      }

      return result;

    }
    
    /*
      Metoda care returneaza cuvintele care apar o singura data in text
      @params: sentence - string 
      @return: set<string> - cuvintele care apar o singura data
      Complexitate timp: O(n)
      Complexitate spatiu: O(n)
    */
    static set<string> solve(const string& sentence) {
      Trie* root = new Trie;
      
      insert_words(root, sentence);
      return get_unique(root);
    }

    /*
      Metoda care returneaza cuvintele care apar o singura data in text
      @params: sentence - string 
      @return: set<string> - cuvintele care apar o singura data
      Complexitate timp: O(n)
      Complexitate spatiu: O(n)
    */
    static set<string> solve1(string sentence) {
      set<string> result;

      sentence.push_back(' ');
      string current_word = "";
      unordered_map<string, int> mp;

      for(const auto& ch : sentence) {
        if(ch == ' ') {
          mp[current_word]++;
          current_word = "";
        } else {
          current_word.push_back(ch);
        }
      }

      for(const auto& p : mp) {
        if(p.second == 1) {
          result.insert(p.first);
        }
      }

      return result;
    }
};

int main() {
  
  set<string> unu {"mere", "rosii"};  
  set<string> doi {"ceva", "el", "care" };

  assert(Solution::solve("ana are ana are mere rosii ana") == unu);
  assert(Solution::solve1("ana are ana are mere rosii ana") == unu);
  assert(Solution::solve("cineva are ceva pentru cineva care are pentru el") == doi);
  assert(Solution::solve1("cineva are ceva pentru cineva care are pentru el") == doi);


  return 0;
}
