from infrastructure.computes import compute_average
from infrastructure.constants import epsilon

def compute_average_test():
  average = compute_average([1, 2, 3])
  assert abs(average - 2) < epsilon

  average = compute_average([5.8, 2.5, 1.2, 9.8])
  assert abs(average - 4.825) < epsilon

def run_computes_tests():
  compute_average_test()
