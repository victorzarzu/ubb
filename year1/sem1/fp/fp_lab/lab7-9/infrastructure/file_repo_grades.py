from domain.grade import Grade
from errors.errors import RepositoryError
from infrastructure.repo_grades import RepositoryGrades

class FileRepositoryGrades(RepositoryGrades):
  
  def __init__(self, filename):
    super().__init__()
    self.__filename = filename
    self.__load_from_file()

  def __load_from_file(self):
    """
    funcion that loads from file the grades 
    params: -
    return: -
    """
    self.clear()
    try:
      with open(self.__filename, "r") as f:
        for line in f:
          grade = Grade.from_string(line)
          RepositoryGrades.add(self, grade)
    except IOError:
      print("Could not load data from persistent storage")
      pass
      

  def __store_to_file(self):
    """
    function that stores the grades in a file
    params: -
    return: -
    """
    with open(self.__filename, "w") as f:
      for grade in self._storage:
        if grade.get_status():
          grade_string = str(grade) + "\n"
          f.write(grade_string)

  def store(self, grade):
    """
    function that stores a grade in file
    params: grade - a grade object
    return: -
    """
    RepositoryGrades.store(self, grade)
    self.__store_to_file()

  def delete(self, studentID, lab, problem):
    """
    function that deletes a student from a file
    params: studentID - an integer
            lab - an integer
            problem - an integer
    return: -
    """
    RepositoryGrades.delete(self, studentID, lab, problem)
    self.__store_to_file()

  def modify(self, studentID, lab, problem, grade_number):
    """
    function that modifies a student based on id
    params: studentID - an integer
            lab - an integer
            problem - an integer
            grade_number - a float number
    return: -
    """
    RepositoryGrades.modify(self, studentID, lab, problem, grade_number)
    self.__store_to_file()
 
  def search(self, studentID, lab, problem):
    """
    function that searches for a grade
    params: studentID - an integer
            lab - an integer
            problem - an integer
    return: a grade 
    """
    RepositoryGrades.search(self, studentID, lab, problem)

  def get_all(self):
    """
    function that returns all the grades
    params: -
    return: a list of grades
    """
    return RepositoryGrades.get_all(self)

  def get_all_lab_problem(self, lab, problem):
    """
    function that return all the grades that has lab and problem as parameters
    params: lab - an integer
            problem - an integer
    return: a list of grades
    """
    return RepositoryGrades.get_all_lab_problem(self, lab, problem)
