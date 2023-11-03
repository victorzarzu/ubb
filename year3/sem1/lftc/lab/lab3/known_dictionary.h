#ifndef KNOWN_DICTIONARY_H
#define KNOWN_DICTIONARY_H

#include <string>

enum AtomType {
    UNKWONW_TYPE,
    ID,
    CONST,
    RESERVED,
    SEPARATOR,
    OPERATOR
};

class KnownDictionary {
public:
    AtomType get_atom_type(const std::string& word) const;
};

#endif