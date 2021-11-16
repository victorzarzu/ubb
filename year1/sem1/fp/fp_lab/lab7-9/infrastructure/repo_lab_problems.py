from errors.errors import RepositoryError
from infrastructure.repo import Repository

class RepositoryLabProblems(Repository):
  """
  repository class for LabProblem class
  domain: {lab_problems objects}
  """

  def __init__(self):
    super().__init__()

  def store(self, lab_problem):
    """
    function that adds a lab_problem into the _storage list of the current class
    params: lab_problem - a lab_problem object
    return: -
    exceptions: RepositoryError with text "exitent lab problem!" if there already is a lab_problem equal with the given one 
    """
    for lab_prob in self._storage:
      if lab_prob == lab_problem:
        raise RepositoryError("existent lab problem!")

    self.add(lab_problem)

  def search(self, lab, problem):
    """
    function that searchs for an lab_problem object in _storage repo
    params: lab - an integer; problem - an integer 
    return: a lab_problem object
    exceptions: RepositoryError with text "absent lab problem!" if lab_problem is not in the repo 
    """
    for lab_prob in self._storage:
      if lab_prob.get_lab() == lab and lab_prob.get_problem() == problem:
        return lab_prob

    raise RepositoryError("absent lab problem!")      

  def delete(self, lab, problem):
    """
    function that deletes an lab_problem from _storage repo
    params: lab - an integer; problem - an integer
    return: -
    """
    for i in range(len(self._storage)):
      if self._storage[i].get_lab() == lab and self._storage[i].get_problem() == problem:
        del self._storage[i] 
        return

  def modify(self, lab, problem, description, datetime):
    """
    function that modifies a lab problem based on the lab and the problem values
    params: lab - an integer
            problem - an integer
            description - a string
            datetime - a datetime object
    return: -
    """
    for lab_problem in self._storage:
      if lab_problem.get_lab() == lab and lab_problem.get_problem() == problem:
        lab_problem.modify(description, datetime)
