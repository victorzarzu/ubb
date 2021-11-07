from testing.tests import Tests
from presentation.console import Console
from business.service_students import ServiceStudents
from business.service_lab_problems import ServiceLabProblems
from validation.validator_student import ValidatorStudent
from validation.validator_lab_problem import ValidatorLabProblem
from infrastructure.repo_students import RepositoryStudents
from infrastructure.repo_lab_problems import RepositoryLabProblems

if __name__ == "__main__":
  validator_student = ValidatorStudent()
  validator_lab_problem = ValidatorLabProblem()

  repo_students = RepositoryStudents()
  repo_lab_problems = RepositoryLabProblems()

  srv_students = ServiceStudents(validator_student, repo_students)
  srv_lab_problems = ServiceLabProblems(validator_lab_problem, repo_lab_problems)

  ui = Console(srv_students, srv_lab_problems)

  tests = Tests()
  tests.run_all_tests()
  
  ui.run()
