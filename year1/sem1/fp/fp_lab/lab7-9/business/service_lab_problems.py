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

  def store(self, lab, problem, description, deadline):
    """
    function that adds a lab_problem object in __repo_lab_problems
    parameters: lab_prob - a dictionary; description - a string; deadline - a datetime object
    return: -
    """
    lab_problem = LabProblem(lab, problem, description, deadline)
    self.__validator_lab_problem.validate(lab_problem)
    self.__repo_lab_problems.store(lab_problem)

  def delete(self, lab, problem):
    """
    function that deletes a lab_problem object from __repo_lab_problems based on the given lab and problem
    parameters: lab - an integer; problem - an integer
    return: -
    """
    self.__repo_lab_problems.search(lab, problem)
    self.__repo_lab_problems.delete(lab, problem)

	
  def search(self, lab, problem):
    """
    function that gets a lab problem and returns a printable form of it
    params: lab - an integer; problem - an integer
    return: a string
    """
    lab_problem = self.__repo_lab_problems.search(lab, problem)
    return lab_problem.to_print()

  def modify(self, lab, problem, description, deadline):
    """
    function that modifies the name and/or the group of a student from __repo_students
    parameters: lab - an integer; problem - an integer; desscription - a string; deadline - a datetime object
    return: -
    """
    lab_problem = self.__repo_lab_problems.search(lab, problem)
    lab_problem = LabProblem(lab, problem, description, deadline)
    self.__validator_lab_problem.validate(lab_problem)

    self.__repo_lab_problems.modify(lab, problem, description, deadline)
    
  def get_all_lab_problems(self):
    """
    function that returns the whole list of lab_problems objects of the current repo
    params: -
    return: a list of lab_problem objects
    """
    return self.__repo_lab_problems.get_all()
