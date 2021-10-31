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
