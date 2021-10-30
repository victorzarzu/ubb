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

def svg_delete_participant_score_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1])
  participants.add_participant_in_list(par_l, participant)

  svg_delete_participant_score(par_l, 0, [])
  assert len(par_l) == 3
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 0

  try:
    svg_delete_participant_score(par_l, 4, [])
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

def svg_delete_participant_interval_score_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(3, [6])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(4, [7])
  participants.add_participant_in_list(par_l, participant)

  svg_delete_participant_interval_score(par_l, "0 2", [])
  assert len(par_l) == 5
  
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 0
  
  participant = participants.get_participant_by_id(par_l, 1)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 0

  participant = participants.get_participant_by_id(par_l, 2)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 0

  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(3, [6])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(4, [7])
  participants.add_participant_in_list(par_l, participant)

  svg_delete_participant_interval_score(par_l, "0 0", [])
  assert len(par_l) == 5
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 0
  
  participant = participants.get_participant_by_id(par_l, 1)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg > 0

  try:
    svg_delete_participant_interval_score(par_l, "0 10", [])
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

def svg_replace_participant_score_test():
  par_l = []
  participant = participants.create_participant(0, [1, 6, 9, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(1, [1.6, 1.8, 1, 10])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(2, [6, 7.66, 9.9999, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(3, [6])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(4, [7])
  participants.add_participant_in_list(par_l, participant)

  svg_replace_participant_score(par_l, 0, "1", 10, [])
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score_avg = participants.get_participant_score_avg(participant)
  assert participant_score_avg == 1

  svg_replace_participant_score(par_l, 4, "1 5", 10, [])
  participant = participants.get_participant_by_id(par_l, 4)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [1, 5]

svg_delete_participant_score_test()
svg_delete_participant_interval_score_test()
svg_replace_participant_score_test()

