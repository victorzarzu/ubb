class StudentGrade:
  
  def __init__(self, studentID, lab, problem, grade):
    self.__studentID = studentID
    self.__student_name = ""
    self.__lab = lab
    self.__problem = problem
    self.__grade = grade


  def get_student_id(self):
    """
    function that returns the student id of the current object
    params: -
    return: an integer
    """
    return self.__studentID
  
  def get_student_name(self):
    """
    function that returns the student name of the current object
    params: -
    return: a string
    """
    return self.__student_name

  def get_lab(self):
    """
    function that returns the lab of the current object
    params: -
    return: an integer 
    """
    return self.__lab

  def get_problem(self):
    """
    function that returns the problem of the current object
    params: -
    return: an integer 
    """
    return self.__problem

  def get_grade(self):
    """
    function that returns the grade of the current object
    params: -
    return: an integer
    """
    return self.__grade
 
  def set_student_name(self, name):
    """
    function that sets the name of the student to name
    params: name - a string
    return: -
    """
    self.__student_name = name
 
