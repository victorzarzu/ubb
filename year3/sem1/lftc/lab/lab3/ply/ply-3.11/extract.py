import sys
import os
import ply.lex as lex

tokens = [
    'ID',
    'CONST',
    'RESERVED',
    'SEPARATOR',
    'OPERATOR',
]

def t_RESERVED(t):
    r'\#include|<iostream>|using|namespace|std|return|int|float|struct|cin>>|cout<<|if|while|main'
    return t

def t_CONST(t):
    r'(0\.[0-9]+|[1-9][0-9]*(\.[1-9][0-9]*[1-9])?|0\s|\"\s\"|\"\\n\")'
    t.value = t.value
    return t

def t_ID(t):
    r'[a-zA-Z_]([a-zA-Z0-9_]){0,249}'
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

# Track the previous token to detect errors like "3.14a"
previous_token = None

def t_error(t):
    global previous_token
    line_start = t.lexer.lexdata.rfind('\n', 0, t.lexpos) + 1
    column = (t.lexpos - line_start) + 1
    
    if previous_token and previous_token.type == 'CONST' and t.value and t.value[0].isalpha():
        print(f"Line {t.lineno}, Column {column}: Illegal character '{previous_token.value + t.value}'")
    else:
        print(f"Line {t.lineno}, Column {column}: Illegal character '{t.value[0]}'")
    
    t.lexer.skip(1)

def t_CONST_error(t):
    global previous_token
    if previous_token and previous_token.type == 'CONST' and t.value and t.value[0].isalpha():
        print(f"Line {t.lineno}, Column {t.lexpos - len(previous_token.value)}: Illegal character(s) '{previous_token.value + t.value}'")
    else:
        print(f"Line {t.lineno}, Column {t.lexpos - len(t.value)}: Illegal character(s) '{t.value}'")
    t.lexer.skip(len(t.value)

# Define a state to handle the case where a letter immediately follows a numeric token
states = (
    ('letterafternumber', 'inclusive'),
)

# Transition to the 'letterafternumber' state when a letter follows a numeric token
def t_letterafternumber(t):
    r'[a-zA-Z_]'
    t.lexer.begin('letterafternumber')

# When in 'letterafternumber' state, treat any character as a part of the error
def t_letterafternumber_error(t):
    global previous_token
    if previous_token and previous_token.type == 'CONST':
        print(f"Line {t.lineno}, Column {t.lexpos - len(previous_token.value)}: Illegal character(s) '{previous_token.value + t.value}'")
    else:
        print(f"Line {t.lineno}, Column {t.lexpos - len(t.value)}: Illegal character(s) '{t.value}'")
    t.lexer.skip(1)

# Return to the initial state after the error
def t_letterafternumber_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)
    t.lexer.begin('INITIAL')

if len(sys.argv) != 2:
    print('Invalid arguments - the name of the file is required')
    exit()

if not os.path.exists(sys.argv[1]):
    print(sys.argv[1] + " file does not exist.")
    exit()

def extract(filename):
    lexer = lex.lex()
    lexer.begin('INITIAL')

    with open(filename, 'r') as file:
        code = file.read()
    
    atoms = {atom_type: [] for atom_type in tokens}
    error = False
    global previous_token
    current_token = ""

    for char in code:
        current_token += char
        lexer.input(current_token)
        tok = lexer.token()
        if tok:
            if 'Illegal' in tok.type:
                print(f"Line {tok.lineno}, Column {tok.lexpos}: Illegal character '{tok.value}'")
                error = True
            else:
                atoms[tok.type].append((tok.value, tok.lineno, tok.lexpos))
            current_token = ""
            previous_token = tok
            if tok.type == 'CONST':
                lexer.begin('letterafternumber')
            else:
                lexer.begin('INITIAL')

    if error:
        exit()

    return atoms

def export_atoms(atoms, filename):
    f = open(filename, "w")
    for atom_type, tuples in atoms.items():
        f.write(str(atom_type) + "\n")
        for atom in tuples:
            f.write(str(atom) + "\n")

atoms = extract(sys.argv[1])
export_atoms(atoms, "atomi.txt")
