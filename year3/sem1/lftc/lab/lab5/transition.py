class Transition:
    def __init__(self, srcState, symbol, destState):
        self.__srcState = srcState
        self.__symbol = symbol
        self.__destState = destState
    
    @property
    def srcState(self):
        return self.__srcState

    @property
    def symbol(self):
        return self.__symbol

    @property
    def destState(self):
        return self.__destState
    
    def __str__(self):
        return self.__srcState.state + " -> " + self.__symbol + " -> " + self.__destState.state