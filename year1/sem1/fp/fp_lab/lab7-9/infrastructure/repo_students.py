from errors.errors import RepositoryError

class RepositoryStudents:
  """
  repository class for Student class
  domain: {student objects}
  """

  def __init__(self):
    self.__students = []

  def __len__(self):
    """
    function that returns the len of the __students list of students
    params: -
    return: an integer
    """
    return len(self.__students)

  def add_student(self, student):
    """
    function that adds a student into the __studets list of the current class
    params: student - a student object
    return: -
    exceptions: RepositoryError with text "exitent id!" if it is already a student with the id of the parameter in the __students list
    """
    for stud in self.__students:
      if student == stud:
        raise RepositoryError("existent id!")

    self.__students.append(student)

  def search_student_by_id(self, studentID):
    """
    function that searches for a student with an id equal to studentID in __students and returns it if it exis
    params: studentID - an integer
    return: a student object
    exceptions: RepositoryError with text "absent id!" if there is no student with the given id
    """
    for student in self.__students:
      if student.get_id() == studentID:
        return student

    if True:
      raise RepositoryError("absent id!")

  def get_all(self):
    """
    a function that returns the whole list of student objects of the current object
    params: -
    return: a list of objects
    """
    return self.__students[:]
