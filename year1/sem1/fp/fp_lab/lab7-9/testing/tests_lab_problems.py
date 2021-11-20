from domain.lab_problem import LabProblem
from validation.validator_lab_problem import ValidatorLabProblem
from errors.errors import ValidationError, RepositoryError 
from infrastructure.repo_lab_problems import RepositoryLabProblems
from business.service_lab_problems import ServiceLabProblems
from infrastructure.file_repo_lab_problems import FileRepositoryLabProblems
import datetime

class TestsLabProblems:
  """
  class with tests for lab_problems
  """
  
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
    assert lab_problem.get_status() == True


    lab_problem.set_status(False)
    assert lab_problem.get_status() == False

    new_description = "Sterge baza de date"
    new_deadline = datetime.date(2021, 10, 11)
    lab_problem_same = LabProblem(lab, problem , new_description, new_deadline)
    assert lab_problem == lab_problem_same
    
    modify_description = "Asa"
    modify_deadline = None
    lab_problem.modify(modify_description, modify_deadline)
    assert lab_problem.get_description() == modify_description
    assert lab_problem.get_deadline() == deadline

    lab_problem_string = "1;1;Sterge baza de date;11 10 2022"
    lab = 1
    problem = 1
    description = "Sterge baza de date"
    deadline = datetime.date(2022, 10, 11)

    lab_problem = LabProblem.from_string(lab_problem_string)
    assert lab_problem.get_lab() == lab
    assert lab_problem.get_problem() == problem
    assert lab_problem.get_description() == description
    assert lab_problem.get_deadline() == deadline

    string = str(lab_problem)
    assert string == lab_problem_string

    printable_string = lab_problem.to_print()
    assert printable_string == "description: Sterge baza de date\ndeadline: 11 10 2022\n"

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

  def __test_store_repo(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)
    
    repo = RepositoryLabProblems()
    assert len(repo) == 0
    lab_problem = LabProblem(lab, problem, description, deadline)
    repo.store(lab_problem)
    assert len(repo) == 1

    absent_lab = 10
    absent_problem = 100
    absent_lab_problem = LabProblem(absent_lab, absent_problem, description, deadline)
    try:
      repo.search(absent_lab, absent_problem)
      assert False
    except RepositoryError as re:
      assert str(re) == "absent lab problem!"

    new_description = "Sterge baza de date"
    new_deadline = datetime.date(2333, 11, 25)
    lab_problem_same = LabProblem(lab, problem, new_description, new_deadline)

    try:
      repo.store(lab_problem_same)
      assert False
    except RepositoryError as re:
      assert str(re) == "existent lab problem!"
  
  def __test_delete_repo(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)
    lab_problem = LabProblem(lab, problem, description, deadline)
    
    repo = RepositoryLabProblems()

    repo.store(lab_problem)

    lab1 = 5
    problem1 = 10
    description = "Stergeti baza de date"
    deadline = datetime.date(2222, 10, 25)
    lab_problem = LabProblem(lab1, problem1, description, deadline)

    repo.store(lab_problem)
    
    repo.delete(lab, problem)
    assert len(repo) == 1

    absent_lab = 7
    absent_problem = 20
    repo.delete(absent_lab, absent_problem)
    assert len(repo) == 1


  def __test_store_service(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)

    validator = ValidatorLabProblem()
    repo = RepositoryLabProblems()
    srv = ServiceLabProblems(validator, repo)

    assert srv.number_of_lab_problems() == 0
    srv.store(lab, problem, description, deadline)
    assert srv.number_of_lab_problems() == 1

    invalid_lab = -1
    invalid_problem = -5
    try:
      srv.store(invalid_lab, invalid_problem, description, deadline)
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid lab problem!\n"

    new_description = "Sterge baza de date"   
    new_deadline = datetime.date(2500, 1, 8) 
    try:
      srv.store(lab, problem, new_description, new_deadline)
      assert False
    except RepositoryError as re:
      assert str(re) == "existent lab problem!"

    printable_lab_problem = srv.search(lab, problem)
    assert printable_lab_problem == "description: Actualizati baza de date\ndeadline: 25 11 2222\n"
  
  def __test_delete_service(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)
    
    repo = RepositoryLabProblems()
    validator = ValidatorLabProblem()
    srv = ServiceLabProblems(validator, repo)

    srv.store(lab, problem, description, deadline)

    lab1 = 5
    problem1 = 10
    description = "Stergeti baza de date"
    deadline = datetime.date(2222, 10, 25)
    srv.store(lab1, problem1, description, deadline)

    srv.delete(lab, problem)
    assert srv.number_of_lab_problems() == 1

    absent_lab = 7
    absent_problem = 100 
    try:
      srv.delete(absent_lab, absent_problem) 
      assert False
    except RepositoryError as re:
      assert str(re) == "absent lab problem!"

  def __test_modify_service(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)

    validator = ValidatorLabProblem()
    repo = RepositoryLabProblems()
    srv = ServiceLabProblems(validator, repo)

    srv.store(lab, problem, description, deadline)

    new_lab = 7
    new_problem = 10
    new_description = "Actualizati baza de date"
    new_deadline = datetime.date(2222, 11, 25)
    srv.store(new_lab, new_problem, new_description, new_deadline)
    
    modify_description = "Stergeti baza de date"
    modify_deadline = None
    srv.modify(lab, problem, modify_description, modify_deadline)
    lab_problem = repo.search(lab, problem)
    assert lab_problem.get_description() == modify_description
    assert lab_problem.get_deadline() == deadline
  
    modify_description = "Stergeti baza de date in alt fel"
    modify_deadline = datetime.date(2223, 11, 25)
    srv.modify(new_lab, new_problem, modify_description, modify_deadline)
    lab_problem = repo.search(new_lab, new_problem)
    assert lab_problem.get_description() == modify_description
    assert lab_problem.get_deadline() == modify_deadline

    absent_lab = 110
    absent_problem = 6
    try:
      srv.modify(absent_lab, absent_problem, new_description, new_deadline)
    except RepositoryError as re:
      assert str(re) == "absent lab problem!"

  def __test_file_repo(self):
    lab = 1
    problem = 1
    description = "Sterge baza de date"
    deadline = datetime.date(2222, 11, 25)
    lab_problem = LabProblem(lab, problem, description, deadline)

    filename = "testing/lab_problems_persistance_test.txt"

    repo = FileRepositoryLabProblems(filename)
    repo.store(lab_problem)

    with open(filename, "r") as f:
      number = 0
      for line in f:
        number += 1
    assert number == 1
  
    new_description = "Actualizeaza baza de date"
    new_datetime = datetime.date(2023, 10, 26)

    repo.modify(lab, problem, new_description, new_datetime)

    with open(filename, "r") as f:
      string = f.readline().strip()
      assert string == "1;1;Actualizeaza baza de date;26 10 2023"
    
    repo.delete(lab, problem)

    with open(filename, "r") as f:
      number = 0
      for line in f:
        number += 1
    assert number == 0

  def run_all_tests(self):
    self.__test_create_lab_problem()
    self.__test_validate_lab_problem()
    self.__test_store_repo()
    self.__test_delete_repo()
    self.__test_store_service()
    self.__test_delete_service()
    self.__test_modify_service()
    self.__test_file_repo()
