class State:
    def __init__(self, state, isFinal = False):
        self.__state = state
        self.__isFinal = isFinal
        self.__transitions = []
    
    def addTransition(self, transition):
        self.__transitions[transition.symbol].append(transition)
    
    @property
    def state(self):
        return self.__state

    @property
    def transitions(self):
        return self.__transitions

    def __eq__(self, other):
        return self.__state == other.state

    def __hash__(self):
        return hash(self.__state)

    def isFinal(self):
        return self.__isFinal 

class FinalState(State):
    def isFinal(self):
        return True