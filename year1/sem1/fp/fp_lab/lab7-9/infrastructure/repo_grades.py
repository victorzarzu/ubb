from errors.errors import RepositoryError
from infrastructure.repo import Repository
from domain.grade import Grade

class RepositoryGrades(Repository):
  """
  repository class for Grade class
  domain: {grade objects}
  """

  def __init__(self):
    super().__init__()

  def __len__(self):
    """
    function that returns the number of the actual grades that exists
    params: -
    return: an integer
    """
    grades = 0
    for grade in self._storage:
      if grade.get_status():
        grades += 1

    return grades

  def store(self, grade):
    """
    function that adds a grade into to _storage list of the current class
    params: grade - a grade object
    return: -
    exceptions: RepositoryError with text "existent grade!" if there is already a grade that is equal to last one
    """
    for _grade in self._storage:
      if grade == _grade and _grade.get_status():
        raise RepositoryError("existent grade!")

    self.add(grade)

  def search(self, studentID, lab, problem):
    """
    function that searches for a grade that has the attributres given by the parameters
    params: studentID - an integer
            lab - an integer
            problem - an integer
    return: a grade object
    exceptions: RepositoryError with text "absent grade!" if there is no grade with the given attributes
    """
    artificial_grade = Grade(studentID, lab, problem, 0)
    for grade in self._storage:
      if grade == artificial_grade and grade.get_status():
        return grade

    raise RepositoryError("absent grade!")

  def delete(self, studentID, lab, problem):
    """
    function that deletes from the repo the grade that matches the arguments
    params: studentID - an integer
            lab - an integer
            problem - an integer
    return: -
    """
    artificial_grade = Grade(studentID, lab, problem, 0)
    for grade in self._storage:
      if grade == artificial_grade:
        grade.set_status(False)
        return

    raise RepositoryError("absent grade!")
    
  def modify(self, studentID, lab, problem, grade_number):
    """
    function that changes the grade of the grade object to grade_number
    params: studentID - an integer 
            lab - an integer
            problem - an integer
            grade_number - a float
    return: -
    """
    artificial_grade = Grade(studentID, lab, problem, 0)
    for grade in self._storage:
      if grade == artificial_grade:
        grade.set_grade(grade_number)

  def get_all(self):
    """
    function that returns all the grades
    params: -
    return: a list of grades
    """
    return self._storage[:]

  def get_all_lab_problem(self, lab, problem):
    """
    function that returns the grades that has the lab and the problem
    params: lab - an integer
            problem - an integer
    return: a list of grades
    """
    result = []
    for grade in self._storage:
      if grade.get_lab() == lab and grade.get_problem() == problem:
        result.append(grade)
    return result
