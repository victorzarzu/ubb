from domain.lab_problem import LabProblem
from validation.validator_lab_problem import ValidatorLabProblem
from errors.errors import ValidationError, RepositoryError 
from infrastructure.repo_lab_problems import RepositoryLabProblems
from business.service_lab_problems import ServiceLabProblems
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

    new_description = "Sterge baza de date"
    new_deadline = datetime.date(2021, 10, 11)
    lab_problem_same = LabProblem(lab, problem , new_description, new_deadline)
    assert lab_problem == lab_problem_same
    
    modify_description = "Asa"
    modify_deadline = None
    lab_problem.modify(modify_description, modify_deadline)
    assert lab_problem.get_description() == modify_description
    assert lab_problem.get_deadline() == deadline

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

  def __test_modify_lab_problem_service(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)

    validator = ValidatorLabProblem()
    repo = RepositoryLabProblems()
    srv = ServiceLabProblems(validator, repo)

    srv.add_lab_problem(lab, problem, description, deadline)

    new_lab = 7
    new_problem = 10
    new_description = "Actualizati baza de date"
    new_deadline = datetime.date(2222, 11, 25)
    srv.add_lab_problem(new_lab, new_problem, new_description, new_deadline)
    
    modify_description = "Stergeti baza de date"
    modify_deadline = None
    srv.modify_lab_problem(lab, problem, modify_description, modify_deadline)
    lab_problem = repo.search_lab_problem(lab, problem)
    assert lab_problem.get_description() == modify_description
    assert lab_problem.get_deadline() == deadline
  
    modify_description = "Stergeti baza de date in alt fel"
    modify_deadline = datetime.date(2223, 11, 25)
    srv.modify_lab_problem(new_lab, new_problem, modify_description, modify_deadline)
    lab_problem = repo.search_lab_problem(new_lab, new_problem)
    assert lab_problem.get_description() == modify_description
    assert lab_problem.get_deadline() == modify_deadline

    absent_lab = 110
    absent_problem = 6
    try:
      srv.modify_lab_problem(absent_lab, absent_problem, new_description, new_deadline)
    except RepositoryError as re:
      assert str(re) == "absent lab problem!"

  def run_all_tests(self):
    self.__test_create_lab_problem()
    self.__test_validate_lab_problem()
    self.__test_add_lab_problem_repo()
    self.__test_delete_lab_problem_repo()
    self.__test_add_lab_problem_service()
    self.__test_delete_lab_problem_service()
    self.__test_modify_lab_problem_service()
