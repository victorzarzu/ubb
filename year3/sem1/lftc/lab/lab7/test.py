from finite_automata.finite_automata import DetFiniteAutomataReader
from extractor.atom_class import AtomClass

class Tester:
    def testAll(self):
        self.__testRealConstants()
        self.__testIntegerConstants()
        self.__testIds()
    
    def __testRealConstants(self):
        reader = DetFiniteAutomataReader('./finite_automata/definitions/real_constants.txt')
        real_constants_af = reader.read()

        assert real_constants_af.type == AtomClass.CONST

        assert real_constants_af.accepts("0b00011.11") == True
        assert real_constants_af.accepts("0b00012.11") == False
        assert real_constants_af.accepts("0xAF453a.8") == True
        assert real_constants_af.accepts("0xAF453a") == True
        assert real_constants_af.accepts("0xAG453a") == False
        assert real_constants_af.accepts("08341") == False
        assert real_constants_af.accepts("07341") == True
        assert real_constants_af.accepts("07341.743") == True
        assert real_constants_af.accepts("07341.7408") == False
        assert real_constants_af.accepts("12314.432") == True
        assert real_constants_af.accepts("99342") == True

    def __testIntegerConstants(self):
        reader = DetFiniteAutomataReader('./finite_automata/definitions/integer_constants.txt')
        real_constants_af = reader.read()

        assert real_constants_af.type == AtomClass.CONST

        assert real_constants_af.accepts("0xAF453a") == True
        assert real_constants_af.accepts("0xAG453a") == False
        assert real_constants_af.accepts("0b1102") == False
        assert real_constants_af.accepts("08341") == False
        assert real_constants_af.accepts("07341") == True
        assert real_constants_af.accepts("08341") == False
        assert real_constants_af.accepts("99342") == True

    def __testIds(self):
        reader = DetFiniteAutomataReader('./finite_automata/definitions/id.txt')
        real_constants_af = reader.read()

        assert real_constants_af.type == AtomClass.ID

        assert real_constants_af.accepts("_absc") == True
        assert real_constants_af.accepts("4dfsa") == False
        assert real_constants_af.accepts("_fdsa_dfsa_") == True 


tester = Tester()
tester.testAll()