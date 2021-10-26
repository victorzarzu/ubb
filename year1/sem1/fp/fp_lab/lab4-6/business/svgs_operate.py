import domain.participants as participants
import infrastructure.comparators as comparators
from infrastructure.computes import compute_average
from infrastructure.conversions import convert_id_interval
from validation.validations import validate_participant_id_interval
import infrastructure.lists as lists
import infrastructure.strings as strings


def svg_participants_average_by_id_interval(par_l, id_interval):
  """
  function that computes the average of the average scores of all participants in the inverval
  params: par_l - a list of participant items; interval - a string
  return: a float representing the average of the average scores of the participants in the given interval
  """
  id_interval = convert_id_interval(id_interval) 
  validate_participant_id_interval(par_l, id_interval)
  average_list = lists.create_participant_score_avg_list_by_interval(par_l, id_interval)
  average = compute_average(average_list)
  return average

def svg_minimum_score_by_interval(par_l, id_interval):
  """
  function that computes the minimum of the average scores of all participants in the inverval
  params: par_l - a list of participant items; interval - a string
  return: a float representing the minimum of the average scores of the participants in the given interval
  """
  id_interval = convert_id_interval(id_interval) 
  validate_participant_id_interval(par_l, id_interval)
  minimum = lists.minimum_score_by_interval(par_l, id_interval)
  return minimum


def svg_participant_ids_if_multiple(par_l, id_interval, div):
  """
  function that computes the ids of the participants that have the score a multiple of div 
  params: par_l - a list of participant items; interval - a string; div - a float
  return: a string 
  """
  id_interval = convert_id_interval(id_interval) 
  validate_participant_id_interval(par_l, id_interval)
  id_l = lists.create_participant_id_list_if_multiple(par_l, id_interval, div)
  ids = strings.create_string_ids(id_l)
  return ids 

def svg_participants_average_by_id_interval_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9], compute_average([8, 9, 9]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 1, 1, 1], compute_average([1, 1, 1, 1]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
  participants.add_participant_in_list(par_l, participant)
  average = svg_participants_average_by_id_interval(par_l, "0 1")
  assert average == compute_average([compute_average([8, 9, 9]), 1])


def svg_minimum_score_by_interval_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9], compute_average([8, 9, 9]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [5, 2, 4, 1], compute_average([5, 2, 4, 1]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
  participants.add_participant_in_list(par_l, participant)
  minimum = svg_minimum_score_by_interval(par_l, "0 2")
  assert minimum == compute_average([5, 2, 4, 1])

  participant = participants.create_participant(len(par_l), [1, 2, 1], compute_average([1, 2, 1]))
  participants.add_participant_in_list(par_l, participant)
  minimum = svg_minimum_score_by_interval(par_l, "0 3")
  assert minimum == compute_average([1, 2, 1]) 

def svg_participant_ids_if_multiple_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [1, 2, 7], compute_average([1, 2, 7]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [5, 2, 4, 1], compute_average([5, 2, 4, 1]))
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
  participants.add_participant_in_list(par_l, participant)
  id_l = svg_participant_ids_if_multiple(par_l, "0 2", 10)
  assert id_l == "ids: 0"
  
  participant = participants.create_participant(len(par_l), [5, 7, 7], compute_average([5, 7, 7]))
  participants.add_participant_in_list(par_l, participant)
  id_l = svg_participant_ids_if_multiple(par_l, "1 3", 10)
  assert id_l == "no participants!" 
  
svg_participants_average_by_id_interval_test()
svg_minimum_score_by_interval_test()
svg_participant_ids_if_multiple_test()
