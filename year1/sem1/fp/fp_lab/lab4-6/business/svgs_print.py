import domain.participants as participants
import infrastructure.comparators as comparators
import infrastructure.conversions as conversions
import validation.validations as validations
from infrastructure.computes import compute_average
import infrastructure.lists as lists

def svg_create_participants_stats_by_comparer(participants_stats, comparer, max_score):
  """
  function that returns a list of participant items with a score smaller than max_score
  params: participants_stats - a list of participant items;comparer - a function; max_score - a float
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
  params: participants_stats - a list of participant items; sort_key - a function; sort_mode - a string
  return: a list of participant items
  """
  validations.validate_sort_mode(sort_mode)
  lists.sort_participants_by_key_and_sort_mode(participants_stats, sort_key, sort_mode)
