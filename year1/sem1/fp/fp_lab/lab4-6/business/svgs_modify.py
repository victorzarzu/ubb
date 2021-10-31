from infrastructure.conversions import convert_id_number, convert_id_interval, convert_score_list
from validation.validations import validate_participant_id_number, validate_participant_id_interval, validate_score_list
from infrastructure.computes import compute_average
import domain.participants as participants

def svg_delete_participant_score(par_l, id_number, undo_stage):
  """
  function that deletes the score of the id_number-th
  params: par_l - a list of lists of integers; id_number - a string; undo_stage - a list of undo_operation items
  return: -
  """
  id_number = convert_id_number(id_number)
  validate_participant_id_number(par_l, id_number)
  participants.delete_participant_score_by_id(par_l, id_number, undo_stage)

def svg_delete_participant_interval_score(par_l, id_interval, undo_stage):  
  """
  function that deletes the score of the concurents that have and id in id_interval 
  params: par_l - a list of lists of integers; id_number - a string; undo_stage - a list of undo_operation items
  return: -
  """
  id_interval = convert_id_interval(id_interval)
  validate_participant_id_interval(par_l, id_interval)
  participants.delete_participant_score_by_id_interval(par_l, id_interval, undo_stage)

def svg_replace_participant_score(par_l, id_number, score_l, max_scores, undo_stage):
  """
  function that replaces the list of index id_number in the par_l list with score_l list
  params: par_l - a list of lists of integers; id_number - an integer; score_l - a list of floatsmax_scores - a float; undo_stage - a list of undo_operation items
  return: -
  """
  id_number = convert_id_number(id_number)
  validate_participant_id_number(par_l, id_number)
  score_l = convert_score_list(score_l)
  validate_score_list(score_l, max_scores, max_scores)
  participants.replace_participant_score_by_id(par_l, id_number, score_l, undo_stage)
