import sys
import os
import ply.lex as lex

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
    r'[0-9]+\.[0-9]+[a-zA-Z_]+|0[a-zA-Z_]([a-zA-Z0-9_])*|0[0-9]+'
    print(f"Line {t.lineno}, Column {t.lexpos - len(t.value)}: Illegal character(s) '{t.value}'")
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
    print("Illegal character '%s'" % t.value[0])
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

    atoms = {atom_type: [] for atom_type in tokens}
    error = False

    while True:
        tok = lexer.token()
        if not tok:
            break
        if 'Illegal' in tok.type:
            print(tok.type)
            error = True
            continue
        atoms[tok.type].append((tok.value, tok.lineno, tok.lexpos))

    if error:
        exit()

    return atoms

def export_atoms(atoms, filename):
    f = open(filename, "w")
    for atom_type, tuples in atoms.items():
        f.write(str(atom_type) + "\n")
        for atom in tuples:
            f.write(str(atom) + "\n")

export_atoms(extract(sys.argv[1]), "atomi.txt")
