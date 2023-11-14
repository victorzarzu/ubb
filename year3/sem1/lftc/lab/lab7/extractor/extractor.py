from extractor.atom_class import AtomClass

class Extractor:
    def __init__(self, filename, afs, reserved_words, separators, operators):
        self.__filename = filename
        self.__afs = afs
        self.__reserved_words = reserved_words
        self.__separators = separators
        self.__operators = operators 
        self.__errors = []
        self.__no_line = 1
        self.__atoms = []
        self.__unique_atoms = dict({AtomClass.ID: 0, AtomClass.CONST: 1})
        self.__grouped_atoms = dict({x : [] for x in AtomClass})
    
    def extract(self):
        with open(self.__filename, "r") as file:
            for line in file:
                self.__extract_line(line)
                self.__no_line += 1
        
        if len(self.__errors):
            raise Exception(self.__errors)
        
        return self.__atoms, self.__unique_atoms, self.__grouped_atoms

    def __accepted_class(self, word):
        if word in self.__reserved_words:
            return AtomClass.RESERVED
        if word in self.__operators:
            return AtomClass.OPERATOR
        if word in self.__separators:
            return AtomClass.SEPARATOR 
        for af in self.__afs:
            if af.accepts(word):
                return af.type 
        return AtomClass.UNKNOWN

    def __is_accepted(self, word):
        return not self.__accepted_class(word) == AtomClass.UNKNOWN

    def __handle_atom(self, atom, line, column):
        if not self.__is_accepted(atom):
            self.__errors.append('Error {line}:{column} at {atom}'.format(line=column - len(atom) + 1, column = line, atom = atom))
            return
        atom_class = self.__accepted_class(atom) 
        if not atom_class == AtomClass.CONST and not atom_class == AtomClass.ID and atom not in self.__unique_atoms:
            self.__unique_atoms[atom] = len(self.__unique_atoms.keys())
        self.__atoms.append((atom_class, atom))
        self.__grouped_atoms[atom_class].append(atom)

    def __isIgnored(self, word):
        return word == " "

    def __isSeparatorOrOperator(self, word):
        return word in self.__separators or word in self.__operators

    def __extract_line(self, line):
        current_word = ""
        for index in range(len(line) - 1):
            if self.__isSeparatorOrOperator(str(line[index])):
                current_word = ""
                if not self.__isIgnored(str(line[index])):
                    self.__handle_atom(atom = str(line[index]), line = self.__no_line, column = index)
                continue
            if current_word in self.__separators:
                self.__handle_atom(atom = current_word, line = self.__no_line, column = index)
                current_word = str(line[index])
                continue
            current_word += str(line[index])
            if str(line[index + 1]) in self.__separators:
                if not current_word in self.__separators:
                    self.__handle_atom(atom = current_word, line = self.__no_line, column = index)
                current_word = str(line[index + 1])
