from errors.errors import RepositoryError
from infrastructure.repo import Repository

class RepositoryLabProblems(Repository):
  """
  repository class for LabProblem class
  domain: {lab_problems objects}
  """

  def __init__(self):
    super().__init__()

  def __len__(self):
    """
    function that returns the number of actual lab problems that exista
    params: -
    return: an integer
    """

    """
    caz favorabil = caz defavorabil = caz mediu
    complexitatea de timp generala: T(n) = n ∈  Θ(n)  

    caz favorabil = caz defavorabil = caz mediu
    complexitatea de memorie generala: T(n) = 1 ∈  Θ(1)
    """
    lab_problems = 0
    for lab_problem in self._storage:
      if lab_problem.get_status():
         lab_problems += 1

    return lab_problems

  def store(self, lab_problem):
    """
    function that adds a lab_problem into the _storage list of the current class
    params: lab_problem - a lab_problem object
    return: -
    exceptions: RepositoryError with text "exitent lab problem!" if there already is a lab_problem equal with the given one 
    """
    for lab_prob in self._storage:
      if lab_prob == lab_problem and lab_prob.get_status():
        raise RepositoryError("existent lab problem!")

    self.add(lab_problem)

  def search(self, lab, problem):
    """
    function that searchs for an lab_problem object in _storage repo
    params: lab - an integer; problem - an integer 
    return: a lab_problem object
    exceptions: RepositoryError with text "absent lab problem!" if lab_problem is not in the repo 
    """

    """
    caz favorabil: daca problema cautata este prima in repo
      T(n) = 1 ∈  Θ(1) 
    caz defavorabil: daca problema cautata este ultima in repo
      T(n) = T(n) = n ∈  Θ(n)       
    caz mediu: problema cautata poate fi pe pozitia 1, 2,..., n
      T(n) = (1 + 2 + ... + n) / n = (n + 1) / 2 => T(n) ∈  Θ(n)
    complexitatea de timp generala: O(n)  

    caz favorabil = caz defavorabil = caz mediu
    complexitatea de memorie generala: T(n) = 0 ∈  Θ(1)
    """

    for lab_prob in self._storage:
      if lab_prob.get_lab() == lab and lab_prob.get_problem() == problem and lab_prob.get_status():
        return lab_prob

    raise RepositoryError("absent lab problem!")      

  def delete(self, lab, problem):
    """
    function that deletes an lab_problem from _storage repo
    params: lab - an integer; problem - an integer
    return: -
    """
    for lab_problem in self._storage:
      if lab_problem.get_lab() == lab and lab_problem.get_problem() == problem:
        lab_problem.set_status(False)

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
