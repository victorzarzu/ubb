import sys
import random
import os

if len(sys.argv) != 5:
    print("Error")
    exit()

countries = int(sys.argv[1])
part_per_country = int(sys.argv[2])
no_prob = int(sys.argv[3])
directory = sys.argv[4]

prob_fra = 0.02
id = 1
for country in range(1, countries + 1):
    for problem in range(1, no_prob + 1):
        with open(os.path.join(directory, "Rezultate{country}_{problem}.txt".format(country = country, problem = problem)), "w") as file:
            for part in range(part_per_country):
                score = random.randint(0, 100)
                is_fra = random.random() <= prob_fra 
                if is_fra:
                    score = -1
                file.write("{id} {score}\n".format(id = part + id, score = score))
    id += part_per_country