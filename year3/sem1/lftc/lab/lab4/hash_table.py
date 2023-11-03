
class HashTable:
    def __init__(self):
        self.__table = dict()
        self.__m = 666013 
        self.__p = 31
    
    def add(self, word):
        hashCode = self.__hashCode(word)
        if hashCode in self.__table:
            if word not in self.__table[hashCode]:
                self.__table.append(word)
            return
        
        self.__table[hashCode] = [word]
    
    def find(self, word):
        hashCode = self.__hashCode(word)
        if hashCode in self.__table:
            return hashCode
        
        return -1

    def __hashCode(self, word):
        return sum([ord(word[i]) * (self.__p ** i) for i in range(len(word))]) % self.__m
    
    def __str__(self):
        result = ""
        for value, words in self.__table.items():
            for word in words:
                result += word + " " + str(value) + "\n"
        return result