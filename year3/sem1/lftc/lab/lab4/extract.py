import sys
import os
import ply.lex as lex
from symbol_table import SymbolTable
from fip import FIP

tokens = [
    'ID',
    'CONST',
    'RESERVED',
    'SEPARATOR',
    'OPERATOR',
    'ERROR',
]

reserved = [
    'using', 'namespace', 'std', 'int', 'float', 'main',
    'cout<<', 'cin>>', 'if', 'while', 'return',
    'cout<<"\\n"',
]

def t_ERROR(t):
    r'[0-9]+\.[0-9]+[a-zA-Z_]+|0[a-zA-Z_]([a-zA-Z0-9_])*|0[0-9]+|[a-zA-Z_]([a-zA-Z0-9_]){250,}'
    line_start = t.lexer.lexdata.rfind('\n', 0, t.lexpos) + 1
    column = (t.lexpos - line_start) + 1
    
    print(f"Line {t.lineno}, Column {column}: Illegal character(s) '{t.value}'")
    t.lexer.skip(1)

def t_RESERVED(t):
    r'\#include|<iostream>|using|namespace|std|return|int|float|struct|cin>>|cout<<|if|while|main'
    return t

def t_CONST(t):
    r'0\.[0-9]+|[1-9][0-9]*(\.[1-9][0-9]*[1-9])?|0|\"\s\"|\"\\n\"'
    t.value = t.value
    return t

def t_ID(t):
    r'[a-zA-Z_]([a-zA-Z0-9_])*'
    return t

def t_SEPARATOR(t):
    r'\(|\)|\{|\}|\;|\,'
    return t

def t_OPERATOR(t):
    r'=|\*|\%|-|\+|\=|\>|==|!=|&&|\|\|;'
    return t

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

t_ignore = ' \t'

def t_error(t):
    line_start = t.lexer.lexdata.rfind('\n', 0, t.lexpos) + 1
    column = (t.lexpos - line_start) + 1
    
    print(f"Line {t.lineno}, Column {column}: Illegal atom '{t.value[0]}'")
    t.lexer.skip(1)

if len(sys.argv) != 2:
    print('Invalid arguments - the name of the file is required')
    exit()

if not os.path.exists(sys.argv[1]):
    print(sys.argv[1] + " file does not exist.")
    exit()

def extract(filename):
    lexer = lex.lex()

    lexer.input(open(filename).read())

    unique_atoms = dict({'ID': 0, 'CONST': 1})
    grouped_atoms = {atom_type: [] for atom_type in tokens}
    atoms = []
    error = False

    while True:
        tok = lexer.token()
        if not tok:
            break
        if 'Illegal' in tok.type:
            print(tok.type)
            error = True
            continue
        grouped_atoms[tok.type].append((tok.value, tok.lineno, tok.lexpos))
        if tok.value not in unique_atoms and tok.type not in ['ID', 'CONST']:
            unique_atoms[tok.value] = len(unique_atoms)
        atoms.append((tok.type, tok.value))

    if error:
        exit()

    return atoms, unique_atoms, grouped_atoms

def export_atoms(atoms, filename):
    f = open(filename, "w")
    for atom_type, tuples in atoms.items():
        f.write(str(atom_type) + "\n")
        for atom in tuples:
            f.write(str(atom) + "\n")

def print_to_file(string, filename):
    with open(filename, "w") as file:
        file.write(string)

def create_ts(words):
    return SymbolTable([word[0] for word in words])

atoms, unique_atoms, grouped_atoms = extract(sys.argv[1])
id_ts = create_ts(grouped_atoms['ID'])
const_ts = create_ts(grouped_atoms['CONST'])
fip = FIP(id_ts, const_ts, unique_atoms, atoms)
print(unique_atoms)

print_to_file(str(id_ts), "id_ts.txt")
print_to_file(str(const_ts), "const_ts.txt")
print_to_file(str(fip), "fip.txt")

#export_atoms(grouped_atoms, "atomi.txt")