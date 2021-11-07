from errors.errors import ValidationError

class ValidatorStudent:
  """
  class that validates a student object
  """

  def validate(self, student):
    """
    function that validates a student object
    params: stundet - a student object
    return: -
    exceptions: ValidateError with text
                "invalid id!\n" - if the id is invalid
                "invalid name!\n" - if the name is invalid (empty)
                "invalid group!\n" - if the group is invalid
    """
    errors = ""
    if student.get_id() < 0:
      errors += "invalid id!\n"
    if student.get_nume() == "":
      errors += "invalid name!\n"
    if student.get_grup() < 0:
      errors += "invalid group!\n"

    if len(errors) > 0:
      raise ValidationError(errors)
