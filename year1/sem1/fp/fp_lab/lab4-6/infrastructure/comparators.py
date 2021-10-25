from validation.validations import validate_score
epsilon = 0.0000001
oo = 0x3f3f3f3f

def comparer_smaller(score1, score2):
  """
  function that return if score1 is smaller than score2
  params: score1 - a float; score2 - a float
  return: True, if score1 is smaller than score2, False otherwise
  """
  return score1 < score2

def comparer_bigger(score1, score2):
  """
  function that return if score1 is smaller than score2
  params: score1 - a float; score2 - a float
  return: True, if score1 is smaller than score2, False otherwise
  """
  return score1 > score2

def comparer_divisible(score, div):
  """
  function that verifies if score is divisible with div
  params: score - a float; div - a float
  return: True if score is divisible with div and False otherwise
  """
  l:int = 0
  r:int = int(score / div) * 2
  m:int = int((l + r) / 2)
  while l < r:
    m = int((l + r) / 2)
    if m * div - score <= epsilon and -epsilon <= m * div - score:
      return True
    elif m * div - score < -epsilon:
      l = m + 1
    else:
      r = m - 1

  return False

def comparer_and_valid_for_print(comparer, score, argument):
  """
  function that compares if a score verifies the comparer and if the score is a valid one
  params: comparer - a comparer function; score - a float; argument - a float number
  return: True if the score satisfies the comparer and it is smaller than 10 or equal with 10, and False otherwise
  """
  if(score > 10): return False
  return comparer(score, argument)

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

comparer_smaller_test()
comparer_bigger_test()
comparer_divisible_test()
comparer_and_valid_for_print_test()
