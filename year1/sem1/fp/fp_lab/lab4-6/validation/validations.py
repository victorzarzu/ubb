def validate_score_list_by_len(score_l, max_scores, max_scores_participant):
  """
  function that verifies if list score_l list has a length smaller than the max_scores
  params: score_l - a list of floats; max_scores_participant - an integer
  return: - 
  raisee: Exception with text
          "too many scores trying to be added -> the maximum scores to be stored for a participant is {$max_scores}!" if the length of score_l is bigger than max_scores 
  """
  if len(score_l) > max_scores or len(score_l) == 0:
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
  params: par_l - a list of participant items; id_number - an integer 
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
  params: par_l - a list of participant items; id_interval - a list of 2 integers
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
