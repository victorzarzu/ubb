from domain.student import Student
from domain.lab_problem import LabProblem
from validation.validator_student import ValidatorStudent
from validation.validator_lab_problem import ValidatorLabProblem
from errors.errors import ValidationError, RepositoryError 
from infrastructure.repo_students import RepositoryStudents
from infrastructure.repo_lab_problems import RepositoryLabProblems
from business.service_students import ServiceStudents
from business.service_lab_problems import ServiceLabProblems
import datetime

class Tests:
  """
  class with test functions
  """
  def __test_create_student(self):
    """
    function to test the constructor of the Student class
    """
    studentID = 15
    name = "G"
    group = 456
    student = Student(studentID, name, group)
    assert student.get_id() == studentID
    assert student.get_nume() == name
    assert student.get_grup() == group

    name_nou = "A"
    group_nou = 345
    student_same_id = Student(studentID, name_nou, group_nou)
    assert student == student_same_id

  def __test_validate_student(self):
    """
    function to text the validator of a stundet
    """
    studentID = 15
    name = "G"
    group = 456
    student = Student(studentID, name, group)
    validator = ValidatorStudent()
    validator.validate(student)

    invalid_studentID = -5
    invalid_student = Student(invalid_studentID, name, group)
    try:
      validator.validate(invalid_student)
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid id!\n"

    invalid_name = ""
    invalid_group = -6
    invalid_student = Student(invalid_studentID, invalid_name, invalid_group)
    try:
      validator.validate(invalid_student)
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid id!\ninvalid name!\ninvalid group!\n"

  def __test_add_student_repo(self):
    """
    function to test the process of adding a stundent in students repo
    """
    studentID = 15
    name = "G"
    group = 456
    student = Student(studentID, name, group)
    repo = RepositoryStudents()
    repo.add_student(student)
    assert len(repo) == 1

    found_student = repo.search_student_by_id(studentID)
    assert student.get_id() == found_student.get_id()
    assert student.get_nume() == found_student.get_nume()
    assert student.get_grup() == found_student.get_grup()

    name_nou = "A"
    group_nou = 345
    student_same_id = Student(studentID, name_nou, group_nou)
    
    try:
      repo.add_student(student_same_id)
      assert False
    except RepositoryError as re:
      assert str(re) == "existent id!"

    absent_studentID = 10
    try:
      found_student = repo.search_student_by_id(absent_studentID)
      assert False
    except RepositoryError as re:
      assert str(re) == "absent id!"
  

  def __test_add_student_service(self):
    studentID = 15
    name = "G"
    group = 456
    repo = RepositoryStudents()  
    validator = ValidatorStudent()
    srv = ServiceStudents(validator, repo)
    
    assert srv.number_of_students() == 0
    srv.add_student(studentID, name, group)
    assert srv.number_of_students() == 1

    try:
      srv.add_student(studentID, name, group)
      assert False
    except RepositoryError as re:
      assert str(re) == "existent id!"
    
    invalid_studentID = -5
    invalid_name = ""
    invalid_group = -6
    try:
      srv.add_student(invalid_studentID, invalid_name, invalid_group) 
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid id!\ninvalid name!\ninvalid group!\n"

  def __test_delete_student_repo(self):
    studentID = 15
    name = "G"
    group = 456
    student = Student(studentID, name, group)
    repo = RepositoryStudents()
    repo.add_student(student)
  
    studentID = 17
    name = "A"
    group = 455
    student = Student(studentID, name, group)
    repo.add_student(student)

    repo.delete_student(studentID)
    assert len(repo) == 1

    absent_studentID = 7
    repo.delete_student(absent_studentID)
    assert len(repo) == 1

  def __test_delete_student_service(self):
    studentID = 15
    name = "G"
    group = 456
    repo = RepositoryStudents()  
    validator = ValidatorStudent()
    srv = ServiceStudents(validator, repo)
    
    srv.add_student(studentID, name, group)

    studentID1 = 16 
    name = "A"
    group = 455
    srv.add_student(studentID1, name, group)
    
    studentID2 = 14 
    name = "B"
    group = 455
    srv.add_student(studentID2, name, group)

    srv.delete_student(studentID1)
    assert srv.number_of_students() == 2
   
    absent_studentID = 2
    try:
      srv.delete_student(absent_studentID)
      assert False
    except RepositoryError as re:
      assert str(re) == "absent id!"

  def __test_create_lab_problem(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2021, 8, 25)

    lab_problem = LabProblem(lab, problem, description, deadline)
    assert lab_problem.get_description() == description
    assert lab_problem.get_deadline() == deadline
    assert lab_problem.get_lab() == 6
    assert lab_problem.get_problem() == 10

    new_description = "Sterge baza de date"
    new_deadline = datetime.date(2021, 10, 11)
    lab_problem_same = LabProblem(lab, problem , new_description, new_deadline)
    assert lab_problem == lab_problem_same

  def __test_validate_lab_problem(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)
    validator = ValidatorLabProblem()

    lab_problem = LabProblem(lab, problem, description, deadline)
    validator.validate(lab_problem)

    invalid_lab = -1
    problem = 10
    lab_problem_invalid_lab_prob = LabProblem(invalid_lab, problem, description, deadline)
    try:
      validator.validate(lab_problem_invalid_lab_prob)
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid lab problem!\n"

    invalid_description = ""
    invalid_deadline = datetime.date(2020, 10, 1)
    invalid_lab_problem_all = LabProblem(invalid_lab, problem, invalid_description, invalid_deadline)

    try:
      validator.validate(invalid_lab_problem_all)
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid lab problem!\ninvalid description!\ninvalid deadline!\n"

  def __test_add_lab_problem_repo(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)
    
    repo = RepositoryLabProblems()
    assert len(repo) == 0
    lab_problem = LabProblem(lab, problem, description, deadline)
    repo.add_lab_problem(lab_problem)
    assert len(repo) == 1

    absent_lab = 10
    absent_problem = 100
    absent_lab_problem = LabProblem(absent_lab, absent_problem, description, deadline)
    try:
      repo.search_lab_problem(absent_lab, absent_problem)
      assert False
    except RepositoryError as re:
      assert str(re) == "absent lab problem!"

    new_description = "Sterge baza de date"
    new_deadline = datetime.date(2333, 11, 25)
    lab_problem_same = LabProblem(lab, problem, new_description, new_deadline)

    try:
      repo.add_lab_problem(lab_problem_same)
      assert False
    except RepositoryError as re:
      assert str(re) == "existent lab problem!"
  
  def __test_delete_lab_problem_repo(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)
    lab_problem = LabProblem(lab, problem, description, deadline)
    
    repo = RepositoryLabProblems()

    repo.add_lab_problem(lab_problem)

    lab1 = 5
    problem1 = 10
    description = "Stergeti baza de date"
    deadline = datetime.date(2222, 10, 25)
    lab_problem = LabProblem(lab1, problem1, description, deadline)

    repo.add_lab_problem(lab_problem)
    
    repo.delete_lab_problem(lab, problem)
    assert len(repo) == 1

    absent_lab = 7
    absent_problem = 20
    repo.delete_lab_problem(absent_lab, absent_problem)
    assert len(repo) == 1


  def __test_add_lab_problem_service(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)

    validator = ValidatorLabProblem()
    repo = RepositoryLabProblems()
    srv = ServiceLabProblems(validator, repo)

    assert srv.number_of_lab_problems() == 0
    srv.add_lab_problem(lab, problem, description, deadline)
    assert srv.number_of_lab_problems() == 1

    invalid_lab = -1
    invalid_problem = -5
    try:
      srv.add_lab_problem(invalid_lab, invalid_problem, description, deadline)
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid lab problem!\n"

    new_description = "Sterge baza de date"   
    new_deadline = datetime.date(2500, 1, 8) 
    try:
      srv.add_lab_problem(lab, problem, new_description, new_deadline)
      assert False
    except RepositoryError as re:
      assert str(re) == "existent lab problem!"
  
  def __test_delete_lab_problem_service(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)
    
    repo = RepositoryLabProblems()
    validator = ValidatorLabProblem()
    srv = ServiceLabProblems(validator, repo)

    srv.add_lab_problem(lab, problem, description, deadline)

    lab1 = 5
    problem1 = 10
    description = "Stergeti baza de date"
    deadline = datetime.date(2222, 10, 25)
    srv.add_lab_problem(lab1, problem1, description, deadline)

    srv.delete_lab_problem(lab, problem)
    assert srv.number_of_lab_problems() == 1

    absent_lab = 7
    absent_problem = 100 
    try:
      srv.delete_lab_problem(absent_lab, absent_problem) 
      assert False
    except RepositoryError as re:
      assert str(re) == "absent lab problem!"

  def run_all_tests(self):
    self.__test_create_student()
    self.__test_validate_student()
    self.__test_add_student_repo()
    self.__test_delete_student_repo()
    self.__test_add_student_service()
    self.__test_delete_student_service()
    self.__test_create_lab_problem()
    self.__test_validate_lab_problem()
    self.__test_add_lab_problem_repo()
    self.__test_delete_lab_problem_repo()
    self.__test_add_lab_problem_service()
    self.__test_delete_lab_problem_service()
