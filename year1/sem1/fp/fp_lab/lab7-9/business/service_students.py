from domain.student import Student

class ServiceStudents:
  """
  service class for students
  """

  def __init__(self, validator_student, repo_students):
    self.__validator_student = validator_student
    self.__repo_students = repo_students

  def number_of_students(self):
    """
    function that returns the number of students that are in __repo_stundets
    params: -
    return: an integer
    """
    return len(self.__repo_students)

  def add_student(self, studentID, name, group):
    """
    function that adds a student object in __repo_students
    parameters: studentID - an integer; name - a string; group - an integer
    return: -
    """
    student = Student(studentID, name, group)
    self.__validator_student.validate(student)
    self.__repo_students.add_student(student)
  
  def delete_student(self, studentID):
    """
    function that deletes a student object from __repo_stundets by its id
    parameters: studentID - an integer
    return: -
    """
    self.__repo_students.search_student_by_id(studentID)
    self.__repo_students.delete_student(studentID)

  def get_all_students(self):
    """
    function that returns the whole list of student objects from the current repo
    params: -
    return: a list of student objects
    """
    return self.__repo_students.get_all()
