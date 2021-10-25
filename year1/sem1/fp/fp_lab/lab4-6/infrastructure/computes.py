import domain.participants as participants
epsilon = 0.0000001

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

  free_space = get_free_space_by_participant_id(par_l, 1, 10)
  assert free_space == 4

def compute_average_test():
  average = compute_average([1, 2, 3])
  assert abs(average - 2) < epsilon

  average = compute_average([5.8, 2.5, 1.2, 9.8])
  assert abs(average - 4.825) < epsilon

compute_average_test()