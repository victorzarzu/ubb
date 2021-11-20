from domain.student import Student
from errors.errors import RepositoryError
from infrastructure.repo_students import RepositoryStudents

class FileRepositoryStudents(RepositoryStudents):

  def __init__(self, filename):
    super().__init__()
    self.__filename = filename
    self.__load_from_file()

  def __load_from_file(self):
    """
    funcion that loads from file the students
    params: -
    return: -
    """
    with open(self.__filename, "r") as f:
      for line in f:
        student = Student.from_string(line)
        RepositoryStudents.add(self, student)

  def __store_to_file(self):
    """
    function that stores the students in a file
    params: -
    return: -
    """
    with open(self.__filename, "w") as f:
      for student in self._storage:
        if student.get_status():
          student_string = str(student) + "\n"
          f.write(student_string)

  def store(self, student):
    """
    function that stores the student in file
    params: student - a student object
    return: -
    """
    RepositoryStudents.store(self, student)
    self.__store_to_file()

  def delete(self, studentID):
    """
    function that deletes a student from a file
    params: studentID - an integer
    return: -
    """
    RepositoryStudents.delete(self, studentID)
    self.__store_to_file()

  def modify(self, studentID, name, group):
    """
    function that modifies a student based on id
    params: name - a string; group - an integer
    return: -
    """
    RepositoryStudents.modify(self, studentID, name, group)
    self.__store_to_file()
