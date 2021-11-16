class Grade:
  """
  class for a grade
  """

  def __init__(self, studentID, lab, problem, grade):
    """
    studentID - an integer
    lab - an integer
    problem - an integer
    grade - a float number
    """
    self.__studentID = studentID
    self.__lab = lab
    self.__problem = problem
    self.__grade = grade
    self.__exists = True
  
  def get_student(self):
    """
    function that returns the student if of the grade object
    params: -
    retrun: an integer 
    """
    return self.__studentID
  
  def get_lab(self):
    """
    function that returns the lab of the grade object
    params: -
    retrun: an integer 
    """
    return self.__lab
  
  def get_problem(self):
    """
    function that returns the problem of the grade object
    params: -
    retrun: an integer 
    """
    return self.__problem
   
  def get_grade(self):
    """
    function that returns the grade of the grade object
    params: -
    retrun: an integer 
    """
    return self.__grade

  def get_status(self):
    """
    function that returns the status of the grade - deleted or not
    params: -
    return: a boolean value
    """
    return self.__exists

  def set_student(self, _id):
    """
    function that sets the student id of the grade object to _id
    params: _id - an integer
    retrun: - 
    """
    self.__studentID = _id
  
  def set_lab(self, lab):
    """
    function that sets lab of the grade object to lab 
    params: lab - an integer
    retrun: - 
    """
    self.__lab = lab
  
  def set_problem(self, problem):
    """
    function that sets problem of the grade object to problem 
    params: problem - an integer
    retrun: - 
    """
    self.__problem = problem
   
  def set_grade(self, grade):
    """
    function that sets problem of the grade object to grade
    params: grade - an integer
    retrun: - 
    """
    self.__grade = grade

  def set_status(self, status):
    """
    function that sets the status of the grade object to status
    params: status - a boolean value
    return: -
    """
    self.__exists = status
 
  def __eq__(self, grade):
    """
    function that compares if 2 grade objects are the same
    params: grade - a grade object
    return: a boolean value
    """
    return self.get_student() == grade.get_student() and self.get_lab() == grade.get_lab() and self.get_problem() == grade.get_problem()
