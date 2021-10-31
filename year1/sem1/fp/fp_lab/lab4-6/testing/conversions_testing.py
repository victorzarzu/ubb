from infrastructure.conversions import convert_score_list, convert_id_number, convert_id_interval, convert_score

def convert_score_list_test():
  score_l = "1 5 6 7 9.6 1"
  score_l = convert_score_list(score_l)
  assert score_l == [1, 5, 6, 7, 9.6, 1]

  try:
    convert_score_list("5.7 1 * 9")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid numbers!"

def convert_id_number_test():
  convert_id_number("5")

  try:
    convert_id_number("1.5")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

  try:
    convert_id_number("a")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id!"

def convert_id_interval_test():
  convert_id_interval("8 9")

  try:
    convert_id_interval("9 6")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

  try:
    convert_id_interval("1.5 10")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid contest id interval!"

def convert_score_test():
  convert_score("1.9")

  try:
    convert_score("7/4")
    assert False
  except Exception as ex:
    assert str(ex) == "invalid score!"

def run_conversions_tests():
  convert_score_list_test()
  convert_id_number_test()
  convert_id_interval_test()
  convert_score_test()
