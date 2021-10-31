from validation.validations import validate_score_list_by_len, validate_score_list_by_values, validate_participant_id_number, validate_participant_id_interval, validate_score_list, validate_score, validate_sort_mode

def validate_score_list_by_len_test():
  score_l = [1, 5, 7, 9, 10]
  validate_score_list_by_len(score_l, 10, 10)

  score_l = [1, 2, 3, 3, 3, 3, 3, 3, 10, 11, 11]
  try:
    validate_score_list_by_len(score_l, 10, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!"


def validate_score_list_by_values_test():
  score_l = [1, 6, 10, 8]
  validate_score_list_by_values(score_l)

  score_l = [1, 11.6, 7, 0]
  try:
    validate_score_list_by_values(score_l)
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!" 
 
def validate_participant_id_number_test():
  par_l = [[1], [2], [3], [6], [7], [9]]
  validate_participant_id_number(par_l, 4)

  try:
    validate_participant_id_number(par_l, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

  try:
    validate_participant_id_number(par_l, 4.5)
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

def validate_participant_id_interval_test():
  par_l = [[1], [2], [3], [6], [7], [9], [2, 5, 7], [10, 2, 7.8]]
  validate_participant_id_interval(par_l, [0, 2])

  try:
    validate_participant_id_interval(par_l, [-1, 3])
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

  try:
    validate_participant_id_interval(par_l, [0, 10])
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

def validate_score_list_test():
  score_l = [1, 6, 10, 8]
  validate_score_list(score_l, 10, 10)

  score_l = [1, 11.6, 7, 0]
  try:
    validate_score_list(score_l, 10, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!"  

  score_l = [1, 11, 3, 4, 4, 4, 4, 4, 4, 8, 8, 8]
  try:
    validate_score_list(score_l, 10, 10)
    assert False
  except Exception as ex:
    assert str(ex) == "too many scores trying to be added -> the maximum scores to be stored for a participant is 10!"

def validate_score_test():
  validate_score(1.5)

  try:
    validate_score(0.999999)
    assert False
  except Exception as ex:
    assert str(ex) == "scores must be between 1 and 10!"

def validate_sort_mode_test():
  validate_sort_mode("asc")
  validate_sort_mode("desc")

  try:
    validate_sort_mode("asc1")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid sort mode!"

def run_validations_tests():
  validate_score_list_by_values_test()
  validate_participant_id_number_test()
  validate_participant_id_interval_test()
  validate_score_list_test()
  validate_score_test()
  validate_sort_mode_test()
