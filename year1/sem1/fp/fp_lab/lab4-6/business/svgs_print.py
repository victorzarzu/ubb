import domain.participants as participants
import infrastructure.comparators as comparators
import infrastructure.conversions as conversions
import validation.validations as validations
from infrastructure.computes import compute_average

import infrastructure.lists as lists

def svg_create_participants_stats_by_comparer(participants_stats, comparer, max_score):
  """
  function that returns a list of participant items with a score smaller than max_score
  params: participants_stats - a list of participant items; max_score - a float
  return: a list of participant items
  """
  participants_ = []
  max_score = conversions.convert_score(max_score)
  validations.validate_score(max_score)
  participants_ = lists.create_participants_list_that_satisfies_comparer(participants_stats, comparer, max_score)
  return participants_

def svg_sort_participants_stats_by_sort_mode(participants_stats, sort_key, sort_mode):
  """
  function that returns a list of participant items sorted in sort_mode mode
  params: participants_stats - a list of participant items; sort_mode - a string
  return: a list of participant items
  """
  validations.validate_sort_mode(sort_mode)
  lists.sort_participants_by_key_and_sort_mode(participants_stats, sort_key, sort_mode)
 # print(participants_stats)

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

svg_create_participants_stats_by_comparer_test()
svg_sort_participants_stats_by_sort_mode_test()
