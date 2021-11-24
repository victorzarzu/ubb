import datetime

class LabProblem:
  """
  abstract data for a problem for a lab
  domain: {{lab_prob, description, deadline}| lab_prob - a dictionary, description - string; deadline - a date}}
  """
  def __init__(self, lab, problem, description, deadline):
    self.__lab_problem = {'lab': lab, 'problem': problem}
    self.__description = description
    self.__deadline = deadline
    self.__exists = True

  def get_lab_problem(self):
    """
    function that returns the __lab_prob of a LabProblem object
    params: -
    return: a dictionary
    """
    return self.__lab_problem
  
  def get_description(self):
    """
    function that returns the __description of a LabProblem object
    params: -
    return: a string 
    """
    return self.__description

  def get_deadline(self):
    """
    function that returns the __description of a LabProblem object
    params: -
    return: a datetime object
    """
    return self.__deadline

  def get_lab(self):
    """
    function that returns only the lab of a LabProblem object
    params: -
    return: an integer
    """
    lab_problem = self.get_lab_problem()
    return lab_problem['lab']


  def get_problem(self):
    """
    function that returns only the problem of a LabProblem object
    params: -
    return: an integer
    """
    lab_problem = self.get_lab_problem()
    return lab_problem['problem']

  def get_status(self):
    """
    function that returns the status of the current object
    params: -
    return: a boolean value
    """
    return self.__exists

  def set_description(self, description):
    """
    function that sets the __description of a LabProblem object
    params: description - a string 
    return: - 
    """
    self.__description = description

  def set_deadline(self, deadline):
    """
    function that sets the __description of a LabProblem object
    params: deadline - a datetime object
    return: - 
    """
    self.__deadline = deadline
  
  def set_status(self, status):
    """
    function that sets the status of the current object to status
    params: status - a boolean value
    return: -
    """
    
    self.__exists = status

  @classmethod
  def from_string(cls, string):
    """
    function that returns a lab_problem from a string
    params: string - a string
    return: a lab_problem object
    """
    string = string.split(";")
    return cls(int(string[0]), int(string[1]), string[2], datetime.datetime.strptime(string[3].strip(), "%d %m %Y").date())

  def __str__(self):
    """
    function that returns a string representing a lab problem
    params: -
    return: a string
    """
    return f'{self.get_lab()};{self.get_problem()};{self.get_description()};{self.get_deadline().strftime("%d %m %Y")}'

  def to_print(self):
    """
    function that returns a printable form of the lab_problem
    params: -
    return: a string
    """
    return f'lab: {self.get_lab()}\nproblem: {self.get_problem()}\ndescription: {self.get_description()}\ndeadline: {self.get_deadline().strftime("%d %m %Y")}\n'

  def modify(self, description, deadline):
    """
    function that modifies the description and the deadline of the lab_problem based on the given parameters
    params: description - a string; deadline - a datetime object
    return: -
    """
    if not description == None:
      self.set_description(description)
    if not deadline == None:
      self.set_deadline(deadline)

  def __eq__(self, other_lab_problem):
    """
    function that verifies if two LabProblem objects are the same by comparing the number of the lab and of the problem
    params: other_lab_problem - a LabProblem object
    return: True, if they are equal, False otherwise
    """
    return self.get_lab() == other_lab_problem.get_lab() and self.get_problem() == other_lab_problem.get_problem()
