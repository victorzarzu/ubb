class RepositoryPersistance:
  """
  class that its resposable for the persistance of the data
  """

  def __init__(self, repo, filename, object_class, separators):
    """
    params: repo - a repository type object; 
            filename - a string; 
            object_class - a class reference
            separators - a string
    """
    self.__repo = repo
    self.__filename = filename
    self.__object_class = object_class
    self.__separators = separators
  
  def store(self):
    """
    function that stores the data from self.__repo in the file specified by filename
    params: -
    return: -
    """
    try:
      with open(self.__filename, "w") as f:
        for object_instance in self.__repo._storage:
          if object_instance.get_status():
            line = object_instance.to_string(self.__separators) + "\n"
            f.write(line)
    except IOError:
      print("Impossible to store the data right now!")

  def load(self):
    """
    function that loads the data from the self.__filename to the repo based on the object_class
    params: -
    return: -
    """
    self.__repo.clear()
    try:
      with open(self.__filename, "r") as f:
        for line in f:
          object_instance = self.__object_class.create_from_string(line, self.__separators)
          self.__repo.add(object_instance)
    except IOError:
      print("Impossible to load the data right now!")
