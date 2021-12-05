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
import unittest

class TestsGrades(unittest.TestCase):
  """
  class with tests for grades
  """

  def setUp(self):
    validator = ValidatorGrade()
    self.repo_students = RepositoryStudents()
    self.repo_lab_problems = RepositoryLabProblems()
    self.repo_grades = RepositoryGrades()
    self.srv = ServiceGrades(validator, self.repo_students, self.repo_lab_problems, self.repo_grades)

  def tearDown(self):
    self.repo_students.clear()
    self.repo_lab_problems.clear()
    self.repo_grades.clear()

  def testCreateGrade(self):
    studentID = 5
    lab = 10
    problem = 15
    grade_number = 9.6
    
    grade = Grade(studentID, lab, problem, grade_number)
    self.assertTrue(grade.get_student() == studentID)
    self.assertTrue(grade.get_lab() == lab)
    self.assertTrue(grade.get_problem() == problem)
    self.assertTrue(grade.get_grade() - grade_number <= 0.00001)
    self.assertTrue(grade.get_status() == True)

    grade_same = Grade(studentID, lab, problem, grade_number)
    self.assertEqual(grade_same, grade)

    new_studentID = 6
    new_lab = 11
    new_problem = 16
    new_grade_number = 9.8
    
    grade.set_student(new_studentID)
    grade.set_lab(new_lab)
    grade.set_problem(new_problem)
    grade.set_grade(new_grade_number)
    grade.set_status(False)
    
    self.assertTrue(grade.get_student() == new_studentID)
    self.assertTrue(grade.get_lab() == new_lab)
    self.assertTrue(grade.get_problem() == new_problem)
    self.assertTrue(grade.get_grade() - new_grade_number <= 0.00001)
    self.assertTrue(grade.get_status() == False)
    
  def testValidatorGrade(self):
    studentID = 5
    lab = 10
    problem = 15
    grade_number = 9.6
    grade = Grade(studentID, lab, problem, grade_number)

    validator = ValidatorGrade()
    validator.validate(grade)

    invalid_studentID = -5
    invalid_grade = Grade(invalid_studentID, lab, problem, grade_number)
    self.assertRaisesRegex(ValidationError, "invalid student!\n", validator.validate, invalid_grade)

    invalid_lab = -5
    invalid_problem = -100
    invalid_grade_number = 10.0001

    invalid_grade = Grade(invalid_studentID, invalid_lab, invalid_problem, invalid_grade_number)
    self.assertRaisesRegex(ValidationError, "invalid student!\ninvalid lab!\ninvalid problem!\ninvalid grade!\n", validator.validate, invalid_grade)


  def testRepo(self):
    studentID = 5
    lab = 10
    problem = 15
    grade_number = 9.6
    
    grade = Grade(studentID, lab, problem, grade_number)

    self.assertTrue(len(self.repo_grades) == 0)
    self.repo_grades.store(grade)
    self.assertTrue(len(self.repo_grades) == 1)
    
    new_studentID = 6
    new_lab = 11
    new_problem = 16
    new_grade_number = 9.8
    new_grade = Grade(new_studentID, new_lab, new_problem, new_grade_number)
    self.repo_grades.store(new_grade)

    self.assertTrue(len(self.repo_grades) == 2)
    repo_all = self.repo_grades.get_all()
    self.assertTrue(len(repo_all) == 2)
    self.assertTrue(repo_all[0].get_student() == studentID)
    self.assertTrue(repo_all[1].get_student() == new_studentID)

    repo_lab_problem = self.repo_grades.get_all_lab_problem(lab, problem)
    self.assertEqual(len(repo_lab_problem), 1)
    self.assertEqual(repo_lab_problem[0], grade)

    self.assertRaisesRegex(RepositoryError, "existent grade!", self.repo_grades.store, new_grade)

    self.repo_grades.delete(new_studentID, new_lab, new_problem)
    self.assertTrue(len(self.repo_grades) == 1)
    
    result = self.repo_grades.search(studentID, lab, problem)
    self.assertEqual(result, grade)
    self.assertEqual(result.get_grade(), grade_number)
    self.assertEqual(result.get_status(), True)

    self.assertRaisesRegex(RepositoryError, "absent grade!", self.repo_grades.search, new_studentID, new_lab, new_problem)
  
  def testServiceGrade(self):
    studentID = 1
    name = "Henry"
    group = 912
    student = Student(studentID, name, group)
    self.repo_students.store(student)
    
    new_studentID = 5
    new_name = "Tim"
    new_group = 566 
    new_student = Student(new_studentID, new_name, new_group)
    self.repo_students.store(new_student)

    lab = 7
    problem = 2
    description = "Sterge baza de date"
    deadline = datetime.date(2022, 8, 25) 
    lab_problem = LabProblem(lab, problem, description, deadline)
    self.repo_lab_problems.store(lab_problem)

    grade_number = 9.5
    self.srv.grade(studentID, lab, problem, grade_number)
    self.assertEqual(len(self.repo_grades), 1)

    new_grade_number = 8.88
    self.srv.grade(new_studentID, lab, problem, grade_number)
    self.assertEqual(len(self.repo_grades), 2)

    self.assertRaisesRegex(RepositoryError, "existent grade!", self.srv.grade, studentID, lab, problem, grade_number)

    absent_studentID = 2
    self.assertRaisesRegex(RepositoryError, "absent id!", self.srv.grade, absent_studentID, lab, problem, grade_number)

    absent_lab = 15
    absent_problem = 16
    self.assertRaisesRegex(RepositoryError, "absent lab problem!", self.srv.grade, studentID, absent_lab, absent_problem, grade_number)

    invalid_grade_number = 0.5
    self.assertRaisesRegex(ValidationError, "invalid grade!", self.srv.grade, studentID, lab, problem, invalid_grade_number)

    self.srv.delete_grade(studentID, lab, problem)
    self.assertTrue(len(self.repo_grades) == 1)

    modify_grade = 7.4 
    self.srv.modify_grade(new_studentID, lab, problem, modify_grade)
    grade = self.repo_grades.search(new_studentID, lab, problem)
    self.assertAlmostEqual(grade.get_grade(), modify_grade)

  def run_all_tests(self):
    unittest.main()
