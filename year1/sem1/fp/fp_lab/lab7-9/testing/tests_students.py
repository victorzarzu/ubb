from domain.student import Student
from validation.validator_student import ValidatorStudent 
from errors.errors import ValidationError, RepositoryError
from infrastructure.repo_students import RepositoryStudents
from business.service_students import ServiceStudents

class TestsStudents:
  """
  class with tests for students
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
    assert student.get_name() == name
    assert student.get_group() == group

    new_name = "A"
    new_group = 345
    student_same_id = Student(studentID, new_name, new_group)
    assert student == student_same_id

    new_name = "E"
    new_group = 567
    student.modify(new_name, new_group)
    assert student.get_name() == new_name
    assert student.get_group() == new_group

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
    assert student.get_name() == found_student.get_name()
    assert student.get_group() == found_student.get_group()

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

  def __test_add_student_service(self):
    studentID = 15
    name = "G"
    group = 456
    repo = RepositoryStudents()  
    validator = ValidatorStudent()
    srv = ServiceStudents(validator, repo)
    
    srv.add_student(studentID, name, group)

    new_studentID = 16
    new_name = "E"
    new_group = 456
    srv.add_student(new_studentID, new_name, new_group)

    modify_name = "H"
    modify_group = 15
    srv.modify_student(studentID, modify_name, modify_group)
    
    new_student = repo.search_student_by_id(studentID)
    assert new_student.get_name() == modify_name
    assert new_student.get_group() == modify_group

    srv.modify_student(new_studentID, None, modify_group)
    new_student = repo.search_student_by_id(new_studentID)
    assert new_student.get_name() == new_name
    assert new_student.get_group() == modify_group
  
  def run_all_tests(self):
    self.__test_create_student()
    self.__test_validate_student()
    self.__test_add_student_repo()
    self.__test_delete_student_repo()
    self.__test_add_student_service()
    self.__test_delete_student_service()
