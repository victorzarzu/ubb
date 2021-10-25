import domain.participants as participants
import infrastructure.comparators as comparators
from infrastructure.computes import compute_average
import infrastructure.conversions as conversions
import validation.validations as validations

oo = 0x3f3f3f3f

def filter_participants_by_comparer(par_l, comparer, argument):
  """
  function that modifies par_l filtering participants with a score that satisfies the comparer
  params: par_l - a list of participant items; comparer - a comparer function; argument - a float number 
  return: -  
  """
  for participant in par_l:
    participant_score_avg = participants.get_participant_score_avg(participant)
    participant_id = participants.get_participant_id(participant)
    if not comparer(participant_score_avg, argument):
      participant_modify = participants.create_participant(participant_id, [], oo)
      participants.change_participant_by_id(par_l, participant_id, participant_modify)


def filter_smaller_than(par_l, max_score):
  """
  function that filters the participants with a score smaller than max_score
  params: par_l - a list of participants items; max_score - a float
  return: - 
  """
  max_score = conversions.convert_score(max_score)
  validations.validate_score(max_score)
  par_l = filter_participants_by_comparer(par_l, comparators.comparer_smaller, max_score)

def filter_divisible_with(par_l, div):
  """
  function that filters the participants with a score smaller than max_score
  params: par_l - a list of participants items; max_score - a float
  return: - 
  """
  div = conversions.convert_score(div)
  validations.validate_score(div)
  par_l = filter_participants_by_comparer(par_l, comparators.comparer_divisible, div)

def filter_participants_by_comparer_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9], compute_average([8, 9, 9]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 1, 1, 1], compute_average([1, 1, 1, 1]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
  participants.add_participant_in_list(par_l, participant)
  filter_participants_by_comparer(par_l, comparators.comparer_smaller, 7.001)
  assert par_l == [{'id': 0, 'score': [], 'score_avg': oo}, {'id': 1, 'score': [1, 1, 1, 1], 'score_avg': 1}, {'id': 2, 'score': [6, 7, 8], 'score_avg': 7}]
  filter_participants_by_comparer(par_l, comparators.comparer_divisible, compute_average([8, 9, 9]) / 7)
  assert par_l == [{'id': 0, 'score': [], 'score_avg': oo}, {'id': 1, 'score': [], 'score_avg': oo}, {'id': 2, 'score': [], 'score_avg': oo}]


def filter_smaller_than_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9], compute_average([8, 9, 9]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 1, 1, 1], compute_average([1, 1, 1, 1]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
  participants.add_participant_in_list(par_l, participant)
  filter_smaller_than(par_l, 7.001)
  assert par_l == [{'id': 0, 'score': [], 'score_avg': oo}, {'id': 1, 'score': [1, 1, 1, 1], 'score_avg': compute_average([1, 1, 1, 1])}, {'id': 2, 'score': [6, 7, 8], 'score_avg': compute_average([6, 7, 8])}]

  try:
    filter_smaller_than(par_l, 10.7)
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!"

def filter_divisible_with_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9], compute_average([8, 9, 9]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 1, 1, 1], compute_average([1, 1, 1, 1]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
  participants.add_participant_in_list(par_l, participant)
  filter_divisible_with(par_l, compute_average([8, 9, 9]) / 7)
  assert par_l == [{'id': 0, 'score': [8, 9, 9], 'score_avg': compute_average([8, 9, 9])}, {'id': 1, 'score': [], 'score_avg': oo}, {'id': 2, 'score': [], 'score_avg': oo}]

  try:
    filter_divisible_with(par_l, 10.7)
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!"

def ui_filter_score(par_l):
  cmd = input().lstrip().rstrip()
  if cmd == "filter_1":
    div = input("divisible with: ")
    filter_divisible_with(par_l, div)
  elif cmd == "filter_2":
    max_score = input("smaller than: ")
    filter_smaller_than(par_l, max_score)
  else:
    print("invalid command!")
 
filter_participants_by_comparer_test()
filter_smaller_than_test()   
filter_divisible_with_test()
