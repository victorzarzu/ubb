from validation.validations import validate_score
from infrastructure.constants import epsilon, oo

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
