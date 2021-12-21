class Repository:
  """
  base class for repository
  """

  def __init__(self):
    self._storage = []

  def __len__(self):
    """
    function that returns the len of the _storage list
    params: -
    return: an integer
    """
    return len(self._storage)

  def clear(self):
    """
    function that clear the _storage
    params: -
    return: -
    """
    self._storage = []

  def add(self, item):
    """
    function that adds an item in _storage list
    params: -
    return: -
    """
    self._storage.append(item)

  def get_all(self):
    """
    function that returns the whole list _storage
    params: -
    return: a list
    """
    return self._storage[:]
