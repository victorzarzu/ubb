from conversions import convert_score_list, convert_id_number
from validation.validations import validate_score_list, validate_participant_id_number, validate_score_list
import domain.participants as participants
from computes import compute_average

def add_score(par_l, score_l, max_scores):
  """
  function that adds participant into par_l
  params: par_l - a list of participant items; score_l - a list of floats
  return: -, if it can add the list of scores
  """
  score_l = convert_score_list(score_l)
  validate_score_list(score_l, max_scores, max_scores)
  score_avg = compute_average(score_l)
  participant = participants.create_participant(len(par_l), score_l, score_avg)
  participants.add_participant_in_list(par_l, participant)

def insert_score(par_l, score_l, id_number, max_scores):
  """
  function that adds a list of scores from scor_l into a list into par_l coresponding to the id_number-th participant
  params: par_l - a list of participant items; score_l - a list  of floats; id_number - a string; max_scores - an integer
  """
  id_number = convert_id_number(id_number)
  validate_participant_id_number(par_l, id_number)
  score_l = convert_score_list(score_l)
  max_scores_add = get_free_space_by_participant_id(par_l, id_number, max_scores)
  validate_score_list(score_l, max_scores_add, max_scores)
  insert_score_by_participant_id(par_l, id_number, score_l)
  

def get_free_space_by_participant_id(par_l, id_number, max_scores):
  """
  function that returns the number of scores that can be inserted for the id_number-th participant
  params: par_l - a list of participant items; id_number - an integer; max_scores - an integer
  return: an integer representig the number of scores that can be inserted for the id_number-th participant
  """
  participant = participants.get_participant_by_id(par_l, id_number)
  score_l = participants.get_participant_score(participant)
  return max_scores - len(score_l)

def insert_score_by_participant_id(par_l, id_number, score_l):
  """
  function that adds the scores in the score_l into the score list coresponding to the id_number-th participant
  params: par_l - a list of participant items; id_number - integer; score_l - a list of floats
  return: -
  """
  participant = participants.get_participant_by_id(par_l, id_number)
  participant_score = participants.get_participant_score(participant)
  participant_score.extend(score_l)
  participant = participants.create_participant(id_number, participant_score, compute_average(participant_score))
  participants.change_participant_by_id(par_l, id_number, participant)
  
def ui_add_score(par_l, max_scores):
  cmd = input().rstrip().lstrip()
  if cmd == "add":
    score_l = input("scores: ")
    add_score(par_l, score_l, max_scores)
  elif cmd == "insert":
    id_number = input("id: ") 
    score_l = input("scores: ")
    insert_score(par_l, score_l, id_number, max_scores)
  else:
    print("invalid command!")

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

def add_participant_list_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [6.2, 7, 7, 1, 4.5, 1.99], compute_average([6.2, 7, 7, 1, 4.5, 1.99]))
  participants.add_participant_in_list(par_l, participant)
  assert len(par_l) == 1
  assert par_l[0] == {'id': 0, 'score': [6.2, 7, 7, 1, 4.5, 1.99], 'score_avg': compute_average([6.2, 7, 7, 1, 4.5, 1.99])}

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
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [5, 5, 5, 5, 7], compute_average([5, 5, 5, 5, 7])))
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [9, 9.9, 9.423, 5, 1, 9], compute_average([9, 9.9, 9.423, 5, 1, 9])))
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [1, 2, 3, 4, 5, 999], compute_average([1, 2, 3, 4, 5, 999])))
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [1], 1))

  free_space = get_free_space_by_participant_id(par_l, 1, 10)
  assert free_space == 4

def insert_score_by_participant_id_test():
  par_l = []
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [5, 5, 5, 5, 7], compute_average([5, 5, 5, 5, 5, 7])))
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [9, 9.9, 9.423, 5, 1, 9], compute_average([9, 9.9, 9.423, 5, 1, 9])))
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [1, 2, 3, 4, 5, 999], compute_average([1, 2, 3, 4, 5, 999])))
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [1], 1))


  insert_score_by_participant_id(par_l, 0, [5, 9.1, 6.7])
  participant = participants.get_participant_by_id(par_l, 0)
  assert participants.get_participant_score(participant) == [5, 5, 5, 5, 7, 5, 9.1, 6.7]

def insert_score_test():
  par_l = []
  add_score(par_l, "6 6 6 2 4 1", 10)
  add_score(par_l, "6", 10)
  add_score(par_l, "10 1.7 9.4", 10)
  add_score(par_l, "9 9 2", 10)

  insert_score(par_l, "5 6", 0, 10)
  participant = participants.get_participant_by_id(par_l, 0)
  assert participants.get_participant_score(participant) == [6, 6, 6, 2, 4, 1, 5, 6] 

  insert_score(par_l, "10 10 10", 1, 10)
  participant = participants.get_participant_by_id(par_l, 1)
  assert participants.get_participant_score(participant) == [6, 10, 10, 10] 

  
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
add_score_test()
get_free_space_by_participant_id_test()
insert_score_by_participant_id_test()
insert_score_test()
