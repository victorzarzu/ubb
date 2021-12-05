from domain.student import Student
from domain.student_dto import StudentDTO
from domain.grade import Grade
from validation.validator_student import ValidatorStudent 
from errors.errors import ValidationError, RepositoryError
from infrastructure.repo_students import RepositoryStudents
from business.service_students import ServiceStudents
from infrastructure.file_repo_students import FileRepositoryStudents
import unittest

class TestsStudents(unittest.TestCase):
  """
  class with tests for students
  """

  def setUp(self):
    validator = ValidatorStudent()
    self.repo = RepositoryStudents()
    self.file_repo = FileRepositoryStudents("testing/students_persistance_test.txt") 
    self.srv = ServiceStudents(validator, self.repo)
    self.srv_file = ServiceStudents(validator, self.file_repo)


  def tearDown(self):
    self.repo.clear()
    self.file_repo.clear()

  def testCreate(self):
    studentID = 15
    name = "G"
    group = 456
    student = Student(studentID, name, group)

    self.assertEqual(student.get_id(), studentID)
    self.assertEqual(student.get_name(), name)
    self.assertEqual(student.get_group(), group)
    self.assertEqual(student.get_status(), True)
    
    student.set_status(False)
    self.assertEqual(student.get_status(), False)

    new_name = "A"
    new_group = 345
    student_same_id = Student(studentID, new_name, new_group)
    self.assertEqual(student, student_same_id)

    new_name = "E"
    new_group = 567
    student.modify(new_name, new_group)
    self.assertEqual(student.get_name(), new_name)
    self.assertTrue(student.get_group() == new_group)

    string = "15;Mark;982"
    student = Student.from_string(string);
    self.assertEqual(student.get_id(), 15)
    self.assertEqual(student.get_name(), "Mark")
    self.assertEqual(student.get_group(), 982)

    string = str(student)
    self.assertEqual(string, "15;Mark;982")

    string = "name: Mark\ngroup: 982"
    student_string = student.to_print()

    self.assertEqual(student_string, string)

  
  def testValidate(self):
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
    self.assertRaisesRegex(ValidationError, "invalid id!\n", validator.validate, invalid_student)

    invalid_name = ""
    invalid_group = -6
    invalid_student = Student(invalid_studentID, invalid_name, invalid_group)
    self.assertRaisesRegex(ValidationError, "invalid id!\ninvalid name!\ninvalid group!\n", validator.validate, invalid_student)

  def testAddRepo(self):
    """
    function to test the process of adding a stundent in students repo
    """
    studentID = 15
    name = "G"
    group = 456
    student = Student(studentID, name, group)
    self.repo.store(student)
    self.assertTrue(len(self.repo) == 1)

    found_student = self.repo.search(studentID)
    self.assertTrue(student.get_id() == found_student.get_id())
    self.assertTrue(student.get_name() == found_student.get_name())
    self.assertTrue(student.get_group() == found_student.get_group())

    name_nou = "A"
    group_nou = 345
    student_same_id = Student(studentID, name_nou, group_nou)
    self.assertRaisesRegex(RepositoryError, "existent id!", self.repo.store, student_same_id) 

    absent_studentID = 10
    self.assertRaisesRegex(RepositoryError, "absent id!", self.repo.search, absent_studentID) 

  def testAddService(self):
    studentID = 15
    name = "G"
    group = 456
    repo = RepositoryStudents()  
    validator = ValidatorStudent()
    srv = ServiceStudents(validator, repo)
    
    assert srv.number_of_students() == 0
    srv.store(studentID, name, group)
    assert srv.number_of_students() == 1

    try:
      srv.store(studentID, name, group)
      assert False
    except RepositoryError as re:
      assert str(re) == "existent id!"
    
    invalid_studentID = -5
    invalid_name = ""
    invalid_group = -6

    try:
      srv.store(invalid_studentID, invalid_name, invalid_group) 
      assert False
    except ValidationError as ve:
      assert str(ve) == "invalid id!\ninvalid name!\ninvalid group!\n"

    studentID = 17
    name = "A"
    group = 217 
    srv.store(studentID, name, group)

    printable = srv.search(studentID)
    assert printable == "name: A\ngroup: 217"

  def testDeleteRepo(self):
    studentID = 15
    name = "G"
    group = 456
    student = Student(studentID, name, group)
    self.repo.store(student)
  
    studentID = 17
    name = "A"
    group = 455
    student = Student(studentID, name, group)
    self.repo.store(student)

    self.assertTrue(len(self.repo) == 2)

    self.repo.delete(studentID)
    self.assertEqual(len(self.repo), 1)

    absent_studentID = 7
    self.repo.delete(absent_studentID)
    self.assertTrue(len(self.repo) == 1)

  def testDeleteService(self):
    studentID = 15
    name = "G"
    group = 456
    
    self.srv.store(studentID, name, group)

    studentID1 = 16 
    name = "A"
    group = 455
    self.srv.store(studentID1, name, group)
    
    studentID2 = 14 
    name = "B"
    group = 455
    self.srv.store(studentID2, name, group)

    self.srv.delete(studentID1)
    self.assertTrue(self.srv.number_of_students() == 2)
   
    absent_studentID = 2
    self.assertRaisesRegex(RepositoryError, "absent id!", self.srv.delete, absent_studentID)

  def testAddService(self):
    studentID = 15
    name = "G"
    group = 456
    
    self.srv.store(studentID, name, group)

    new_studentID = 16
    new_name = "E"
    new_group = 456
    self.srv.store(new_studentID, new_name, new_group)

    modify_name = "H"
    modify_group = 15
    self.srv.modify(studentID, modify_name, modify_group)
    
    new_student = self.repo.search(studentID)
    self.assertTrue(new_student.get_name() == modify_name)
    self.assertTrue(new_student.get_group() == modify_group)

    self.srv.modify(new_studentID, None, modify_group)
    new_student = self.repo.search(new_studentID)
    self.assertTrue(new_student.get_name() == new_name)
    self.assertTrue(new_student.get_group() == modify_group)
  
  def testFileRepoStudents(self):
    studentID = 15
    name = "G"
    group = 912
    student = Student(studentID, name, group)

    filename = "testing/students_persistance_test.txt"

    self.file_repo.store(student)
    
    with open(filename, "r") as f:
      number = 0
      for line in f:
        number += 1
    self.assertEqual(number, 1)

    new_name = "E"
    new_group = 217
    self.file_repo.modify(studentID, new_name, new_group)

    with open(filename, "r") as f:
      string = f.readline().strip()
      self.assertEqual(string, "15;E;217")

    self.file_repo.delete(studentID)

    with open(filename, "r") as f:
      number = 0
      for line in f:
        number += 1
    self.assertTrue(number == 0)

  def testCreateStudentdto(self):
    name = "Mike"
    studentdto = StudentDTO(name)

    self.assertTrue(studentdto.get_name() == "Mike")

    studentdto.add_grade(Grade(0, 1, 2, 6))
    studentdto.add_grade(Grade(1, 2, 3, 15))
    self.assertEqual(len(studentdto), 2)
    self.assertAlmostEqual(studentdto.average(), 10.5)

  def run_all_tests(self):
    unittest.main()
