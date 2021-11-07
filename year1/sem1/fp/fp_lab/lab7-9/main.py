from testing.tests import Tests
from presentation.console import Console
from business.service_students import ServiceStudents
from validation.validator_student import ValidatorStudent
from infrastructure.repo_students import RepositoryStudents

if __name__ == "__main__":
  validator_student = ValidatorStudent()
  repo_student = RepositoryStudents()

  srv_students = ServiceStudents(validator_student, repo_student)

  ui = Console(srv_students)

  tests = Tests()
  tests.run_all_tests()
  
  ui.run()
