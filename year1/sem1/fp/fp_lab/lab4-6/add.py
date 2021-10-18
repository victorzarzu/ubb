from conversions import convert_score_list, convert_id_number
from validations import validate_score_list, validate_participant_id_number, validate_score_list


def add_score_list_in_list(par_l, score_l):
  """
  function that adds the score list from score_l to par_l
  params: par_l - a list of list of floats; score_l: a list of floats
  return: -
  """
  par_l.append(score_l)

def add_score(par_l, score_l, max_scores):
  """
  function that adds a list of scores from score_l into par_l
  params: par_l - a list of lists of floats; score_l - a list of floats
  return: -, if it can add the list of scores
  """
  score_l = convert_score_list(score_l)
  validate_score_list(score_l, max_scores, max_scores)
  add_score_list_in_list(par_l, score_l)

def insert_score(par_l, score_l, id_number, max_scores):
  """
  function that adds a list of scores from scor_l into a list into par_l coresponding to the id_number-th participant
  params: par_l - a list of list of floats; score_l - a list of lists of floats; id_number - an integer; max_scores - an integer
  """
  validate_participant_id_number(par_l, id_number)
  score_l = convert_score_list(score_l)
  max_scores_add = get_free_space_by_participant_id(par_l, id_number, max_scores)
  validate_score_list(score_l, max_scores_add, max_scores)
  insert_score_by_participant_id(par_l, id_number, score_l)
  

def ui_add_score(par_l, max_scores):
  cmd = input().rstrip().lstrip()
  if cmd == "add":
    score_l = input("scores: ")
    add_score(par_l, score_l, max_scores)
  elif cmd == "insert":
    try:
      id_number = convert_id_number(input("id: ")) 
    except Exception as ex:
      print(ex)
      return

    score_l = input("scores: ")
    insert_score(par_l, score_l, id_number, max_scores)
  else:
    print("invalid command!")

def get_score_by_participant_id(par_l, id_number):
  """
  a function that returns the list of scores of the id_number-th participant
  params: par_l - a list of list of floats; id_number - an integer
  return: a list of floats, if the id_number is a correct id
  raises: Exception with text
          "invalid contest id!" if the id_number is not a valid id
  """
  return par_l[id_number]

def get_free_space_by_participant_id(par_l, id_number, max_scores):
  """
  function that returns the number of scores that can be inserted for the id_number-th participant
  params: par_l - a list of lists of integers; id_number - an integer; max_scores - an integer
  return: an integer representig the number of scores that can be inserted for the id_number-th participant
  """
  score_l = get_score_by_participant_id(par_l, id_number)
  return max_scores - len(score_l)

def insert_score_by_participant_id(par_l, id_number, score_l):
  """
  function that adds the scores in the score_l into the score list coresponding to the id_number-th participant
  params: par_l - a list of lists of floats; id_number - integer; score_l - a list of floats
  return: -
  """
  par_l[id_number].extend(score_l)

def convert_score_list_test():
  score_l = "5 6 9 10 15, a"
  try:
    convert_score_list(score_l)
    assert(False)
  except Exception as ex:
    assert str(ex) == "invalid numbers!"

  score_l = "15.6 6 9 15"
  score_l = convert_score_list(score_l)
  assert score_l == [15.6, 6.0, 9.0, 15.0]
  
  score_l = "6 8 ? 10 6.7 9./"
  try:
    convert_score_list(score_l)
    assert(False)
  except Exception as ex:
    assert str(ex) == "invalid numbers!"

def add_score_list_in_list_test():
  par_l = []
  score_l = [6.2, 7, 7, 1, 4.5, 1.99]
  add_score_list_in_list(par_l, score_l)
  assert len(par_l) == 1
  assert par_l[0] == [6.2, 7.0, 7.0, 1.0, 4.5, 1.99]

def add_score_test():
  par_l = []
  add_score(par_l, "9.8 1 5 1.4", 10)
  assert len(par_l) == 1

  add_score(par_l, "9 1 8 10", 10)

  try:
    add_score(par_l, "1 1 1 1 1 1 11 1 1 1 11 1 1 ", 10)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!"

  try:
    add_score(par_l, "9.6 1 1 / 6 7", 10)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid numbers!"
 

def get_free_space_by_participant_id_test():
  par_l = []
  add_score_list_in_list(par_l, [5, 5, 5, 5, 7])
  add_score_list_in_list(par_l, [9, 9.9, 10.52352, 5, 1, 9])
  add_score_list_in_list(par_l, [1, 2, 3, 4, 5, 999])
  add_score_list_in_list(par_l, [1])

  free_space = get_free_space_by_participant_id(par_l, 1, 10)
  assert free_space == 4

def get_score_by_participant_id_test():
  par_l = []
  add_score_list_in_list(par_l, [5, 5, 5, 5, 7])
  add_score_list_in_list(par_l, [9, 9.9, 10.52352, 5, 1, 9])
  add_score_list_in_list(par_l, [1, 2, 3, 4, 5, 999])
  add_score_list_in_list(par_l, [1])

  score_l = get_score_by_participant_id(par_l, 2)
  assert score_l == [1, 2, 3, 4, 5, 999]

  add_score_list_in_list(par_l, [10.1])
  score_l = get_score_by_participant_id(par_l, 1)
  assert score_l == [9, 9.9, 10.52352, 5, 1, 9]

def insert_score_by_participant_id_test():
  par_l = []
  add_score_list_in_list(par_l, [5, 5, 5, 5, 7])
  add_score_list_in_list(par_l, [9, 9.9, 10.52352, 5, 1, 9])
  add_score_list_in_list(par_l, [1, 2, 3, 4, 5, 999])

  insert_score_by_participant_id(par_l, 0, [5, 9.1, 6.7])
  assert get_score_by_participant_id(par_l, 0) == [5, 5, 5, 5, 7, 5, 9.1, 6.7]

def insert_score_test():
  par_l = []
  add_score(par_l, "6 6 6 2 4 1", 10)
  add_score(par_l, "6", 10)
  add_score(par_l, "10 1.7 9.4", 10)
  add_score(par_l, "9 9 2", 10)

  insert_score(par_l, "5 6", 0, 10)
  assert get_score_by_participant_id(par_l, 0) == [6, 6, 6, 2, 4, 1, 5, 6] 
  
  try: 
    insert_score(par_l, "1 1 1 1 1 1 1 1 6 7", 2, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!" 

  try:
    insert_score(par_l, "6 & 1 4", 3, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid numbers!"

  try:
    insert_score(par_l, "3 4", 6, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

convert_score_list_test()
add_score_list_in_list_test()
add_score_test()
get_score_by_participant_id_test()
get_free_space_by_participant_id_test()
insert_score_by_participant_id_test()
insert_score_test()
