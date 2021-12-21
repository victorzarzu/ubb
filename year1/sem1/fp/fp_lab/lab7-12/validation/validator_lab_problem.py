from errors.errors import ValidationError
import datetime

class ValidatorLabProblem:
  """
  class that validates a labproblem object
  """

  def validate(self, lab_problem):
    """
    function that validates a labproblem object
    params: lab_problem - a labproblem object
    return: -
    exceptions: ValidateError with text
                "invalid lab problem!\n" - if the combination of the lab and problem is not a good one
                "invalid description!\n" - if the description is invalid (empty)
                "invalid deadline!\n" - if the deadline is an invalid one
    """
    errors = ""
    if lab_problem.get_lab() < 0 or lab_problem.get_problem() < 0:
      errors += "invalid lab problem!\n"
    if lab_problem.get_description().strip() == "":
      errors += "invalid description!\n"
    if lab_problem.get_deadline() != None and lab_problem.get_deadline() < datetime.date.today():
      errors += "invalid deadline!\n"
    if len(errors):
      raise ValidationError(errors) 

