import domain.participants as participants
from infrastructure.computes import compute_average

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

def create_string_ids(id_l):
  """
  creates a string to be shown based on the id_l list
  params: id_l - a list  of intergers
  return: a string
  """
  if not len(id_l):
    return "no participants!"

  ids = "ids: "
  for _id in id_l:
    ids += str(_id) + " "
  ids = ids[:-1]
  return ids

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

def create_string_ids_test():
  id_l = [1, 7, 10, 20]
  ids = create_string_ids(id_l)
  assert ids == "ids: 1 7 10 20"

create_string_for_print_test()
create_string_ids_test()
