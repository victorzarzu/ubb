class StudentDTO:
  def __init__(self, name):
    self.__name = name
    self.__grades = []

  def __len__(self):
    """
    function that returns the len of the 
    """
    return len(self.__grades)

  def add_grade(self, grade):
    """
    function that adds a grade to the list of grades
    params: grade - a StudentGrade object
    return: -
    """
    self.__grades.append(grade)

  def get_name(self):
    """
    function that returns the name of the student
    params: -
    return: a string
    """
    return self.__name

  def __str__(self):
    """
    returns the printable form of the object
    params: -
    return: a string
    """
    return f'{self.__name}: {self.average()}'

  def average(self):
    """
    function that returns the average grades of the student
    params: -
    return: a float
    """
    grades_number = [_grade.get_grade() for _grade in self.__grades]
    return sum(grades_number) / len(grades_number)
