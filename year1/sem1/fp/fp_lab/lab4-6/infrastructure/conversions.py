def convert_score_list(score_l):
  """
  function that converts the score lists into a list of floats and returns it
  params: -
  return: a list of floats, if it cand convert them
  raises: Exception with text
          "invalid numbers!\n", if the data is not float
  """
  try:
    return [float(x) for x in score_l.split()]
  except ValueError:
    raise Exception("invalid numbers!")

def convert_id_number(id_number):
  """
  function that converts the string of id_number into integer
  params: id_number - a string
  return: a integer representing id_number
  raises: Exception with text
          "invalid contest id!", if the conversion to integer is not possibile
  """
  try:
    return int(id_number)
  except ValueError:
    raise Exception("invalid contest id!")
 

def convert_id_interval(id_interval):
  """
  function that converts the string of id_interval into a list of integers
  params: id_interval - a string
  return: a list of integers
  raises: Exception with text
          "invalid contest id interval!", if the strint cannot be converted to a list of integers, because the list is not of length 2 or if the interval is not in the form [a, b], a <= b
  """
  try:
    id_interval = [int(x) for x in id_interval.split()]
  except ValueError:
    raise Exception("invalid contest id interval!")

  if len(id_interval) != 2:
    raise Exception("invalid contest id interval!")

  if id_interval[0] > id_interval[1]:
    raise Exception("invalid contest id interval!")
  
  return id_interval

def convert_score(score):
  """
  a function that converts a score from string to int
  params: score - a string
  return: a float number, if it is in float format
  raisese: Exception with text
          "invalid score!", if the string cannot be converted to a float
  """
  try:
    return float(score)
  except ValueError:
    raise Exception("invalid score!")

def convert_score_list_test():
  score_l = "1 5 6 7 9.6 1"
  score_l = convert_score_list(score_l)
  assert score_l == [1, 5, 6, 7, 9.6, 1]

  try:
    convert_score_list("5.7 1 * 9")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid numbers!"

def convert_id_number_test():
  convert_id_number("5")

  try:
    convert_id_number("1.5")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

  try:
    convert_id_number("a")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

def convert_id_interval_test():
  convert_id_interval("8 9")

  try:
    convert_id_interval("9 6")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

  try:
    convert_id_interval("1.5 10")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

def convert_score_test():
  convert_score("1.9")

  try:
    convert_score("7/4")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid score!"

convert_score_list_test()
convert_id_number_test()
convert_id_interval_test()
convert_score_test()
