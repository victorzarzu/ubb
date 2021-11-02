import domain.participants as participants
import infrastructure.comparators as comparators
from infrastructure.computes import compute_average
import infrastructure.conversions as conversions
import validation.validations as validations
from infrastructure.constants import oo

def svg_filter_smaller_than(par_l, max_score, undo_stage):
  """
  function that filters the participants with a score smaller than max_score
  params: par_l - a list of participants items; max_score - a float; undo_stage - a list of undo_operation items
  return: - 
  """
  max_score = conversions.convert_score(max_score)
  validations.validate_score(max_score)
  par_l = participants.filter_participants_by_comparer(par_l, comparators.comparer_smaller, max_score, undo_stage)

def svg_filter_divisible_with(par_l, div, undo_stage):
  """
  function that filters the participants with a score smaller than max_score
  params: par_l - a list of participants items; max_score - a float;undo_stage - a list of undo_operation items
  return: - 
  """
  div = conversions.convert_score(div)
  validations.validate_score(div)
  par_l = participants.filter_participants_by_comparer(par_l, comparators.comparer_divisible, div, undo_stage)
