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
 
def add_element_in_list(score_l, score):
  """
  function that adds score in score_l list
  params: score_l - a list of floats; score - a float
  return: -
  """
  score_l.append(score)

def create_participant_score_avg_list_by_interval(par_l, id_interval):
  """
  function that returns a list with the score averages of all participants
  params: par_l - a list of participant items; id_interval - a list of 2 integers
  return: a list of floats
  """
  average_list = []
  for i in range(id_interval[0], id_interval[1] + 1):
    participant_score_avg = participants.get_participant_score_avg(par_l[i])
    add_element_in_list(average_list, participant_score_avg)
  return average_list

def minimum_score_by_interval(par_l, id_interval):
  """
  function that returns the minimum average score of a participant in a given interval of ids
  params: par_l - a list of participant items; interval - a list of 2 intergers
  return: a float
  """
  minimum = 11
  for i in range(id_interval[0], id_interval[1] + 1):
    participant_average_score = participants.get_participant_score_avg(par_l[i])
    if comparators.comparer_smaller(participant_average_score, minimum):
      minimum = participant_average_score
  return minimum

def get_free_space_by_participant_id(par_l, id_number, max_scores):
  """
  function that returns the number of scores that can be inserted for the id_number-th participant
  params: par_l - a list of participant items; id_number - an integer; max_scores - an integer
  return: an integer representig the number of scores that can be inserted for the id_number-th participant
  """
  participant = participants.get_participant_by_id(par_l, id_number)
  score_l = participants.get_participant_score(participant)
  return max_scores - len(score_l)

def create_participant_id_list_if_multiple(par_l, id_interval, div):
  """
  function that creates a list of integers that are the ids of the participant that a score a multiple of div
  params: par_l - a list of participant items; id_interval - a list of 2 integers; div: a float value
  """
  id_l = []
  for i in range(id_interval[0], id_interval[1] + 1):
    participant_average_score = participants.get_participant_score_avg(par_l[i])
    participant_score = participants.get_participant_score(par_l[i])
    participant_average_score *= len(participant_score) 
    if comparators.comparer_divisible(participant_average_score, div):  
      participant_id = participants.get_participant_id(par_l[i])
      add_element_in_list(id_l, participant_id)
      
  return id_l
