#ifndef EXTRACTOR_H_
#define EXTRACTOR_H_

#include <string>
#include <tuple>
#include <unordered_map>
#include <map>
#include <vector>

#include "known_dictionary.h"

struct Atom {
    int column, row;
    std::string atom;
    AtomType type;

    Atom(const int& row, const int& column, const std::string& atom, AtomType type) {
        this->row = row;
        this->column = column;
        this->atom = atom;
        this->type = type;
    }
};

class Extractor {
public:
    Extractor(const std::string& filename, const KnownDictionary& known_dictionary);

    std::map<AtomType, std::vector<Atom> > extract() const;

private:
    const KnownDictionary& known_dictionary;
    const std::string filename;
};

#endif