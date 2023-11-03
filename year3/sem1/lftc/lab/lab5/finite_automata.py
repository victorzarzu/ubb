from state import State, FinalState
from transition import Transition

class FiniteAutomata:
    def __init__(self, transitions, initState):
        self._initState = initState
        self._transitions = dict() 
        self.__createAutomata(transitions)

    def __createAutomata(self, transitions):
        for transition in transitions:
            if transition.srcState not in self._transitions:
                self._transitions[transition.srcState] = [transition]
                continue
            self._transitions[transition.srcState].append(transition)
    
    def accepts(self, sequence):
        return self.__accepts(self._initState, sequence)

    def __accepts(self, state, sequence):
        if(len(sequence) == 0 and state.isFinal()):
            return True
        if(len(sequence) == 0):
            return False
        if not state in self._transitions:
            return False
        
        for destState in self._symbolDestinations(state, sequence[0]):
            if self.__accepts(destState, sequence[1:]):
                return True

        return False
    
    def statesSet(self):
        return [state.state for state in self._transitions.keys()]
    
    def alphabetSet(self):
        return set(transition.symbol for transitions in self._transitions.values() for transition in transitions)

    def transitionsSet(self):
        return [str(transition) for transitions in self._transitions.values() for transition in transitions]
    
    def finalStatesSet(self):
        return [state.state for state in self._transitions.keys() if state.isFinal()]

    def __finalStates(self):
        return [state for state in self._transitions.keys() if state.isFinal()]

    def _symbolDestinations(self, state, symbol):
        if state not in self._transitions:
            return []
        return [transition.destState for transition in self._transitions[state] if transition.symbol == symbol]

    def __stateTransisions(self, state):
        if state not in self._transitions:
            raise Exception("State " + state.state + " is not in transitions")
        return self._transitions[state]

    def __removeFinalStates(self):
        newTransitions = dict()
        for transition in [transition for transitions in self._transitions.values() for transition in transitions]:
            srcState = State(transition.srcState.state)
            symbol = transition.symbol
            destState = State(transition.destState.state)
            if srcState not in newTransitions:
                newTransitions[srcState] = [Transition(srcState, symbol, destState)]
                continue
            newTransitions[srcState].append(Transition(srcState, symbol, destState))

        return newTransitions

    def concatenate(self, af):
        if not af._initState.isFinal():
            newTransitions = self.__removeFinalStates()
            thisFinalStates = self.__finalStates()
            finalStates = [newState for newState in newTransitions.keys() if newState in thisFinalStates]
            print([state.state for state in finalStates])

            transitions = [transition for transitions in newTransitions.values() for transition in transitions]
            transitions.extend([transition for transitions in af._transitions.values() for transition in transitions])

            for finalState in finalStates:
                for transition in af.__stateTransisions(af._initState):
                    transitions.append(Transition(finalState, transition.symbol, transition.destState))
        else:
            transitions = [transition for transitions in self._transitions.values() for transition in transitions]
            transitions.extend([transition for transitions in af._transitions.values() for transition in transitions])

            for finalState in self.__finalStates():
                for transition in af.__stateTransisions(af._initState):
                    transitions.append(Transition(finalState, transition.symbol, transition.destState))


        return self.__class__(transitions = transitions, initState = self._initState)


class DetFiniteAutomata(FiniteAutomata):
    def accepts(self, sequence):
        return self.__accepts(self._initState, sequence)

    def __accepts(self, state, sequence):
        if(len(sequence) == 0 and state.isFinal()):
            return True
        
        while len(sequence) > 0 and self._hasSymbolDestination(state, sequence[0]):
            state = self.__getSymbolDestination(state, sequence[0])
            sequence = sequence[1:]
        
        return len(sequence) == 0 and state.isFinal()
    
    def __longestPrefixLength(self, state, sequence):
        longestPrefixLength = 0
        length = 0

        while len(sequence) > 0 and self._hasSymbolDestination(state, sequence[0]):
            length += 1
            state = self.__getSymbolDestination(state, sequence[0])
            sequence = sequence[1:]
            
            if state.isFinal():
                longestPrefixLength = length
        
        return longestPrefixLength

    def longestPrefixLength(self, sequence):
        return self.__longestPrefixLength(self._initState, sequence)
    
    def _hasSymbolDestination(self, state, symbol):
        return len(self._symbolDestinations(state, symbol)) > 0

    def __getSymbolDestination(self, state, symbol):
        return self._symbolDestinations(state, symbol)[0]
    

class FiniteAutomataReader:
    def __init__(self, filename = None):
        self._filename = filename
        self.__states = dict()
    
    def read(self):
        if self._filename is None:
            transitions, initState = self._console_read_elements()
            return FiniteAutomata(transitions = transitions, initState = initState)
        transitions, initState =  self._file_read_elements() 
        return FiniteAutomata(transitions = transitions, initState = initState)

    def _console_read_elements(self):
        initState = State(input("Initial state: "))
        finalStates = self.__getSpacedFinalStates(input("Final states (separated by blanks): "))
        for finalState in finalStates:
            self.__addState(finalState)
        initState = self.__addState(initState)

        print("Transitions (state symbols state)")

        transitions = []
        while True:
            line = input()
            if not line:
                break 
            transitions.extend(self.__getTransitionsFromSequence(line))
        
        return transitions, initState

    def _file_read_elements(self):
        with open(self._filename, "r") as file:
            initState = State(file.readline()[:-1])
            finalStates = self.__getSpacedFinalStates(file.readline()[:-1])
            for finalState in finalStates:
                self.__addState(finalState)
            initState = self.__addState(initState)

            transitions = []
            for line in file:
                transitions.extend(self.__getTransitionsFromSequence(line[:-1]))
            
            return transitions, initState
                
    def __getTransitionsFromSequence(self, sequence):
        [srcSymbol, symbols, destSymbol] = sequence.split()
        srcState = self.__addState(State(srcSymbol))
        destState = self.__addState(State(destSymbol))

        return [Transition(srcState, symbol, destState) for symbol in self.__getListedSymbols(symbols)]

    def __getSpacedFinalStates(self, sequence):
        return [FinalState(state = state) for state in sequence.split()]
    
    def __getIntervalSymbols(self, interval):
        if len(interval) == 1:
            return interval
        [start, end] = interval.split('-')
        return [chr(val) for val in range(ord(start), ord(end) + 1)]
    
    def __flatten(self, l):
        return [item for sublist in l for item in sublist]

    def __getListedSymbols(self, sequence):
        return self.__flatten([self.__getIntervalSymbols(interval) for interval in sequence.split(',')])

    def __addState(self, state):
        if state.state not in self.__states:
            self.__states[state.state] = state 
        return self.__states[state.state]
    
    def __getState(self, symbol):
        if symbol not in self.__states:
            raise Exception("Symbol not in dictionary")
        return self.__states[symbol]
    
class DetFiniteAutomataReader(FiniteAutomataReader):
    def __init__(self, filename = None):
        super().__init__(filename)
    
    def read(self):
        if self._filename is None:
            transitions, initState = self._console_read_elements()
            return DetFiniteAutomata(transitions = transitions, initState = initState)
        transitions, initState =  self._file_read_elements() 
        return DetFiniteAutomata(transitions = transitions, initState = initState)
