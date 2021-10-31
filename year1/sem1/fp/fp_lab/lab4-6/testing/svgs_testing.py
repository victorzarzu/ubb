import inspect
from infrastructure.conversions import convert_score_list, convert_id_number
from validation.validations import validate_score_list, validate_participant_id_number, validate_score_list
import domain.participants as participants
from infrastructure.computes import compute_average
import infrastructure.comparators as comparators
import infrastructure.lists as lists
from business.svgs_add import svg_add_score, svg_insert_score
from business.svgs_filter import svg_filter_smaller_than, svg_filter_divisible_with
from business.svgs_modify import svg_delete_participant_score, svg_delete_participant_interval_score, svg_replace_participant_score
from business.svgs_operate import svg_participants_average_by_id_interval, svg_minimum_score_by_interval, svg_participant_ids_if_multiple
from business.svgs_print import svg_create_participants_stats_by_comparer, svg_sort_participants_stats_by_sort_mode
from infrastructure.constants import oo, epsilon

def svg_add_score_test():
  par_l = []
  undo_stage = []
  svg_add_score(par_l, "9.8 1 5 1.4", 10, undo_stage)
  assert len(par_l) == 1

  svg_add_score(par_l, "9 1 8 10", 10, undo_stage)

  participant = participants.get_participant_by_id(par_l, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9.8, 1, 5, 1.4]

  participant = participants.get_participant_by_id(par_l, 1)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9, 1, 8, 10]

  try:
    svg_add_score(par_l, "1 1 1 1 1 1 11 1 1 1 11 1 1 ", 10, undo_stage)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!"

  try:
    svg_add_score(par_l, "9.6 1 1 / 6 7", 10, undo_stage)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid numbers!"

def svg_insert_score_test():
  par_l = []
  undo_stage = []
  svg_add_score(par_l, "6 6 6 2 4 1", 10, undo_stage)
  svg_add_score(par_l, "6", 10, undo_stage)
  svg_add_score(par_l, "10 1.7 9.4", 10, undo_stage)
  svg_add_score(par_l, "9 9 2", 10, undo_stage)

  svg_insert_score(par_l, "5 6", 0, 10, undo_stage)
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [6, 6, 6, 2, 4, 1, 5, 6] 

  svg_insert_score(par_l, "10 10 10", 1, 10, undo_stage)
  participant = participants.get_participant_by_id(par_l, 1)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [6, 10, 10, 10] 
  
  try: 
    svg_insert_score(par_l, "1 1 1 1 1 1 1 1 6 7", 2, 10, undo_stage)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!" 

  try:
    svg_insert_score(par_l, "6 & 1 4", 3, 10, undo_stage)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid numbers!"

  try:
    svg_insert_score(par_l, "3 4", 6, 10, undo_stage)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"
    
def svg_filter_smaller_than_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 1, 1, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8])
  participants.add_participant_in_list(par_l, participant)

  svg_filter_smaller_than(par_l, 7.001, [])
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [oo]

  participant = participants.get_participant_by_id(par_l, 2)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [6, 7, 8]

  try:
    svg_filter_smaller_than(par_l, 10.7, [])
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!"

def svg_filter_divisible_with_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 1, 1, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8])
  participants.add_participant_in_list(par_l, participant)

  svg_filter_divisible_with(par_l, compute_average([8, 9, 9]) / 7, [])
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [8, 9, 9]
  
  participant = participants.get_participant_by_id(par_l, 1)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [oo]

  participant = participants.get_participant_by_id(par_l, 2)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [oo]

  try:
    svg_filter_divisible_with(par_l, 10.7, [])
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!"

def svg_delete_participant_score_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1])
  participants.add_participant_in_list(par_l, participant)

  svg_delete_participant_score(par_l, 0, [])
  assert len(par_l) == 3
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 0

  try:
    svg_delete_participant_score(par_l, 4, [])
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

def svg_delete_participant_interval_score_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(3, [6])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(4, [7])
  participants.add_participant_in_list(par_l, participant)

  svg_delete_participant_interval_score(par_l, "0 2", [])
  assert len(par_l) == 5
  
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 0
  
  participant = participants.get_participant_by_id(par_l, 1)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 0

  participant = participants.get_participant_by_id(par_l, 2)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 0

  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(3, [6])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(4, [7])
  participants.add_participant_in_list(par_l, participant)

  svg_delete_participant_interval_score(par_l, "0 0", [])
  assert len(par_l) == 5
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 0
  
  participant = participants.get_participant_by_id(par_l, 1)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg > 0

  try:
    svg_delete_participant_interval_score(par_l, "0 10", [])
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

def svg_replace_participant_score_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(3, [6])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(4, [7])
  participants.add_participant_in_list(par_l, participant)

  svg_replace_participant_score(par_l, 0, "1", 10, [])
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 1

  svg_replace_participant_score(par_l, 4, "1 5", 10, [])
  participant = participants.get_participant_by_id(par_l, 4)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [1, 5]

def svg_participants_average_by_id_interval_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 1, 1, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8])
  participants.add_participant_in_list(par_l, participant)
  average = svg_participants_average_by_id_interval(par_l, "0 1")
  assert average == compute_average([compute_average([8, 9, 9]), 1])


def svg_minimum_score_by_interval_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [5, 2, 4, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8])
  participants.add_participant_in_list(par_l, participant)
  minimum = svg_minimum_score_by_interval(par_l, "0 2")
  assert minimum == compute_average([5, 2, 4, 1])

  participant = participants.create_participant(len(par_l), [1, 2, 1])
  participants.add_participant_in_list(par_l, participant)
  minimum = svg_minimum_score_by_interval(par_l, "0 3")
  assert minimum == compute_average([1, 2, 1]) 

def svg_participant_ids_if_multiple_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [1, 2, 7])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [5, 2, 4, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8])
  participants.add_participant_in_list(par_l, participant)
  id_l = svg_participant_ids_if_multiple(par_l, "0 2", 10)
  assert id_l == "ids: 0"
  
  participant = participants.create_participant(len(par_l), [5, 7, 7])
  participants.add_participant_in_list(par_l, participant)
  id_l = svg_participant_ids_if_multiple(par_l, "1 3", 10)
  assert id_l == "no participants!" 

def svg_create_participants_stats_by_comparer_test():
  participants_stats = []
  participant = participants.create_participant(0, [1, 2, 3])
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(1, [5, 6, 7])
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(2, [9, 8, 9])
  participants.add_participant_in_list(participants_stats, participant)

  participants_ = svg_create_participants_stats_by_comparer(participants_stats, comparators.comparer_smaller, "8")

  assert len(participants_) == 2
  participant = participants.get_participant_by_id(participants_, 0)
  participant_id = participants.get_participant_id(participant)
  participant_score = participants.get_participant_score(participant)
  assert participant_id == 0
  assert participant_score == [1, 2, 3]

  participant = participants.get_participant_by_id(participants_, 1)
  participant_id = participants.get_participant_id(participant)
  participant_score = participants.get_participant_score(participant)
  assert participant_id == 1
  assert participant_score == [5, 6, 7]

  participants_ = svg_create_participants_stats_by_comparer(participants_, comparators.comparer_bigger, "9.8")
  assert participants_ == []

def svg_sort_participants_stats_by_sort_mode_test():
  participants_stats = []
  participant = participants.create_participant(0, [1, 2, 3])
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(1, [5, 6, 7])
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(2, [9, 8, 9])
  participants.add_participant_in_list(participants_stats, participant)

  svg_sort_participants_stats_by_sort_mode(participants_stats, participants.get_participant_score_avg, "asc")
  participant = participants.get_participant_by_id(participants_stats, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [1, 2, 3]

  participant = participants.get_participant_by_id(participants_stats, 1)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [5, 6, 7]

  participant = participants.get_participant_by_id(participants_stats, 2)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9, 8, 9]

  svg_sort_participants_stats_by_sort_mode(participants_stats, participants.get_participant_score_avg, "desc")

  participant = participants.get_participant_by_id(participants_stats, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9, 8, 9]

  participant = participants.get_participant_by_id(participants_stats, 1)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [5, 6, 7]

  participant = participants.get_participant_by_id(participants_stats, 2)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [1, 2, 3]

def run_svgs_tests():
  svg_add_score_test()
  svg_insert_score_test()
  svg_filter_smaller_than_test()   
  svg_filter_divisible_with_test()
  svg_delete_participant_score_test()
  svg_delete_participant_interval_score_test()
  svg_replace_participant_score_test()
  svg_participants_average_by_id_interval_test()
  svg_minimum_score_by_interval_test()
  svg_participant_ids_if_multiple_test()
  svg_create_participants_stats_by_comparer_test()
  svg_sort_participants_stats_by_sort_mode_test()
