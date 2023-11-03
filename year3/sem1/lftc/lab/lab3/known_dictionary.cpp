#include "known_dictionary.h"

#include <regex>
#include <string>

namespace {
using std::regex_match;
using std::regex;
using std::string;

string id_regex = "[a-zA-Z_]([a-zA-Z0-9_])*";
string const_regex = "0|0\\s|0\\.[1-9][0-9]*[1-9]|[1-9]*(\\.[1-9][0-9]*[1-9])?";
string reserved_regex = "#include|<iostream>|using|namespace|std|return|int|float|struct|cin>>|cout<<(\"\\\\n\")?|if|while|main";
string separator_regex = "\\(|\\)|\\{|\\}|\\;|\\,|\\s";
string operator_regex = "=|\\*|%|-|\\+|=|>|==|!=|&&|\\|\\|";

}

AtomType KnownDictionary::get_atom_type(const string& word) const {
    if(regex_match(word, regex(reserved_regex))) {
        return RESERVED;
    }
    if(regex_match(word, regex(id_regex))) {
        return ID;
    }
    if(regex_match(word, regex(const_regex))) {
        return CONST;
    }
    if(regex_match(word, regex(separator_regex))) {
        return SEPARATOR;
    }
    if(regex_match(word, regex(operator_regex))) {
        return OPERATOR;
    }

    return UNKWONW_TYPE;
}