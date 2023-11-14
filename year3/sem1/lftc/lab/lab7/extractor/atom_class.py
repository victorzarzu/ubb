from enum import Enum

class AtomClass(Enum):
    UNKNOWN = 0
    ID = 1
    CONST = 2
    RESERVED = 3
    SEPARATOR = 4
    OPERATOR = 5