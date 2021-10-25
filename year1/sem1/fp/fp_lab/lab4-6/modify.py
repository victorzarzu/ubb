from conversions import convert_id_number, convert_id_interval, convert_score_list
from validation.validations import validate_participant_id_number, validate_participant_id_interval, validate_score_list
from computes import compute_average
import domain.participants as participants


def delete_participant_score_by_id(par_l, id_number):
  """
  function that deletes the score list of the id_numer-th participant
  params: par_l - a list of participant items; id_number - an integer
  return: -, if the deletion is complete
  """
  participant = participants.create_participant(id_number, [], 0)
  participants.change_participant_by_id(par_l, id_number, participant)

def delete_participant_score_by_id_interval(par_l, id_interval):
  """
  function that deletes the score list of the participants that have an id in id_interval
  par_l: par_l - a list of participant; id_interval - a list of 2 integers
  return -, if the deletion is complete
  """
  for i in range(id_interval[0], id_interval[1] + 1):
    delete_participant_score_by_id(par_l, i)

def replace_participant_score_by_id(par_l, id_number, score_l):
  """
  function that replaces the score in the par_l of the id_number-th participant with score_l score list
  params: par_l - a list of lists of floats; id_numer - an integer; score_l - a list of floats
  return: -
  """
  participant = participants.create_participant(id_number, score_l, compute_average(score_l))
  participants.change_participant_by_id(par_l, id_number, participant)

def delete_participant_score(par_l, id_number):
  """
  function that deletes the score of the id_number-th
  params: par_l - a list of lists of integers; id_number - a string
  return: -
  """
  id_number = convert_id_number(id_number)
  validate_participant_id_number(par_l, id_number)
  delete_participant_score_by_id(par_l, id_number)

def delete_participant_interval_score(par_l, id_interval):  
  """
  function that deletes the score of the concurents that have and id in id_interval 
  params: par_l - a list of lists of integers; id_number - a string
  return: -
  """
  id_interval = convert_id_interval(id_interval)
  validate_participant_id_interval(par_l, id_interval)
  delete_participant_score_by_id_interval(par_l, id_interval)

def replace_participant_score(par_l, id_number, score_l, max_scores):
  """
  function that replaces the list of index id_number in the par_l list with score_l list
  params: par_l - a list of lists of integers; id_number - an integer; score_l - a list of floats
  return: -
  """
  id_number = convert_id_number(id_number)
  validate_participant_id_number(par_l, id_number)
  score_l = convert_score_list(score_l)
  validate_score_list(score_l, max_scores, max_scores)
  replace_participant_score_by_id(par_l, id_number, score_l)

def ui_modify_score(par_l, max_scores):
  cmd = input().lstrip().rstrip()
  if cmd == "del_id":
    id_number = input("id: ")
    delete_participant_score(par_l, id_number)
  elif cmd == "del_int_id":
    id_interval = input("id interval: ")
    delete_participant_interval_score(par_l, id_interval)
  elif cmd == "replace_id":
    id_number = input("id: ")
    score_l = input("scores: ")
    replace_participant_score(par_l, id_number, score_l, max_scores)
  else:
    print("invalid command!")

def delete_participant_score_by_id_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10], compute_average([1.6, 1.8, 1, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1], compute_average([6, 7.66, 9.9999, 1]))
  participants.add_participant_in_list(par_l, participant)
  delete_participant_score_by_id(par_l, 1)

  assert len(par_l) == 3
  assert par_l == [{'id': 0, 'score': [1, 6, 9, 10], 'score_avg': 6.5}, {'id': 1, 'score': [], 'score_avg': 0}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': 6.164975}]

  delete_participant_score_by_id(par_l, 0)
  assert par_l == [{'id': 0, 'score': [], 'score_avg': 0}, {'id': 1, 'score': [], 'score_avg': 0}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': 6.164975}]


def delete_participant_score_by_id_interval_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [5], compute_average([5]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [9], compute_average([9]))

  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(3, [5, 6], compute_average([5, 6]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(4, [1, 6.77, 4, 7, 7, 9], compute_average([1, 6.77, 4, 7, 7, 9]))
  participants.add_participant_in_list(par_l, participant)

  delete_participant_score_by_id_interval(par_l, [1, 3])
  assert par_l == [{'id': 0, 'score': [1, 6, 9, 10], 'score_avg': compute_average([1, 6, 9, 10])}, {'id': 1, 'score' : [], 'score_avg': 0}, {'id': 2, 'score' : [], 'score_avg': 0}, {'id': 3, 'score' : [], 'score_avg': 0}, {'id': 4, 'score': [1, 6.77, 4, 7, 7, 9], 'score_avg': compute_average([1, 6.77, 4, 7, 7, 9])}]

def replace_participant_score_by_id_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10], compute_average([1.6, 1.8, 1, 10]))
  participants.add_participant_in_list(par_l, participant) 
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1], compute_average([6, 7.66, 9.9999, 1]))
  participants.add_participant_in_list(par_l, participant)

  replace_participant_score_by_id(par_l, 0, [1, 1])
  assert par_l == [{'id': 0, 'score' : [1, 1], 'score_avg': compute_average([1, 1])}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg' : compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': compute_average([6, 7.66, 9.9999, 1])}]

  replace_participant_score_by_id(par_l, 2, [1, 6])
  assert par_l == [{'id': 0, 'score' : [1, 1], 'score_avg': compute_average([1, 1])}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg' : compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [1, 6], 'score_avg': compute_average([1, 6])}

]

def delete_participant_score_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10], compute_average([1.6, 1.8, 1, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1], compute_average([6, 7.66, 9.9999, 1]))
  participants.add_participant_in_list(par_l, participant)

  delete_participant_score(par_l, 0)
  assert len(par_l) == 3
  assert par_l == [{'id': 0, 'score' : [], 'score_avg': 0}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg' : compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': compute_average([6, 7.66, 9.9999, 1])}]

  try:
    delete_participant_score(par_l, 4)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

def delete_participant_interval_score_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10], compute_average([1.6, 1.8, 1, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1], compute_average([6, 7.66, 9.9999, 1]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(3, [6], compute_average([6]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(4, [7], compute_average([7]))
  participants.add_participant_in_list(par_l, participant)

  delete_participant_interval_score(par_l, "0 2")
  assert len(par_l) == 5
  assert par_l == [{'id': 0, 'score': [], 'score_avg': 0}, {'id': 1, 'score': [], 'score_avg': 0}, {'id': 2, 'score': [], 'score_avg': 0}, {'id': 3, 'score': [6], 'score_avg': 6}, {'id': 4, 'score': [7], 'score_avg': 7}]

  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10], compute_average([1.6, 1.8, 1, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1], compute_average([6, 7.66, 9.9999, 1]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(3, [6], compute_average([6]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(4, [7], compute_average([7]))
  participants.add_participant_in_list(par_l, participant)



  delete_participant_interval_score(par_l, "0 0")
  assert len(par_l) == 5
  assert par_l == [{'id': 0, 'score': [], 'score_avg': 0}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg': compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': compute_average([6, 7.66, 9.9999, 1])}, {'id': 3, 'score': [6], 'score_avg': 6}, {'id': 4, 'score': [7], 'score_avg': 7}]

  try:
    delete_participant_interval_score(par_l, "0 10")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

def replace_participant_score_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10], compute_average([1.6, 1.8, 1, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1], compute_average([6, 7.66, 9.9999, 1]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(3, [6], compute_average([6]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(4, [7], compute_average([7]))
  participants.add_participant_in_list(par_l, participant)

  replace_participant_score(par_l, 0, "1", 10)
  assert par_l == [{'id': 0, 'score': [1], 'score_avg': 1}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg': compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': compute_average([6, 7.66, 9.9999, 1])}, {'id': 3, 'score': [6], 'score_avg': 6}, {'id': 4, 'score': [7], 'score_avg': 7}]

  replace_participant_score(par_l, 4, "1 5", 10)
  assert par_l == [{'id': 0, 'score': [1], 'score_avg': 1}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg': compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': compute_average([6, 7.66, 9.9999, 1])}, {'id': 3, 'score': [6], 'score_avg': 6}, {'id': 4, 'score': [1, 5], 'score_avg': compute_average([1, 5])}]

  

delete_participant_score_by_id_test()
delete_participant_score_by_id_interval_test()
replace_participant_score_by_id_test()
delete_participant_score_test()
delete_participant_interval_score_test()
replace_participant_score_test()
