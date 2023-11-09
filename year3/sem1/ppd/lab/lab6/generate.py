import sys
import random

if len(sys.argv) != 3:
    print("Error")
    exit()

n = int(sys.argv[1])
filename = sys.argv[2]

with open(filename, 'w') as file:
    file.write(str(n) + "\n")
    line = ""
    for _ in range(n):
        line += str(random.randint(0, 1000)) + " "
    file.write(line)
