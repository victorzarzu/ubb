class LabProblem:
  """
  abstract data for a problem for a lab
  domain: {{lab_prob, description, deadline}| lab_prob - a dictionary, description - string; deadline - a date}}
  """
  def __init__(self, lab, problem, description, deadline):
    self.__lab_problem = {'lab': lab, 'problem': problem}
    self.__description = description
    self.__deadline = deadline

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

  def __eq__(self, other_lab_problem):
    """
    function that verifies if two LabProblem objects are the same by comparing the number of the lab and of the problem
    params: other_lab_problem - a LabProblem object
    return: True, if they are equal, False otherwise
    """
    return self.get_lab() == other_lab_problem.get_lab() and self.get_problem() == other_lab_problem.get_problem()
