#include "extractor.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>

#include "known_dictionary.h"

namespace {
using std::string;
using std::ifstream;
using std::map;
using std::set;
using std::vector;

bool file_exists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if(file == nullptr) {
        return false;
    }

    fclose(file);
    return true;
}

int get_next_word_start(const string& line, const int& position) {
    int next_position = position;
    while(next_position < line.size() && line[next_position] == ' ') {
        ++next_position;
    }

    return next_position;
}

bool is_separator(char ch, const KnownDictionary& known_dictionary) {
    return known_dictionary.get_atom_type(string(1, ch)) == SEPARATOR;
}

string get_word_from_start(const string& line, const int& position, const KnownDictionary& known_dictionary) {
    int current_position = position;
    string word = "";
    while(current_position < line.size() && !is_separator(line[current_position], known_dictionary)) {
        word.push_back(line[current_position]);
        current_position++;
    }
    return word;
}

int get_words_start(const string& line) {
    return get_next_word_start(line, 0);
}
} //  namespace

Extractor::Extractor(const string& filename, const KnownDictionary& known_dictionary) : filename(filename), known_dictionary(known_dictionary) {
    if(!file_exists(filename.c_str())) {
        throw std::invalid_argument("The provided program file does not exist.");
    }
}

std::map<AtomType, vector<Atom> > Extractor::extract() const {
    map<AtomType, vector<Atom> > atoms;
    int row = 1, column;
    string line;
    ifstream input;
    input.open(filename);

    if(!input.is_open()) {
        throw std::invalid_argument("The provided program file can't be opened.");
    }

    while(getline(input, line)) {
        if(line.empty()) {
            ++row;
            continue;
        }
        column = get_words_start(line);

        while(column < line.size()) {
            if(is_separator(line[column], this->known_dictionary)) {
                atoms[SEPARATOR].push_back(Atom(row, column, string(1, line[column]), SEPARATOR));
                column++;
                continue;
            }
            string word = get_word_from_start(line, column, this->known_dictionary);
            AtomType atom_type = this->known_dictionary.get_atom_type(word);
            if(atom_type == UNKWONW_TYPE) {
                input.close();
                throw std::invalid_argument("Error at " + std::to_string(row) + ":" + std::to_string(column) + " - " + word + ".");
            }
            atoms[atom_type].push_back(Atom(row, column, word, atom_type));

            column = get_next_word_start(line, column + word.size());
        }
        row++;
    }

    input.close();

    return atoms;
}