from domain.student import Student
from validation.validator_student import ValidatorStudent
from errors.errors import RepositoryError, ValidationError
import random
import string

letters = string.ascii_lowercase

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

  def store(self, studentID, name, group):
    """
    function that adds a student object in __repo_students
    parameters: studentID - an integer; name - a string; group - an integer
    return: -
    """
    student = Student(studentID, name, group)
    self.__validator_student.validate(student)
    self.__repo_students.store(student)
  
  def delete(self, studentID):
    """
    function that deletes a student object from __repo_stundets by its id
    parameters: studentID - an integer
    return: -
    """
    self.__repo_students.search(studentID)
    self.__repo_students.delete(studentID)

  def modify(self, studentID, name, group):
    """
    function that modifies the name and/or the group of a student from __repo_students
    parameters: studentID - an integer; name - a string; group - an integer
    return: -
    """
    self.__repo_students.search(studentID)
    self.__repo_students.modify(studentID, name, group)

  def search(self, studentID):
    """
    function that gets a student by its id and returns a printable form of it
    params: studentID - an integer
    return: a string
    """
    student = self.__repo_students.search(studentID)
    return student.to_print()

  def get_all_students(self):
    """
    function that returns the whole list of student objects from the current repo
    params: -
    return: a list of student objects
    """
    return self.__repo_students.get_all()
  
  def store_random_students(self):
    """
    function that adds a random number of students with random data
    params: -
    return: -
    """
    students_number = random.randrange(20)
    validator = ValidatorStudent()

    for i in range(students_number):
      try:
        studentID = random.randrange(10000)
        name_len = random.randrange(25)
        name = "".join(random.choices(letters, k = name_len)).capitalize()
        group = random.randrange(10000)
        student = Student(studentID, name, group)
        validator.validate(student)
        
        self.__repo_students.store(student)
      except RepositoryError as re:
        if str(re) == "existent id!":
          i -= 1 
        else:
          raise RepositoryError(str(re))
      except ValidationError as ve:
        i -= 1
