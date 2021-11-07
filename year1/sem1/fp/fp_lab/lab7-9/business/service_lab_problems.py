from domain.lab_problem import LabProblem

class ServiceLabProblems:
  """
  service class for lab problems
  """

  def __init__(self, validator_lab_problem, repo_lab_problems):
    self.__validator_lab_problem = validator_lab_problem
    self.__repo_lab_problems = repo_lab_problems

  def number_of_lab_problems(self):
    """
    function that returns the number of lab_problem objects that are in _repo_lab_problems
    params: -
    return: an integer
    """
    return len(self.__repo_lab_problems)

  def add_lab_problem(self, lab_prob, description, deadline):
    """
    function that adds a lab_problem object in __repo_lab_problems
    parameters: lab_prob - a dictionary; description - a string; deadline - a datetime object
    return: -
    """
    lab_problem = LabProblem(lab_prob, description, deadline)
    self.__validator_lab_problem.validate(lab_problem)
    self.__repo_lab_problems.add_lab_problem(lab_problem)

  def get_all_lab_problems(self):
    """
    function that returns the whole list of lab_problems objects of the current repo
    params: -
    return: a list of lab_problem objects
    """
    return self.__repo_lab_problems.get_all()