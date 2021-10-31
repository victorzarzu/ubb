import domain.participants as participants
from infrastructure.constants import epsilon

def compute_average(score_l):
  """
  function that computes the average of the items of a list
  score_l: score_l - a list of floats
  return: a float number representing the average of the list
  """
  if len(score_l):
    return sum(score_l) / len(score_l)
  else:
    return 0
