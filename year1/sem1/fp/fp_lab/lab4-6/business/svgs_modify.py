from infrastructure.conversions import convert_id_number, convert_id_interval, convert_score_list
from validation.validations import validate_participant_id_number, validate_participant_id_interval, validate_score_list
from infrastructure.computes import compute_average
import domain.participants as participants

def svg_delete_participant_score(par_l, id_number):
  """
  function that deletes the score of the id_number-th
  params: par_l - a list of lists of integers; id_number - a string
  return: -
  """
  id_number = convert_id_number(id_number)
  validate_participant_id_number(par_l, id_number)
  participants.delete_participant_score_by_id(par_l, id_number)

def svg_delete_participant_interval_score(par_l, id_interval):  
  """
  function that deletes the score of the concurents that have and id in id_interval 
  params: par_l - a list of lists of integers; id_number - a string
  return: -
  """
  id_interval = convert_id_interval(id_interval)
  validate_participant_id_interval(par_l, id_interval)
  participants.delete_participant_score_by_id_interval(par_l, id_interval)

def svg_replace_participant_score(par_l, id_number, score_l, max_scores):
  """
  function that replaces the list of index id_number in the par_l list with score_l list
  params: par_l - a list of lists of integers; id_number - an integer; score_l - a list of floats
  return: -
  """
  id_number = convert_id_number(id_number)
  validate_participant_id_number(par_l, id_number)
  score_l = convert_score_list(score_l)
  validate_score_list(score_l, max_scores, max_scores)
  participants.replace_participant_score_by_id(par_l, id_number, score_l)

def svg_delete_participant_score_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10], compute_average([1.6, 1.8, 1, 10]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1], compute_average([6, 7.66, 9.9999, 1]))
  participants.add_participant_in_list(par_l, participant)

  svg_delete_participant_score(par_l, 0)
  assert len(par_l) == 3
  assert par_l == [{'id': 0, 'score' : [], 'score_avg': 0}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg' : compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': compute_average([6, 7.66, 9.9999, 1])}]

  try:
    svg_delete_participant_score(par_l, 4)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

def svg_delete_participant_interval_score_test():
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

  svg_delete_participant_interval_score(par_l, "0 2")
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

  svg_delete_participant_interval_score(par_l, "0 0")
  assert len(par_l) == 5
  assert par_l == [{'id': 0, 'score': [], 'score_avg': 0}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg': compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': compute_average([6, 7.66, 9.9999, 1])}, {'id': 3, 'score': [6], 'score_avg': 6}, {'id': 4, 'score': [7], 'score_avg': 7}]

  try:
    svg_delete_participant_interval_score(par_l, "0 10")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

def svg_replace_participant_score_test():
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

  svg_replace_participant_score(par_l, 0, "1", 10)
  assert par_l == [{'id': 0, 'score': [1], 'score_avg': 1}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg': compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': compute_average([6, 7.66, 9.9999, 1])}, {'id': 3, 'score': [6], 'score_avg': 6}, {'id': 4, 'score': [7], 'score_avg': 7}]

  svg_replace_participant_score(par_l, 4, "1 5", 10)
  assert par_l == [{'id': 0, 'score': [1], 'score_avg': 1}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg': compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': compute_average([6, 7.66, 9.9999, 1])}, {'id': 3, 'score': [6], 'score_avg': 6}, {'id': 4, 'score': [1, 5], 'score_avg': compute_average([1, 5])}]

  

svg_delete_participant_score_test()
svg_delete_participant_interval_score_test()
svg_replace_participant_score_test()

