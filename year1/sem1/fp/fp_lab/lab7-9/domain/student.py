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
    self.__exists = True

  def get_id(self):
    """
    function that returns the studentID of the current object
    params: -
    return: an integer
    """
    return self.__studentID
  
  def get_name(self):
    """
    function that returns the name of the current object
    params: -
    return: a string
    """
    return self.__nume

  def get_group(self):
    """
    function that returns the group of the current object
    params: -
    return: an integer
    """

    return self.__grup

  def get_status(self):
    """
    function that returns the status of the current object
    params: -
    return: a boolean value
    """
    return self.__exists

  def set_nume(self, nume):
    """
    function that sets the name of the current object to name
    params: name - a string
    return: -
    """
    self.__nume = nume

  def set_grup(self, grup):
    """
    function that sets the grup of the current object to grup
    params: name - an integer
    return: -
    """
    self.__grup = grup
  
  def set_status(self, status):
    """
    function that sets the status of the current object to status
    params: status - a boolean value
    return: -
    """
    self.__exists = status

  def modify(self, name, group):
    """
    function that modifies the name and the group of the student based on the parameters
    params: name - a string or None; group - an integer or None
    return: -
    """
    if not name == None:
      self.set_nume(name)
    if not group == None:
      self.set_grup(group)

  @classmethod
  def from_string(cls, string):
    """
    function that returns a student from a string
    params: string - a string;
    return: a student object
    """
    string = string.split(";")
    return cls(int(string[0]), string[1], int(string[2]))

  def to_string(self):
    """
    function that returns a string representing the student
    params: 
    return: a string
    """
    return f"{self.get_id()};{self.get_name()};{self.get_group()}"

  def to_print(self):
    """
    function that returns a printable form of a student
    params: -
    return: a string
    """
    return f'name: {self.get_name()}\ngroup: {self.get_group()}'

  def __eq__(self, other_student):
    """
    function that verifies if the current student object is equal to the other_student object based on their ids
    params: other_student - a student object
    return: True, if they are equal, False otherwise
    """
    return self.get_id() == other_student.get_id()
