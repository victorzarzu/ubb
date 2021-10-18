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

def comparer_smaller_test():
  assert comparer_smaller(1, 7) == True
  assert comparer_smaller(1.999999999, 2) == True
  assert comparer_smaller(2.000001, 2) == False

def comparer_bigger_test():
  assert comparer_bigger(6, 5) == True
  assert comparer_bigger(7.00001, 7) == True
  assert comparer_bigger(8.89, 9) == False

comparer_smaller_test()
comparer_bigger_test()
