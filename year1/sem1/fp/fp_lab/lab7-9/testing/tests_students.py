from domain.student import Student
from domain.student_dto import StudentDTO
from domain.grade import Grade
from domain.student_grade import StudentGrade
from validation.validator_student import ValidatorStudent 
from errors.errors import ValidationError, RepositoryError
from infrastructure.repo_students import RepositoryStudents
from business.service_students import ServiceStudents
from infrastructure.file_repo_students import FileRepositoryStudents

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
    assert student.get_status() == True

    student.set_status(False)
    assert student.get_status() == False

    new_name = "A"
    new_group = 345
    student_same_id = Student(studentID, new_name, new_group)
    assert student == student_same_id

    new_name = "E"
    new_group = 567
    student.modify(new_name, new_group)
    assert student.get_name() == new_name
    assert student.get_group() == new_group

    string = "15;Mark;982"
    student = Student.from_string(string);
    assert student.get_id() == 15
    assert student.get_name() == "Mark"
    assert student.get_group() == 982

    string = str(student)
    assert string == "15;Mark;982"

    string = "name: Mark\ngroup: 982"
    student_string = student.to_print()
    assert student_string == string

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

  def __test_add_repo(self):
    """
    function to test the process of adding a stundent in students repo
    """
    studentID = 15
    name = "G"
    group = 456
    student = Student(studentID, name, group)
    repo = RepositoryStudents()
    repo.store(student)
    assert len(repo) == 1

    found_student = repo.search(studentID)
    assert student.get_id() == found_student.get_id()
    assert student.get_name() == found_student.get_name()
    assert student.get_group() == found_student.get_group()

    name_nou = "A"
    group_nou = 345
    student_same_id = Student(studentID, name_nou, group_nou)
    
    try:
      repo.store(student_same_id)
      assert False
    except RepositoryError as re:
      assert str(re) == "existent id!"

    absent_studentID = 10
    try:
      found_student = repo.search(absent_studentID)
      assert False
    except RepositoryError as re:
      assert str(re) == "absent id!"
  

  def __test_add_service(self):
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

  def __test_delete_repo(self):
    studentID = 15
    name = "G"
    group = 456
    student = Student(studentID, name, group)
    repo = RepositoryStudents()
    repo.store(student)
  
    studentID = 17
    name = "A"
    group = 455
    student = Student(studentID, name, group)
    repo.store(student)

    assert len(repo) == 2

    repo.delete(studentID)
    assert len(repo) == 1

    absent_studentID = 7
    repo.delete(absent_studentID)
    assert len(repo) == 1

  def __test_delete_service(self):
    studentID = 15
    name = "G"
    group = 456
    repo = RepositoryStudents()  
    validator = ValidatorStudent()
    srv = ServiceStudents(validator, repo)
    
    srv.store(studentID, name, group)

    studentID1 = 16 
    name = "A"
    group = 455
    srv.store(studentID1, name, group)
    
    studentID2 = 14 
    name = "B"
    group = 455
    srv.store(studentID2, name, group)

    srv.delete(studentID1)
    assert srv.number_of_students() == 2
   
    absent_studentID = 2
    try:
      srv.delete(absent_studentID)
      assert False
    except RepositoryError as re:
      assert str(re) == "absent id!"

  def __test_add_service(self):
    studentID = 15
    name = "G"
    group = 456
    repo = RepositoryStudents()  
    validator = ValidatorStudent()
    srv = ServiceStudents(validator, repo)
    
    srv.store(studentID, name, group)

    new_studentID = 16
    new_name = "E"
    new_group = 456
    srv.store(new_studentID, new_name, new_group)

    modify_name = "H"
    modify_group = 15
    srv.modify(studentID, modify_name, modify_group)
    
    new_student = repo.search(studentID)
    assert new_student.get_name() == modify_name
    assert new_student.get_group() == modify_group

    srv.modify(new_studentID, None, modify_group)
    new_student = repo.search(new_studentID)
    assert new_student.get_name() == new_name
    assert new_student.get_group() == modify_group
  
  def __test_file_repo_students(self):
    repo = RepositoryStudents()  
    filename = "testing/students_persistance_test.txt"
    object_class = Student
    separators = ";"

    repo_persistance = RepositoryPersistance(repo, filename, object_class, separators)
    repo_persistance.load()
    assert len(repo) == 4

    studentID = 99
    repo.delete(studentID)
    studentID = 99 
    name = "Eric"
    group = 124
    student = Student(studentID, name, group)
    repo.store(student)

    repo_persistance.store()
    repo_persistance.load()

    repo1 = RepositoryStudents()
    repo_persistance1 = RepositoryPersistance(repo1, filename, object_class, separators)
    repo_persistance1.load()
    assert len(repo1) == 4
  """  
  
  """
  def __test_file_repo_students(self):
    studentID = 15
    name = "G"
    group = 912
    student = Student(studentID, name, group)

    filename = "testing/students_persistance_test.txt"

    repo = FileRepositoryStudents(filename)
    repo.store(student)
    
    with open(filename, "r") as f:
      number = 0
      for line in f:
        number += 1
    assert number == 1

    new_name = "E"
    new_group = 217
    repo.modify(studentID, new_name, new_group)

    with open(filename, "r") as f:
      string = f.readline().strip()
      assert string == "15;E;217"

    repo.delete(studentID)

    with open(filename, "r") as f:
      number = 0
      for line in f:
        number += 1
    assert number == 0

  def __test_create_studentdto(self):
    name = "Mike"
    studentdto = StudentDTO(name)

    assert studentdto.get_name() == "Mike"

    studentdto.add_grade(Grade(0, 1, 2, 6))
    studentdto.add_grade(Grade(1, 2, 3, 15))
    assert len(studentdto) == 2
    assert studentdto.average() - 10.5 <= 0.0000001

  def __test_create_student_grade(self):
    studentID = 5
    lab = 7
    problem = 7
    grade = 7.8
  
    student_grade = StudentGrade(studentID, lab, problem, grade)
    assert student_grade.get_student_id() == studentID
    assert student_grade.get_lab() == lab
    assert student_grade.get_problem() == problem 
    assert student_grade.get_grade() == grade

    name = "Mike"
    student_grade.set_student_name(name)
    assert student_grade.get_student_name() == name



  def run_all_tests(self):
    self.__test_create_student()
    self.__test_validate_student()
    self.__test_add_repo()
    self.__test_delete_repo()
    self.__test_add_service()
    self.__test_delete_service()
    self.__test_file_repo_students()
    self.__test_create_studentdto()
    self.__test_create_student_grade()
