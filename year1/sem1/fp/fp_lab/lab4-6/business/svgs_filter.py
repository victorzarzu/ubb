import domain.participants as participants
import infrastructure.comparators as comparators
from infrastructure.computes import compute_average
import infrastructure.conversions as conversions
import validation.validations as validations

oo = 0x3f3f3f3f

def svg_filter_smaller_than(par_l, max_score):
  """
  function that filters the participants with a score smaller than max_score
  params: par_l - a list of participants items; max_score - a float
  return: - 
  """
  max_score = conversions.convert_score(max_score)
  validations.validate_score(max_score)
  par_l = participants.filter_participants_by_comparer(par_l, comparators.comparer_smaller, max_score)

def svg_filter_divisible_with(par_l, div):
  """
  function that filters the participants with a score smaller than max_score
  params: par_l - a list of participants items; max_score - a float
  return: - 
  """
  div = conversions.convert_score(div)
  validations.validate_score(div)
  par_l = participants.filter_participants_by_comparer(par_l, comparators.comparer_divisible, div)


def svg_filter_smaller_than_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 1, 1, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8])
  participants.add_participant_in_list(par_l, participant)

  svg_filter_smaller_than(par_l, 7.001)
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [oo]

  participant = participants.get_participant_by_id(par_l, 2)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [6, 7, 8]

  try:
    svg_filter_smaller_than(par_l, 10.7)
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!"

def svg_filter_divisible_with_test():
  par_l = []
  participant = participants.create_participant(len(par_l), [8, 9, 9])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [1, 1, 1, 1])
  participants.add_participant_in_list(par_l, participant)
  participant = participants.create_participant(len(par_l), [6, 7, 8])
  participants.add_participant_in_list(par_l, participant)

  svg_filter_divisible_with(par_l, compute_average([8, 9, 9]) / 7)
  participant = participants.get_participant_by_id(par_l, 0)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [8, 9, 9]
  
  participant = participants.get_participant_by_id(par_l, 1)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [oo]

  participant = participants.get_participant_by_id(par_l, 2)
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [oo]

  try:
    svg_filter_divisible_with(par_l, 10.7)
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!"

svg_filter_smaller_than_test()   
svg_filter_divisible_with_test()
