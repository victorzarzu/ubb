from errors.errors import RepositoryError

class RepositoryLabProblems:
  """
  repository class for LabProblem class
  domain: {lab_problems objects}
  """

  def __init__(self):
    self.__lab_problems = []

  def __len__(self):
    """
    function that returns the len of the __lab_problems list of lab_problems
    params: -
    return: an integer
    """
    return len(self.__lab_problems)

  def add_lab_problem(self, lab_problem):
    """
    function that adds a lab_problem into the __lab_problems list of the current class
    params: lab_problem - a lab_problem object
    return: -
    exceptions: RepositoryError with text "exitent lab problem!" if there already is a lab_problem equal with the given one 
    """
    for lab_prob in self.__lab_problems:
      if lab_prob == lab_problem:
        raise RepositoryError("existent lab problem!")

    self.__lab_problems.append(lab_problem)

  def search_lab_problem(self, lab, problem):
    """
    function that searchs for an lab_problem object in __lab_problems repo
    params: lab - an integer; problem - an integer 
    return: a lab_problem object
    exceptions: RepositoryError with text "absent lab problem!" if lab_problem is not in the repo 
    """
    for lab_prob in self.__lab_problems:
      if lab_prob.get_lab() == lab and lab_prob.get_problem() == problem:
        return lab_prob

    if True:
      raise RepositoryError("absent lab problem!")      

  def delete_lab_problem(self, lab, problem):
    """
    function that deletes an lab_problem from __lab_problems repo
    params: lab - an integer; problem - an integer
    return: -
    """
    for i in range(len(self.__lab_problems)):
      if self.__lab_problems[i].get_lab() == lab and self.__lab_problems[i].get_problem() == problem:
        del self.__lab_problems[i] 
        return

  def get_all(self):
    """
    a function that returns the whole list of lab_problem objects of the current object
    params: -
    return: a list of objects
    """
    return self.__lab_problems[:]
