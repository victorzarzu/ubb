from infrastructure.conversions import convert_score_list, convert_id_number
from validation.validations import validate_score_list, validate_participant_id_number, validate_score_list
import domain.participants as participants
from infrastructure.computes import compute_average
import infrastructure.lists as lists
import domain.undos as undos

def svg_add_score(par_l, score_l, max_scores, undo_stage):
  """
  function that adds participant into par_l
  params: par_l - a list of participant items; score_l - a list of floats; undo_stage - a list of undo_opeartion items
  return: -, if it can add the list of scores
  """
  score_l = convert_score_list(score_l)
  validate_score_list(score_l, max_scores, max_scores)
  score_avg = compute_average(score_l)
  participant = participants.create_participant(len(par_l), score_l)

  undo_operation = undos.create_undo_operation(participants.remove_participant_from_list, [par_l])
  undos.add_undo_operation_in_undo_stage(undo_stage, undo_operation)
  participants.add_participant_in_list(par_l, participant)

def svg_insert_score(par_l, score_l, id_number, max_scores, undo_stage):
  """
  function that adds a list of scores from scor_l into a list into par_l coresponding to the id_number-th participant
  params: par_l - a list of participant items; score_l - a list  of floats; id_number - a string; max_scores - an integer; undo_stage - a list of undo_opeartion items
  return: -
  """
  id_number = convert_id_number(id_number)
  validate_participant_id_number(par_l, id_number)
  score_l = convert_score_list(score_l)
  max_scores_add = lists.get_free_space_by_participant_id(par_l, id_number, max_scores)
  validate_score_list(score_l, max_scores_add, max_scores)

  participants.insert_score_by_participant_id(par_l, id_number, score_l, undo_stage)
