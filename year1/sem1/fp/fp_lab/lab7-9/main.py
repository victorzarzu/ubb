from testing.tests import Tests
from testing.tests_students import TestsStudents
from testing.tests_lab_problems import TestsLabProblems
from testing.tests_grades import TestsGrades

from presentation.console import Console

from business.service_students import ServiceStudents
from business.service_lab_problems import ServiceLabProblems
from business.service_grades import ServiceGrades

from validation.validator_student import ValidatorStudent
from validation.validator_lab_problem import ValidatorLabProblem
from validation.validator_grade import ValidatorGrade

from infrastructure.repo_students import RepositoryStudents
from infrastructure.repo_lab_problems import RepositoryLabProblems
from infrastructure.repo_grades import RepositoryGrades
from infrastructure.repo_lab_problems import RepositoryLabProblems
from infrastructure.repo_grades import RepositoryGrades

from infrastructure.file_repo_students import FileRepositoryStudents
from infrastructure.file_repo_lab_problems import FileRepositoryLabProblems
from infrastructure.file_repo_grades import FileRepositoryGrades

if __name__ == "__main__":
  validator_student = ValidatorStudent()
  validator_lab_problem = ValidatorLabProblem()
  validator_grade = ValidatorGrade()

  students_file = "students.txt"
  lab_problems_file = "lab_problems.txt"
  grades_file = "grades.txt"

  #repo_students = RepositoryStudents()
  #repo_lab_problems = RepositoryLabProblems()
  #repo_grades = RepositoryGrades()

  try: 
    repo_students = FileRepositoryStudents(students_file)
    repo_lab_problems = FileRepositoryLabProblems(lab_problems_file)
    repo_grades = FileRepositoryGrades(grades_file)
  except IOError:
    print("Couldn't load the data from the memory right now")
    exit()

  srv_students = ServiceStudents(validator_student, repo_students)
  srv_lab_problems = ServiceLabProblems(validator_lab_problem, repo_lab_problems)
  srv_grades = ServiceGrades(validator_grade, repo_students, repo_lab_problems, repo_grades)

  ui = Console(srv_students, srv_lab_problems, srv_grades)

  tests_students = TestsStudents()
  tests_lab_problems = TestsLabProblems()
  tests_grades = TestsGrades()
  tests = Tests(tests_students, tests_lab_problems, tests_grades)
  tests.run_all_tests()
  
  ui.run()
