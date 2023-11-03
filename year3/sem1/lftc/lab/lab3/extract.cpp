#include <unordered_set>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#include "extractor.h"
#include "known_dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Invalid arguments - the name of the file is required";
        return 0;
    }


    KnownDictionary known_dictionary = KnownDictionary();
    Extractor extractor = Extractor(argv[1], known_dictionary);
    
    try {
        map<AtomType, vector<Atom> > atoms = extractor.extract();
        std::ofstream atomi_output;
        atomi_output.open("atomi.txt");

        for(const auto& kv : atoms) {
            atomi_output<<kv.first<<'\n';
            for(const auto& atom : kv.second) {
                atomi_output<<atom.row<<" "<<atom.column<<" "<<atom.atom<<"\n";
            }
        }
    } catch(const std::invalid_argument& ex) {
        cout<<ex.what();
    }

    return 0;
}