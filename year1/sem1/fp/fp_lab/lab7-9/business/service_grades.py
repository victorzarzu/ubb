from domain.student import Student
from domain.lab_problem import LabProblem
from domain.grade import Grade

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
