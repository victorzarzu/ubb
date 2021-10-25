def validate_score_list_by_len(score_l, max_scores, max_scores_participant):
  """
  function that verifies if list score_l list has a length smaller than the max_scores
  params: score_l - a list of floats; max_scores - an integer
  return: - 
  raisee: Exception with text
          "too many scores trying to be added -> the maximum scores to be stored for a participant is {$max_scores}!" if the length of score_l is bigger than max_scores 
  """
  if len(score_l) > max_scores:
    raise Exception("too many scores trying to be added -> the maximum scores to be stored for a participant is " + str(max_scores_participant) + "!")

def validate_score_list_by_values(score_l):
  """
  function that verifies if the score list has values between 1 and 10
  params: score_l - a list of floats
  return: - 
  raises: Exception with text
          "scores must be between 1 and 10!", if the values are not between 1 and 10
  """
  for x in score_l:
    validate_score(x)

def validate_participant_id_number(par_l, id_number):
  """
  function that verifies if the id_number is a valid one
  params: par_l - a list of list of integers
  return: -
  raises: Exception with text
          "invalid contest id!" if the id_number is not a valid one
  """

  if not id_number == int(id_number):
    raise Exception("invalid contest id!")

  if id_number < 0 or id_number >= len(par_l):
    raise Exception("invalid contest id!")

  
def validate_participant_id_interval(par_l, id_interval):
  """
  function that verifies if the id_interval is a valid one for par_l
  params: par_l - a list of lists of floats; id_interval - a list of 2 integers
  return: -, if the interval is valid
  raises: Exception with text
          "invalid contest id interval!", if the interval is not valid
  """
  if id_interval[0] < 0 or id_interval[1] >= len(par_l):
    raise Exception("invalid contest id interval!")


def validate_score_list(score_l, max_scores, max_scores_participant):
  """
  function that verifies if score_l is a valid string to be put in the the list
  params: score_l - a list of floats; max_scores - an integer
  return: -
  """
  validate_score_list_by_len(score_l, max_scores, max_scores_participant)
  validate_score_list_by_values(score_l)

def validate_score(score):
  """
  function that verifies if the score is a valid one (from 1 to 10)
  params: score - a float number
  return: -, if the score is a valid one
  raises: Exception with text
          "scores must be between 1 and 10!", if the score is not valid
  """
  if score < 1 or score > 10:
    raise Exception("scores must be between 1 and 10!")

def validate_score_print(score):
  """
  function that verifies if the score is smaller or equal than 10
  params: score - a float number
  return: True if the score is smaller or equal than 10 
  """
  return score <= 10 

def validate_sort_mode(sort_mode):
  """
  function that validates the sort_mode
  params: sort_mode - a string
  return -, if the sort mode is valid
  raises: Exception with text
          "invalid sort mode", if the sort mode is not a valid one
  """
  if sort_mode != "asc" and sort_mode != "desc":
    raise Exception("invalid sort mode!")


def validate_score_list_by_len_test():
  score_l = [1, 5, 7, 9, 10]
  validate_score_list_by_len(score_l, 10, 10)

  score_l = [1, 2, 3, 3, 3, 3, 3, 3, 10, 11, 11]
  try:
    validate_score_list_by_len(score_l, 10, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!"


def validate_score_list_by_values_test():
  score_l = [1, 6, 10, 8]
  validate_score_list_by_values(score_l)

  score_l = [1, 11.6, 7, 0]
  try:
    validate_score_list_by_values(score_l)
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!" 
 
def validate_participant_id_number_test():
  par_l = [[1], [2], [3], [6], [7], [9]]
  validate_participant_id_number(par_l, 4)

  try:
    validate_participant_id_number(par_l, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

  try:
    validate_participant_id_number(par_l, 4.5)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

def validate_participant_id_interval_test():
  par_l = [[1], [2], [3], [6], [7], [9], [2, 5, 7], [10, 2, 7.8]]
  validate_participant_id_interval(par_l, [0, 2])

  try:
    validate_participant_id_interval(par_l, [-1, 3])
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

  try:
    validate_participant_id_interval(par_l, [0, 10])
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

def validate_score_list_test():
  score_l = [1, 6, 10, 8]
  validate_score_list(score_l, 10, 10)

  score_l = [1, 11.6, 7, 0]
  try:
    validate_score_list(score_l, 10, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!"  

  score_l = [1, 11, 3, 4, 4, 4, 4, 4, 4, 8, 8, 8]
  try:
    validate_score_list(score_l, 10, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!"

def validate_score_test():
  validate_score(1.5)

  try:
    validate_score(0.999999)
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!"

def validate_sort_mode_test():
  validate_sort_mode("asc")
  validate_sort_mode("desc")

  try:
    validate_sort_mode("asc1")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid sort mode!"

validate_score_list_by_values_test()
validate_participant_id_number_test()
validate_participant_id_interval_test()
validate_score_list_test()
validate_score_test()
validate_sort_mode_test()
