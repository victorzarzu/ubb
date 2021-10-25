from presentation.ui_add import ui_add_score
from modify import ui_modify_score
#from print import ui_print_score
from filter import ui_filter_score
from operate import ui_operate_score

import domain.participants as participants
import infrastructure.comparators as comparators
import infrastructure.conversions as conversions
import validation.validations as validations
from infrastructure.computes import compute_average

def sort_participants_by_key_and_sort_mode(participants_stats, sort_key, sort_mode):
  """
  function that sorts a list of participants by sort_key and sort_mode
  params: participants_stats - a list of participant items; sort_key - a function; sort_mode - a string
  return: -
  """
  participants_stats.sort(key = sort_key, reverse = bool(sort_mode == "desc"))

def create_participants_list_that_satisfies_comparer(participants_stats, comparer, argument):
  """
  function that creates a list of participant items of participants that satisfies a comparer with a given argument
  params: participants_stats - a list of participant items; comparer - a function; argument - a float number
  return: a list of participant items
  """
  participants_ = []
  for participant in participants_stats:
    participant_score_avg = participants.get_participant_score_avg(participant)
    if comparer(participant_score_avg, argument):
      participants.add_participant_in_list(participants_, participant)

  return participants_

def create_string_for_print(participants_stats):
  """
  function that creates a string to be printed for a given participant items list
  params: participants_stats - a list of participant items
  return: a string
  """
  stats = ""
  for participant in participants_stats:
    stats += participants.participant_to_str(participant) 
  stats = stats[:-1]
  return stats

def svg_create_participants_stats_by_comparer(participants_stats, comparer, max_score):
  """
  function that returns a list of participant items with a score smaller than max_score
  params: participants_stats - a list of participant items; max_score - a float
  return: a list of participant items
  """
  participants_ = []
  max_score = conversions.convert_score(max_score)
  validations.validate_score(max_score)
  participants_ = create_participants_list_that_satisfies_comparer(participants_stats, comparer, max_score)
  return participants_

def svg_sort_participants_stats_by_sort_mode(participants_stats, sort_key, sort_mode):
  """
  function that returns a list of participant items sorted in sort_mode mode
  params: participants_stats - a list of participant items; sort_mode - a string
  return: a list of participant items
  """
  validations.validate_sort_mode(sort_mode)
  sort_participants_by_key_and_sort_mode(participants_stats, sort_key, sort_mode)
  

def sort_participants_by_key_and_sort_mode_test():
  participants_stats = []
  participant = participants.create_participant(0, [1, 2, 3], 2)
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(1, [5, 6, 7], compute_average([5, 6, 7]))
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(2, [9, 8, 9], compute_average([9, 8, 9]))
  participants.add_participant_in_list(participants_stats, participant)

  sort_participants_by_key_and_sort_mode(participants_stats, participants.get_participant_score_avg, "asc")
  assert participants_stats == [{'id': 0, 'score': [1, 2, 3], 'score_avg': 2}, {'id': 1, 'score': [5, 6, 7], 'score_avg': compute_average([5, 6, 7])}, {'id': 2, 'score': [9, 8, 9], 'score_avg': compute_average([9, 8, 9])}]

  sort_participants_by_key_and_sort_mode(participants_stats, participants.get_participant_score_avg, "desc")
  assert participants_stats == [{'id': 2, 'score': [9, 8, 9], 'score_avg': compute_average([9, 8, 9])}, {'id': 1, 'score': [5, 6, 7], 'score_avg': compute_average([5, 6, 7])}, {'id': 0, 'score': [1, 2, 3], 'score_avg': 2}]

def create_participants_list_that_satisfies_comparer_test():
  participants_stats = []
  participant = participants.create_participant(0, [1, 2, 3], 2)
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(1, [5, 6, 7], compute_average([5, 6, 7]))
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(2, [9, 8, 9], compute_average([9, 8, 9]))
  participants.add_participant_in_list(participants_stats, participant)
  
  participants_ = create_participants_list_that_satisfies_comparer(participants_stats, comparators.comparer_smaller, 8)
  assert participants_ == [{'id': 0, 'score': [1, 2, 3], 'score_avg': 2}, {'id': 1, 'score': [5, 6, 7], 'score_avg': compute_average([5, 6, 7])}]
  
  participants_ = create_participants_list_that_satisfies_comparer(participants_stats, comparators.comparer_bigger, 7)
  assert participants_ == [{'id': 2, 'score': [9, 8, 9], 'score_avg': compute_average([9, 8, 9])}]

def create_string_for_print_test():
  participants_stats = []
  participant = participants.create_participant(0, [1, 2, 3], 2)
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(1, [5, 6, 7], compute_average([5, 6, 7]))
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(2, [9, 8, 9], compute_average([9, 8, 9]))
  participants.add_participant_in_list(participants_stats, participant)
  stats = create_string_for_print(participants_stats)

  assert stats == "id: 0\nscore: 2.00\nid: 1\nscore: 6.00\nid: 2\nscore: 8.67"

def svg_create_participants_stats_by_comparer_test():
  participants_stats = []
  participant = participants.create_participant(0, [1, 2, 3], 2)
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(1, [5, 6, 7], compute_average([5, 6, 7]))
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(2, [9, 8, 9], compute_average([9, 8, 9]))
  participants.add_participant_in_list(participants_stats, participant)

  participants_ = svg_create_participants_stats_by_comparer(participants_stats, comparators.comparer_smaller, "8")
  assert participants_ == [{'id': 0, 'score': [1, 2, 3], 'score_avg': 2}, {'id': 1, 'score': [5, 6, 7], 'score_avg': compute_average([5, 6, 7])}]

  participants_ = svg_create_participants_stats_by_comparer(participants_, comparators.comparer_bigger, "9.8")
  assert participants_ == []

def svg_sort_participants_stats_by_sort_mode_test():
  participants_stats = []
  participant = participants.create_participant(0, [1, 2, 3], 2)
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(1, [5, 6, 7], compute_average([5, 6, 7]))
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(2, [9, 8, 9], compute_average([9, 8, 9]))
  participants.add_participant_in_list(participants_stats, participant)

  svg_sort_participants_stats_by_sort_mode(participants_stats, participants.get_participant_score_avg, "asc")
  assert participants_stats == [{'id': 0, 'score': [1, 2, 3], 'score_avg': 2}, {'id': 1, 'score': [5, 6, 7], 'score_avg': compute_average([5, 6, 7])}, {'id': 2, 'score': [9, 8, 9], 'score_avg': compute_average([9, 8, 9])}]

  svg_sort_participants_stats_by_sort_mode(participants_stats, participants.get_participant_score_avg, "desc")
  assert participants_stats == [{'id': 2, 'score': [9, 8, 9], 'score_avg': compute_average([9, 8, 9])}, {'id': 1, 'score': [5, 6, 7], 'score_avg': compute_average([5, 6, 7])}, {'id': 0, 'score': [1, 2, 3], 'score_avg': 2}]


sort_participants_by_key_and_sort_mode_test()
create_participants_list_that_satisfies_comparer_test()
create_string_for_print_test()
svg_create_participants_stats_by_comparer_test()
svg_sort_participants_stats_by_sort_mode_test()

def ui_print_score(par_l):
  participants_stats = par_l[:]
  cmd = input().lstrip().rstrip()
  try:
    if cmd == "print_1":
      max_score = input("smaller than: ")
      participants_ = svg_create_participants_stats_by_comparer(participants_stats, comparators.comparer_smaller, max_score)
      stats = create_string_for_print(participants_)
      print(stats)
    elif cmd == "print_2":
      sort_mode = input("asc or desc: ")
      svg_sort_participants_stats_by_sort_mode(participants_stats, participants.get_participant_score_avg, sort_mode) 
      stats = create_string_for_print(participants_stats)
      print(stats)
    elif cmd == "print_3":
      min_score = input("bigger than: ")
      sort_mode = input("asc or desc: ")
      participants_ = svg_create_participants_stats_by_comparer(participants_stats, comparators.comparer_bigger, min_score)
      svg_sort_participants_stats_by_sort_mode(participants_, participants.get_participant_score_avg, sort_mode) 
      stats = create_string_for_print(participants_)
      print(stats)
    else:
      print("invalid command!")
  except Exception as ex:
    print(ex)
  pass

def ui():
  par_l = []
  max_scores = 10
  while True:
    cmd = input().rstrip().lstrip()
    if cmd == "exit":
      break
    if cmd == "1":
      try:
        ui_add_score(par_l, max_scores)
      except Exception as ex:
        print(ex)
    elif cmd == "2":
      try:
        ui_modify_score(par_l, max_scores)
      except Exception as ex:
        print(ex)
    elif cmd == "3":
      try:
        ui_print_score(par_l)
      except Exception as ex:
        print(ex)
    elif cmd == "4":
      try:
        ui_operate_score(par_l)
      except Exception as ex:
        print(ex)
    elif cmd == "5":
      try:
        ui_filter_score(par_l)
      except Exception as ex:
        print(ex)
    else:
      print("invalid command!")

def main():
  ui()


main()
