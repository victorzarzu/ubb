from errors.errors import RepositoryError, ValidationError
from domain.grade import Grade
from domain.student import Student
from domain.lab_problem import LabProblem
from infrastructure.repo_grades import RepositoryGrades
from infrastructure.repo_students import RepositoryStudents
from infrastructure.repo_lab_problems import RepositoryLabProblems
from validation.validator_grade import ValidatorGrade
from business.service_grades import ServiceGrades
import datetime

class TestsGrades:
  """
  class with tests for grades
  """

  def __test_create_grade(self):
    studentID = 5
    lab = 10
    problem = 15
    grade_number = 9.6
    
    grade = Grade(studentID, lab, problem, grade_number)

    assert grade.get_student() == studentID
    assert grade.get_lab() == lab
    assert grade.get_problem() == problem
    assert grade.get_grade() - grade_number <= 0.00001
    assert grade.get_status() == True

    grade_same = Grade(studentID, lab, problem, grade_number)
    assert grade_same == grade

    new_studentID = 6
    new_lab = 11
    new_problem = 16
    new_grade_number = 9.8
    
    grade.set_student(new_studentID)
    grade.set_lab(new_lab)
    grade.set_problem(new_problem)
    grade.set_grade(new_grade_number)
    grade.set_status(False)
    
    assert grade.get_student() == new_studentID
    assert grade.get_lab() == new_lab
    assert grade.get_problem() == new_problem
    assert grade.get_grade() - new_grade_number <= 0.00001
    assert grade.get_status() == False

    
  def __test_validator_grade(self):
    studentID = 5
    lab = 10
    problem = 15
    grade_number = 9.6
    grade = Grade(studentID, lab, problem, grade_number)

    validator = ValidatorGrade()
    validator.validate(grade)

    invalid_studentID = -5
    invalid_grade = Grade(invalid_studentID, lab, problem, grade_number)
    try:
      validator.validate(invalid_grade)
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid student!\n"

    invalid_lab = -5
    invalid_problem = -100
    invalid_grade_number = 10.0001

    invalid_grade = Grade(invalid_studentID, invalid_lab, invalid_problem, invalid_grade_number)
    try:
      validator.validate(invalid_grade)
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid student!\ninvalid lab!\ninvalid problem!\ninvalid grade!\n"

      


  def __test_repo(self):
    studentID = 5
    lab = 10
    problem = 15
    grade_number = 9.6
    
    grade = Grade(studentID, lab, problem, grade_number)
    repo = RepositoryGrades()

    assert len(repo) == 0
    repo.store(grade)
    assert len(repo) == 1
    
    new_studentID = 6
    new_lab = 11
    new_problem = 16
    new_grade_number = 9.8
    new_grade = Grade(new_studentID, new_lab, new_problem, new_grade_number)
    repo.store(new_grade)

    assert len(repo) == 2

    try:
      repo.store(new_grade)
      assert False
    except RepositoryError as re:
      assert str(re) == "existent grade!"

    repo.delete(new_studentID, new_lab, new_problem)
    assert len(repo) == 1
    
    result = repo.search(studentID, lab, problem)
    assert result == grade
    assert result.get_grade() == grade_number
    assert result.get_status() == True

    try:
      result = repo.search(new_studentID, new_lab, new_problem)
      assert True
    except RepositoryError as re:
      assert str(re) == "absent grade!"
  
  def __test_service_grade(self):
    repo_students = RepositoryStudents()
    repo_lab_problems = RepositoryLabProblems()
    repo_grades = RepositoryGrades()
    validator = ValidatorGrade()
    srv = ServiceGrades(validator, repo_students, repo_lab_problems, repo_grades)

    studentID = 1
    name = "Henry"
    group = 912
    student = Student(studentID, name, group)
    repo_students.store(student)
    
    new_studentID = 5
    new_name = "Tim"
    new_group = 566 
    new_student = Student(new_studentID, new_name, new_group)
    repo_students.store(new_student)

    lab = 7
    problem = 2
    description = "Sterge baza de date"
    deadline = datetime.date(2022, 8, 25) 
    lab_problem = LabProblem(lab, problem, description, deadline)
    repo_lab_problems.store(lab_problem)

    grade_number = 9.5
    srv.grade(studentID, lab, problem, grade_number)
    assert len(repo_grades) == 1

    new_grade_number = 8.88
    srv.grade(new_studentID, lab, problem, grade_number)
    assert len(repo_grades) == 2

    try:
      srv.grade(studentID, lab, problem, grade_number)
      assert False
    except RepositoryError as re:
      assert str(re) == "existent grade!"

    absent_studentID = 2
    try:
      srv.grade(absent_studentID, lab, problem, grade_number)
      assert False
    except RepositoryError as re:
      assert str(re) == "absent id!"

    absent_lab = 15
    absent_problem = 16
    try:
      srv.grade(studentID, absent_lab, absent_problem, grade_number)
      assert False
    except RepositoryError as re:
      assert str(re) == "absent lab problem!"

    invalid_grade_number = 0.5
    try:
      srv.grade(studentID, lab, problem, invalid_grade_number)
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid grade!\n"

    srv.delete_grade(studentID, lab, problem)
    assert len(repo_grades) == 1

    modify_grade = 7.4 
    srv.modify_grade(new_studentID, lab, problem, modify_grade)
    grade = repo_grades.search(new_studentID, lab, problem)
    assert (grade.get_grade() - modify_grade) < 0.00001

  def run_all_tests(self):
    self.__test_create_grade()
    self.__test_validator_grade()
    self.__test_repo()
    self.__test_service_grade() 
