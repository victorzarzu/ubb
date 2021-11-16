class Tests:
  """
  class with test functions
  """
  
  def __init__(self, student_test, lab_problem_test, grade_test):
  	self.__student_test = student_test
  	self.__lab_problem_test = lab_problem_test
  	self.__grade_test = grade_test

  
  def run_all_tests(self):
    self.__student_test.run_all_tests()
    self.__lab_problem_test.run_all_tests()
    self.__grade_test.run_all_tests()
