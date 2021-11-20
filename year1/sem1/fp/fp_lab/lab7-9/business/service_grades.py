from domain.student import Student
from domain.student_dto import StudentDTO
from domain.lab_problem import LabProblem
from domain.grade import Grade
from functools import cmp_to_key

class ServiceGrades:
  """
  service class for grades
  """

  def __init__(self, validator, repo_students, repo_lab_problems, repo_grades):
    self.__validator = validator
    self.__repo_students = repo_students
    self.__repo_lab_problems = repo_lab_problems
    self.__repo_grades = repo_grades

  def grade(self, studentID, lab, problem, grade_number):
    """
    function that grades a student based on its id on the problem of the lab
    params: studentID - an integer
            lab - an integer
            problem - an integer
            grade_number - a float value
    return: -
    """
    self.__repo_students.search(studentID)
    self.__repo_lab_problems.search(lab, problem)

    grade = Grade(studentID, lab, problem, grade_number)
    self.__validator.validate(grade)

    self.__repo_grades.store(grade)

  def delete_grade(self, studentID, lab, problem):
    """
    function that deletes a grade of a student
    params: studentID - an integer
            lab - an integer
            problem - an integer
    return: -
    """
    #self.__repo_students.search(studentID)
    #self.__repo_lab_problems.search(lab, problem)
    self.__repo_grades.search(studentID, lab, problem)

    self.__repo_grades.delete(studentID, lab, problem)
  
  def modify_grade(self, studentID, lab, problem, grade_number):
    """
    function that modifies a grade of a student to a lab problem
    params: studentID - an integer
            lab - an integer
            problem - an integer
            grade_number - a float value
    return: -
    """
    grade = Grade(studentID, lab, problem, grade_number)
    self.__validator.validate(grade)

    #self.__repo_students.search(studentID)
    #self.__repo_lab_problems.search(lab, problem)
    self.__repo_grades.search(studentID, lab, problem)
    
    self.__repo_grades.modify(studentID, lab, problem, grade_number)
  

  def get_lab_problem(self, lab, problem):
    pass
    

  def get_all(self):
    """
    function that returns a list of StudentDTO objects
    params: -
    return: a lsit of StudentDTO objects
    """
    grades = self.__repo_grades.get_all()

    students_data = {}
    for grade in grades:
      if grade.get_student() not in students_data:
        students_data[grade.get_student()] = []
      students_data[grade.get_student()].append(grade)

    result = []
    for student_data in students_data:  
      name = self.__repo_students.search(student_data).get_name()
      student_dto = StudentDTO(name)
      for grade in students_data[student_data]:
        student_dto.add_grade(grade) 
      result.append(student_dto)

    return result
  
  def get_students_by_lab_problem(self, lab, problem):
    """
    function that returns a list of StudentDTO objects that have the lab and the problem as parameters
    params: lab - an integer
            problem - an integer
    return: a list of StundetDTO objects
    """
    grades = self.__repo_grades.get_all_lab_problem(lab, problem)
  
    students_data = {}
    for grade in grades:
      if grade.get_student() not in students_data:
        students_data[grade.get_student()] = []
      students_data[grade.get_student()].append(grade)

    result = []
    for student_data in students_data:
      name = self.__repo_students.search(student_data).get_name()
      student_dto = StudentDTO(name)
      for grade in students_data[student_data]:
        student_dto.add_grade(grade)
      result.append(student_dto)
        
    result.sort(key = cmp_to_key(sort_grade_name))
    return result
  
  def get_students_with_small_average(self):
    """
    function that returns a list of StudentDTO objects that have the average smaller than 5
    param: -
    return: a list of StudentDTO objects
    """
    student_dtos = self.get_all()
    student_dtos = list(filter(filter_average_smaller_than_5, student_dtos))
    return student_dtos




def filter_average_smaller_than_5(student_odt):
    """
    function used at filtering for students that have an average of grades smaller than 5
    params: student_odt - a StudentDTO object
    return: True if the current object has an average smaller than 5, False otherwise
    """
    if student_odt.average() - 5 < 0.000001:
      return True
    return False

def sort_grade_name(studentdto1, studentdto2):
  """
  function used for sorting the students based on their grades and names
  params: stundetdto1, studentdto2 - StundetDTO object
  return: -1 if studentdto1 need to be in front of studentdto2 in sorted list
          -1 if studentdto1 need to be after the studentdto2 in sorted list
          0 if they are equal
  """
  if abs(studentdto1.average() - studentdto2.average()) <= 0.000001:
    if studentdto1.get_name() < studentdto2.get_name():
      return -1
    elif studentdto1.get_name() > studentdto2.get_name():
      return 1
    return 0
  else:
    return studentdto1.average() - studentdto2.average()
