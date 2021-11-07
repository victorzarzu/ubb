class Student:
  """
  abstract data for a student
  domain: {{studentID, nume, grup}| studentID - integer, nume - string, grup - integer}
  """
  def __init__(self, studentID, nume, grup):
    """
    function that creates an student object
    """
    self.__studentID = studentID
    self.__nume = nume
    self.__grup = grup

  def get_id(self):
    """
    function that returns the studentID of the current object
    params: -
    return: an integer
    """
    return self.__studentID
  
  def get_nume(self):
    """
    function that returns the name of the current object
    params: -
    return: a string
    """
    return self.__nume

  def get_grup(self):
    """
    function that returns the group of the current object
    params: -
    return: an integer
    """

    return self.__grup

  def set_nume(self, nume):
    """
    function that sets the name of the current object with name
    params: name - a string
    return: -
    """
    self.__nume = nume

  def set_grup(self, grup):
    """
    function that sets the grup of the current object with grup
    params: name - an integer
    return: -
    """
    self.__grup = grup
  
  def __eq__(self, other_student):
    """
    function that verifies if the current student object is equal to the other_student object based on their ids
    params: other_student - a student object
    return: True, if they are equal, False otherwise
    """
    return self.get_id() == other_student.get_id()
