from errors.errors import ValidationError

class ValidatorGrade: 
  """
  class that validates a grade object
  """

  def validate(self, grade):
    """
    function that validates a grade object
    params: grade - a grade object
    return: -
    exceptions: ValidatorError with text
                "invalid student!\n" - if the student id is not valid
                "invalid lab!\n" - if the lab is not valid
                "invalid problem!\n" - if the problem is not valid
                "invalid grade!\n" - if the grade is not valid
    """
    errors = ""
    if grade.get_student() < 0:
      errors += "invalid student!\n"
    if grade.get_lab() < 0:
      errors += "invalid lab!\n"
    if grade.get_problem() < 0:
      errors += "invalid problem!\n"
    if grade.get_grade() > 10 or grade.get_grade() < 1:
      errors += "invalid grade!\n"
    
    if len(errors):
      raise ValidationError(errors)
