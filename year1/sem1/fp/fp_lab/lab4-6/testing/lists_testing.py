import domain.participants as participants
import infrastructure.comparators as comparators
import infrastructure.conversions as conversions
import validation.validations as validations
from infrastructure.computes import compute_average
from infrastructure.lists import sort_participants_by_key_and_sort_mode, create_participants_list_that_satisfies_comparer, add_element_in_list, create_participant_score_avg_list_by_interval, minimum_score_by_interval, get_free_space_by_participant_id, create_participant_id_list_if_multiple

def sort_participants_by_key_and_sort_mode_test():
  participants_stats = []
  participant = participants.create_participant(0, [1, 2, 3])
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(1, [5, 6, 7])
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(2, [9, 8, 9])
  participants.add_participant_in_list(participants_stats, participant)

  sort_participants_by_key_and_sort_mode(participants_stats, participants.get_participant_score_avg, "asc")

  participant = participants.get_participant_by_id(participants_stats, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [1, 2, 3]

  participant = participants.get_participant_by_id(participants_stats, 2)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9, 8, 9]

  sort_participants_by_key_and_sort_mode(participants_stats, participants.get_participant_score_avg, "desc")

  participant = participants.get_participant_by_id(participants_stats, 2)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [1, 2, 3]

  participant = participants.get_participant_by_id(participants_stats, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9, 8, 9]
 

def create_participants_list_that_satisfies_comparer_test():
  participants_stats = []
  participant = participants.create_participant(0, [1, 2, 3])
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(1, [5, 6, 7])
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(2, [9, 8, 9])
  participants.add_participant_in_list(participants_stats, participant)
  
  participants_ = create_participants_list_that_satisfies_comparer(participants_stats, comparators.comparer_smaller, 8)

  participant = participants.get_participant_by_id(participants_, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [1, 2, 3]

  participant = participants.get_participant_by_id(participants_, 1)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [5, 6, 7]
  
  participants_ = create_participants_list_that_satisfies_comparer(participants_stats, comparators.comparer_bigger, 7)

  participant = participants.get_participant_by_id(participants_, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9, 8, 9]

def add_element_in_list_test():
  score_l = []
  add_element_in_list(score_l, 6)
  add_element_in_list(score_l, 8)
  add_element_in_list(score_l, 1)
  assert score_l == [6, 8, 1]

def create_participant_score_avg_list_by_interval_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 1, 1, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8])
  participants.add_participant_in_list(par_l, participant)

  average_list = create_participant_score_avg_list_by_interval(par_l, [0, 2])
  assert average_list == [compute_average([8, 9, 9]), 1, 7]
  
  participant = participants.create_participant(len(par_l), [6, 6, 6, 7])
  participants.add_participant_in_list(par_l, participant)

def minimum_score_by_interval_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 2, 1, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8])
  participants.add_participant_in_list(par_l, participant)
  
  minimum = minimum_score_by_interval(par_l, [0, 2])
  assert minimum == compute_average([1, 2, 1, 1,])

def get_free_space_by_participant_id_test():
  par_l = []
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [5, 5, 5, 5, 7]))
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [9, 9.9, 9.423, 5, 1, 9]))
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [1, 2, 3, 4, 5, 999]))
  participants.add_participant_in_list(par_l, participants.create_participant(len(par_l), [1]))
  
def create_participant_id_list_if_multiple_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [1, 2, 7])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [5, 2, 4, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8])
  participants.add_participant_in_list(par_l, participant)
  id_l = create_participant_id_list_if_multiple(par_l, [0, 2], 10)
  assert id_l == [0]
  
  participant = participants.create_participant(len(par_l), [5, 7, 7])
  participants.add_participant_in_list(par_l, participant)
  id_l = create_participant_id_list_if_multiple(par_l, [1, 3], 10)
  assert id_l == []

def run_lists_tests():
  sort_participants_by_key_and_sort_mode_test()
  create_participants_list_that_satisfies_comparer_test()
  add_element_in_list_test()
  create_participant_score_avg_list_by_interval_test()
  minimum_score_by_interval_test()
  get_free_space_by_participant_id_test()
create_participant_id_list_if_multiple_test()
