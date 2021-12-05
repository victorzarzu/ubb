from domain.lab_problem import LabProblem
from errors.errors import RepositoryError
from infrastructure.repo_lab_problems import RepositoryLabProblems

class FileRepositoryLabProblems(RepositoryLabProblems):

  def __init__(self, filename):
    super().__init__()
    self.__filename = filename
    self.__load_from_file()

  def __load_from_file(self):
    """
    funcion that loads from file the lab_problems
    params: -
    return: -
    """
    try:
      with open(self.__filename, "r") as f:
        for line in f:
          lab_problem = LabProblem.from_string(line)
          RepositoryLabProblems.add(self, lab_problem)
    except IOError:
      print("Could not load data from persistent storage")


  def __store_to_file(self):
    """
    function that stores the lab_problems in a file
    params: -
    return: -
    """
    with open(self.__filename, "w") as f:
      for lab_problem in self._storage:
        if lab_problem.get_status():
          lab_problem_string = str(lab_problem) + "\n"
          f.write(lab_problem_string)

  def store(self, lab_problem):
    """
    function that stores the lab_problem in file
    params: lab_problem - a lab_problem object
    return: -
    """
    RepositoryLabProblems.store(self, lab_problem)
    self.__store_to_file()

  def delete(self, lab, problem):
    """
    function that deletes a lab_problem from a file
    params: lab, an integer; problem - an integer
    return: -
    """
    RepositoryLabProblems.delete(self, lab, problem)
    self.__store_to_file()

  def modify(self, lab, problem, description, deadline):
    """
    function that modifies a lab_problem based on id
    params: lab - an integer; problem - an integer; description - a string; deadline - a datetime object 
    return: -
    """
    RepositoryLabProblems.modify(self, lab, problem, description, deadline)
    self.__store_to_file()

  def search(self, lab, problem):
    """
    function that searches for a lab_problem based on lab and problem
    params: lab - an integer
            problem - an integer
    return: a lab_problem object
    """
    return RepositoryLabProblems.search(self, lab, problem)

  def clear(self):
    """
    function that clears the repo
    params: -
    return: -
    """
    RepositoryLabProblems.clear(self)
    self.__store_to_file()
