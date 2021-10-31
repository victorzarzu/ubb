from infrastructure.comparators import comparer_smaller, comparer_bigger, comparer_divisible, comparer_and_valid_for_print
from infrastructure.constants import epsilon, oo

def comparer_smaller_test():
  assert comparer_smaller(1, 7) == True
  assert comparer_smaller(1.999999999, 2) == True
  assert comparer_smaller(2.000001, 2) == False

def comparer_bigger_test():
  assert comparer_bigger(6, 5) == True
  assert comparer_bigger(7.00001, 7) == True
  assert comparer_bigger(8.89, 9) == False
  
def comparer_divisible_test():
  assert comparer_divisible(10.5, 0.5) == True
  assert comparer_divisible(9.9, 0.1) == True
  assert comparer_divisible(5.6, 0.79) == False

def comparer_and_valid_for_print_test():
  assert comparer_and_valid_for_print(comparer_smaller, 7, 9) == True
  assert comparer_and_valid_for_print(comparer_smaller, 7, 6.999) == False 
  assert comparer_and_valid_for_print(comparer_divisible, 7.5, 0.5) == True 
  assert comparer_and_valid_for_print(comparer_divisible, 7.5, 0.45) == False 
  assert comparer_and_valid_for_print(comparer_divisible, 9, 9) == True 
  assert comparer_and_valid_for_print(comparer_divisible, 10.5, 0.45) == False 
  assert comparer_and_valid_for_print(comparer_smaller, oo, 0.45) == False 

def run_comparators_tests():
  comparer_smaller_test()
  comparer_bigger_test()
  comparer_divisible_test()
  comparer_and_valid_for_print_test()
