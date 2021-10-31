import domain.participants as participants
from infrastructure.computes import compute_average
from infrastructure.strings import create_string_for_print, create_string_ids

def create_string_for_print_test():
  participants_stats = []
  participant = participants.create_participant(0, [1, 2, 3])
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(1, [5, 6, 7])
  participants.add_participant_in_list(participants_stats, participant)
  participant = participants.create_participant(2, [9, 8, 9])
  participants.add_participant_in_list(participants_stats, participant)
  stats = create_string_for_print(participants_stats)

  assert stats == "id: 0\nscore: 2.00\nid: 1\nscore: 6.00\nid: 2\nscore: 8.67"

  participants_stats = []
  stats = create_string_for_print(participants_stats)
  assert stats == "no participants!"
  

def create_string_ids_test():
  id_l = [1, 7, 10, 20]
  ids = create_string_ids(id_l)
  assert ids == "ids: 1 7 10 20"
  

def run_strings_tests():
  create_string_for_print_test()
  create_string_ids_test()
