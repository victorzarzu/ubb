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

  if stats == "":
    stats = "no participants!"

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
