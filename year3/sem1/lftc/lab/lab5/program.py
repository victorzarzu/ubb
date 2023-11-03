from finite_automata import FiniteAutomataReader, DetFiniteAutomataReader

reader = DetFiniteAutomataReader('integer_constants.txt')
constants_af = reader.read()

reader = DetFiniteAutomataReader('integer_constants_suffixes.txt')
suffixes_af = reader.read()

literals_af = constants_af.concatenate(suffixes_af)

number = input("Number: ")
print(literals_af.accepts(number))
print(literals_af.longestPrefixLength(number))