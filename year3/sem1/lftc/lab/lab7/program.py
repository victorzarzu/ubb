from finite_automata.finite_automata import DetFiniteAutomataReader
from extractor.atom_class import AtomClass
from extractor.extractor import Extractor
from internal_program.fip import FIP
from internal_program.hash_table import HashTable
from internal_program.symbol_table import SymbolTable
import sys

reader = DetFiniteAutomataReader('./finite_automata/definitions/integer_constants.txt')
constants_af = reader.read()
reader = DetFiniteAutomataReader('./finite_automata/definitions/integer_constants_suffixes.txt')
suffixes_af = reader.read()
literals_af = constants_af.concatenate(suffixes_af)

reader = DetFiniteAutomataReader('./finite_automata/definitions/real_constants.txt')
real_constants_af = reader.read()

reader = DetFiniteAutomataReader('./finite_automata/definitions/string_constants.txt')
string_constants_af = reader.read()

reader = DetFiniteAutomataReader('./finite_automata/definitions/id.txt')
id_constants_af = reader.read()

separators = [" ", "(", ")", "{", "}", ";", "\n", ","]
operators = ["=", "+", "-", "*", "%",]
reserved_words = ["#include", "<iostream>", "using", "namespace", "std", "return", "int", "float", "struct", "cin>>", "cout<<", "if", "while", "main"]

afs = [literals_af, real_constants_af, string_constants_af, id_constants_af]
filename = "doi_1.cpp"

def create_ts(words):
    return SymbolTable([word for word in words])

def print_to_file(string, filename):
    with open(filename, "w") as file:
        file.write(string)

extractor = Extractor(filename = sys.argv[1], afs = afs, reserved_words = reserved_words, separators = separators, operators = operators)
atoms, unique_atoms, grouped_atoms = extractor.extract()
print(unique_atoms)

id_ts = create_ts(grouped_atoms[AtomClass.ID])
const_ts = create_ts(grouped_atoms[AtomClass.CONST])
fip = FIP(id_ts, const_ts, unique_atoms, atoms)

print_to_file(str(id_ts), "id_ts.txt")
print_to_file(str(const_ts), "const_ts.txt")
print_to_file(str(fip), "fip.txt")