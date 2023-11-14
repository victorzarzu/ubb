from internal_program.hash_table import HashTable

class SymbolTable:
    def __init__(self, symbols):
        self.__ts = HashTable()
        for symbol in symbols:
            self.__ts.add(symbol)
    
    def find(self, word):
        return self.__ts.find(word)
    
    def __str__(self):
        return str(self.__ts)