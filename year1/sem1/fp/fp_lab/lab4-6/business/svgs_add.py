from infrastructure.conversions import convert_score_list, convert_id_number
from validation.validations import validate_score_list, validate_participant_id_number, validate_score_list
import domain.participants as participants
from infrastructure.computes import compute_average
import infrastructure.lists as lists

def svg_add_score(par_l, score_l, max_scores):
  """
  function that adds participant into par_l
  params: par_l - a list of participant items; score_l - a list of floats
  return: -, if it can add the list of scores
  """
  score_l = convert_score_list(score_l)
  validate_score_list(score_l, max_scores, max_scores)
  score_avg = compute_average(score_l)
  participant = participants.create_participant(len(par_l), score_l)
  participants.add_participant_in_list(par_l, participant)

def svg_insert_score(par_l, score_l, id_number, max_scores):
  """
  function that adds a list of scores from scor_l into a list into par_l coresponding to the id_number-th participant
  params: par_l - a list of participant items; score_l - a list  of floats; id_number - a string; max_scores - an integer
  """
  id_number = convert_id_number(id_number)
  validate_participant_id_number(par_l, id_number)
  score_l = convert_score_list(score_l)
  max_scores_add = lists.get_free_space_by_participant_id(par_l, id_number, max_scores)
  validate_score_list(score_l, max_scores_add, max_scores)
  participants.insert_score_by_participant_id(par_l, id_number, score_l)

def svg_add_score_test():
  par_l = []
  svg_add_score(par_l, "9.8 1 5 1.4", 10)
  assert len(par_l) == 1

  svg_add_score(par_l, "9 1 8 10", 10)

  participant = participants.get_participant_by_id(par_l, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9.8, 1, 5, 1.4]

  participant = participants.get_participant_by_id(par_l, 1)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [9, 1, 8, 10]

  try:
    svg_add_score(par_l, "1 1 1 1 1 1 11 1 1 1 11 1 1 ", 10)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!"

  try:
    svg_add_score(par_l, "9.6 1 1 / 6 7", 10)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid numbers!"

def svg_insert_score_test():
  par_l = []
  svg_add_score(par_l, "6 6 6 2 4 1", 10)
  svg_add_score(par_l, "6", 10)
  svg_add_score(par_l, "10 1.7 9.4", 10)
  svg_add_score(par_l, "9 9 2", 10)

  svg_insert_score(par_l, "5 6", 0, 10)
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [6, 6, 6, 2, 4, 1, 5, 6] 

  svg_insert_score(par_l, "10 10 10", 1, 10)
  participant = participants.get_participant_by_id(par_l, 1)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [6, 10, 10, 10] 
  
  try: 
    svg_insert_score(par_l, "1 1 1 1 1 1 1 1 6 7", 2, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!" 

  try:
    svg_insert_score(par_l, "6 & 1 4", 3, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid numbers!"

  try:
    svg_insert_score(par_l, "3 4", 6, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

svg_add_score_test()
svg_insert_score_test()
