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
  
sort_participants_by_key_and_sort_mode_test()
create_participants_list_that_satisfies_comparer_test()
