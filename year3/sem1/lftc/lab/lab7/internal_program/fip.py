from internal_program.symbol_table import SymbolTable
from extractor.atom_class import AtomClass

class FIP:
    def __init__(self, id_ts, const_ts, unique_atoms, atoms):
        self.__fip = []
        self.__id_ts = id_ts
        self.__const_ts = const_ts

        for atom in atoms:
            type = atom[0]
            word = atom[1]
            if type == AtomClass.ID:
                self.__fip.append((unique_atoms[type], self.__id_ts.find(word)))
                continue
            if type == AtomClass.CONST:
                self.__fip.append((unique_atoms[type], self.__const_ts.find(word)))
                continue
            self.__fip.append((unique_atoms[word], -1))
    

    def __str__(self):
        result = ""
        for pair in self.__fip:
            result += str(pair[0]) + " " + str(pair[1]) + "\n"
        return result