from domain.lab_problem import LabProblem
from validation.validator_lab_problem import ValidatorLabProblem
from errors.errors import ValidationError, RepositoryError 
from infrastructure.repo_lab_problems import RepositoryLabProblems
from business.service_lab_problems import ServiceLabProblems
from infrastructure.file_repo_lab_problems import FileRepositoryLabProblems
import datetime
import unittest

class TestsLabProblems(unittest.TestCase):
  """
  class with tests for lab_problems
  """
  def setUp(self):
    validator = ValidatorLabProblem()
    self.repo = RepositoryLabProblems()
    self.file_repo = FileRepositoryLabProblems("testing/lab_problems_persistance_test.txt")
    self.srv = ServiceLabProblems(validator, self.repo)
    self.srv_file = ServiceLabProblems(validator, self.file_repo)

  def tearDown(self):
    self.repo.clear()
    self.file_repo.clear()
  
  def testCreateLabProblem(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2021, 8, 25)

    lab_problem = LabProblem(lab, problem, description, deadline)
    self.assertTrue(lab_problem.get_description() == description)
    self.assertTrue(lab_problem.get_deadline() == deadline)
    self.assertTrue(lab_problem.get_lab() == 6)
    self.assertTrue(lab_problem.get_problem() == 10)
    self.assertTrue(lab_problem.get_status() == True)


    lab_problem.set_status(False)
    self.assertEqual(lab_problem.get_status(), False)

    new_description = "Sterge baza de date"
    new_deadline = datetime.date(2021, 10, 11)
    lab_problem_same = LabProblem(lab, problem , new_description, new_deadline)
    self.assertEqual(lab_problem, lab_problem_same)
    
    modify_description = "Asa"
    modify_deadline = None
    lab_problem.modify(modify_description, modify_deadline)
    self.assertTrue(lab_problem.get_description() == modify_description)
    self.assertTrue(lab_problem.get_deadline() == deadline)

    lab_problem_string = "1;1;Sterge baza de date;11 10 2022"
    lab = 1
    problem = 1
    description = "Sterge baza de date"
    deadline = datetime.date(2022, 10, 11)

    lab_problem = LabProblem.from_string(lab_problem_string)
    self.assertTrue(lab_problem.get_lab() == lab)
    self.assertTrue(lab_problem.get_problem() == problem)
    self.assertTrue(lab_problem.get_description() == description)
    self.assertTrue(lab_problem.get_deadline() == deadline)

    string = str(lab_problem)
    self.assertEqual(string, lab_problem_string)

    printable_string = lab_problem.to_print()
    self.assertEqual(printable_string, "lab: 1\nproblem: 1\ndescription: Sterge baza de date\ndeadline: 11 10 2022\n")

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
    self.assertRaisesRegex(ValidationError, "invalid lab problem!\n", validator.validate, lab_problem_invalid_lab_prob)

    invalid_description = ""
    invalid_deadline = datetime.date(2020, 10, 1)
    invalid_lab_problem_all = LabProblem(invalid_lab, problem, invalid_description, invalid_deadline)
    self.assertRaisesRegex(ValidationError, "invalid lab problem!\ninvalid description!\ninvalid deadline!\n", validator.validate, invalid_lab_problem_all)

  def testStoreRepo(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)
    
    self.assertTrue(len(self.repo) == 0)
    lab_problem = LabProblem(lab, problem, description, deadline)
    self.repo.store(lab_problem)
    self.assertTrue(len(self.repo) == 1)

    absent_lab = 10
    absent_problem = 100
    absent_lab_problem = LabProblem(absent_lab, absent_problem, description, deadline)
    self.assertRaisesRegex(RepositoryError, "absent lab problem!", self.repo.search, absent_lab, absent_problem)

    new_description = "Sterge baza de date"
    new_deadline = datetime.date(2333, 11, 25)
    lab_problem_same = LabProblem(lab, problem, new_description, new_deadline)
    self.assertRaisesRegex(RepositoryError, "existent lab problem!", self.repo.store, lab_problem_same)
  
  def testDeleteRepo(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)
    lab_problem = LabProblem(lab, problem, description, deadline)
    
    self.repo.store(lab_problem)

    lab1 = 5
    problem1 = 10
    description = "Stergeti baza de date"
    deadline = datetime.date(2222, 10, 25)
    lab_problem = LabProblem(lab1, problem1, description, deadline)

    self.repo.store(lab_problem)
    
    self.repo.delete(lab, problem)
    self.assertTrue(len(self.repo) == 1)

    absent_lab = 7
    absent_problem = 20
    self.repo.delete(absent_lab, absent_problem)
    self.assertEqual(len(self.repo), 1)

  def testStoreService(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25) 
    self.assertTrue(self.srv.number_of_lab_problems() == 0)
    self.srv.store(lab, problem, description, deadline)
    self.assertTrue(self.srv.number_of_lab_problems() == 1)

    invalid_lab = -1
    invalid_problem = -5
    self.assertRaisesRegex(ValidationError, "invalid lab problem!\n", self.srv.store, invalid_lab, invalid_problem, description, deadline)

    new_description = "Sterge baza de date"   
    new_deadline = datetime.date(2500, 1, 8) 
    self.assertRaisesRegex(RepositoryError, "existent lab problem!", self.srv.store, lab, problem, new_description, new_deadline)

    printable_lab_problem = self.srv.search(lab, problem)
    self.assertEqual(printable_lab_problem, "lab: 6\nproblem: 10\ndescription: Actualizati baza de date\ndeadline: 25 11 2222\n")
  
  def testDeleteService(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)
    
    self.srv.store(lab, problem, description, deadline)

    lab1 = 5
    problem1 = 10
    description = "Stergeti baza de date"
    deadline = datetime.date(2222, 10, 25)
    self.srv.store(lab1, problem1, description, deadline)

    self.srv.delete(lab, problem)
    self.assertEqual(self.srv.number_of_lab_problems(), 1)

    absent_lab = 7
    absent_problem = 100 
    self.assertRaisesRegex(RepositoryError, "absent lab problem!", self.srv.delete, absent_lab, absent_problem)

  def testModifyService(self):
    lab = 6
    problem = 10
    description = "Actualizati baza de date"
    deadline = datetime.date(2222, 11, 25)

    self.srv.store(lab, problem, description, deadline)

    new_lab = 7
    new_problem = 10
    new_description = "Actualizati baza de date"
    new_deadline = datetime.date(2222, 11, 25)
    self.srv.store(new_lab, new_problem, new_description, new_deadline)
    
    modify_description = "Stergeti baza de date"
    modify_deadline = None
    self.srv.modify(lab, problem, modify_description, modify_deadline)
    lab_problem = self.repo.search(lab, problem)
    self.assertTrue(lab_problem.get_description() == modify_description)
    self.assertTrue(lab_problem.get_deadline() == deadline)
  
    modify_description = "Stergeti baza de date in alt fel"
    modify_deadline = datetime.date(2223, 11, 25)
    self.srv.modify(new_lab, new_problem, modify_description, modify_deadline)
    lab_problem = self.repo.search(new_lab, new_problem)
    self.assertEqual(lab_problem.get_description(), modify_description)
    self.assertEqual(lab_problem.get_deadline(), modify_deadline)

    absent_lab = 110
    absent_problem = 6
    self.assertRaisesRegex(RepositoryError, "absent lab problem!", self.srv.modify, absent_lab, absent_problem, new_description, new_deadline)

  def testFileRepo(self):
    lab = 1
    problem = 1
    description = "Sterge baza de date"
    deadline = datetime.date(2222, 11, 25)
    lab_problem = LabProblem(lab, problem, description, deadline)

    filename =  "testing/lab_problems_persistance_test.txt"
    self.file_repo.store(lab_problem)

    with open(filename, "r") as f:
      number = 0
      for line in f:
        number += 1
    self.assertTrue(number == 1)
  
    new_description = "Actualizeaza baza de date"
    new_datetime = datetime.date(2023, 10, 26)

    self.file_repo.modify(lab, problem, new_description, new_datetime)

    with open(filename, "r") as f:
      string = f.readline().strip()
      self.assertEqual(string, "1;1;Actualizeaza baza de date;26 10 2023")
    
    self.file_repo.delete(lab, problem)

    with open(filename, "r") as f:
      number = 0
      for line in f:
        number += 1
    self.assertEqual(number, 0)

  def run_all_tests(self):
    unittest.main()
