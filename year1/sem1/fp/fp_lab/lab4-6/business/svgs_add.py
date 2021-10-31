from infrastructure.conversions import convert_score_list, convert_id_number
from validation.validations import validate_score_list, validate_participant_id_number, validate_score_list
import domain.participants as participants
from infrastructure.computes import compute_average
import infrastructure.lists as lists
import domain.undos as undos

def svg_add_score(par_l, score_l, max_scores, undo_stage):
  """
  function that adds participant into par_l
  params: par_l - a list of participant items; score_l - a list of floats
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
  params: par_l - a list of participant items; score_l - a list  of floats; id_number - a string; max_scores - an integer
  """
  id_number = convert_id_number(id_number)
  validate_participant_id_number(par_l, id_number)
  score_l = convert_score_list(score_l)
  max_scores_add = lists.get_free_space_by_participant_id(par_l, id_number, max_scores)
  validate_score_list(score_l, max_scores_add, max_scores)

  participants.insert_score_by_participant_id(par_l, id_number, score_l, undo_stage)

def svg_add_score_test():
  par_l = []
  undo_stage = []
  svg_add_score(par_l, "9.8 1 5 1.4", 10, undo_stage)
  assert len(par_l) == 1

  svg_add_score(par_l, "9 1 8 10", 10, undo_stage)

  participant = participants.get_participant_by_id(par_l, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9.8, 1, 5, 1.4]

  participant = participants.get_participant_by_id(par_l, 1)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9, 1, 8, 10]

  try:
    svg_add_score(par_l, "1 1 1 1 1 1 11 1 1 1 11 1 1 ", 10, undo_stage)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!"

  try:
    svg_add_score(par_l, "9.6 1 1 / 6 7", 10, undo_stage)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid numbers!"

