from errors.errors import RepositoryError
from infrastructure.repo import Repository

class RepositoryStudents(Repository):
  """
  repository class for Student class
  domain: {student objects}
  """

  def __init__(self):
    super().__init__()

  def __len__(self):
    """
    function that returns the number of the actual students that exists
    params: -
    return: an integer
    """
    students = 0
    for student in self._storage:
      if student.get_status():
        students += 1

    return students

  def store(self, student):
    """
    function that adds a student into the _storage list of the current class
    params: student - a student object
    return: -
    exceptions: RepositoryError with text "exitent id!" if it is already a student with the id of the parameter in the _storage list
    """
    for _student in self._storage:
      if student == _student and _student.get_status():
        raise RepositoryError("existent id!")

    self.add(student)

  """
  def search(self, studentID):
    function that searches for a student with an id equal to studentID in _storage and returns it if it exis
    params: studentID - an integer
    return: a student object
    exceptions: RepositoryError with text "absent id!" if there is no student with the given id
    for student in self._storage:
      if student.get_id() == studentID and student.get_status():
        return student

    raise RepositoryError("absent id!")
  """

  def search(self, studentID):
    """
    function that searches for a student with an id equal to studentID in _storage and returns it if it exis
    params: studentID - an integer
    return: a student object
    exceptions: RepositoryError with text "absent id!" if there is no student with the given id
    """
    return self.search_recursive(studentID, 0)
 
  def search_recursive(self, studentID, position):
    """
    function that searches for a student with an id equal to studentID in _storage and returns it if it exis
    params: studentID - an integer
            position - an integer
    return: a student object
    exceptions: RepositoryError with text "absent id!" if there is no student with the given id

    """
    if position == len(self):
      raise RepositoryError("absent id!")
    
    if self._storage[position].get_id() == studentID:
      return self._storage[position]
    
    return self.search_recursive(studentID, position + 1)

  def delete(self, studentID):
    """
    function that deletes from the repo the student with the given id
    params: studentID - an integer
    return: -
    """
    self.delete_recursive(studentID, 0)

  def delete_recursive(self, studentID, position):
    """
    function that deletes from the repo the student with the given id
    params: studentID - an integer
            position - an integer
    return: -
    """
    if position == len(self._storage):
      return

    if self._storage[position].get_id() == studentID:
      self._storage[position].set_status(False)
      return
    
    self.delete_recursive(studentID, position + 1)

  def modify(self, studentID, name, group):
    """
    function that modifies a student based on his id
    params: studentID - an integer; name - a string; group - an integer
    return: -
    """
    for student in self._storage:
      if student.get_id() == studentID:
        student.modify(name, group)
