from errors.errors import ValidationError, RepositoryError
import datetime

class Console:
  def __init__(self, srv_students, srv_lab_problems, srv_grades):
    self.__srv_students = srv_students
    self.__srv_lab_problems = srv_lab_problems
    self.__srv_grades = srv_grades

  def __ui_add_student(self):
    try:
      studentID = int(input("id: "))
    except ValueError:
      print("invalid id!")
      return

    name = input("name: ")

    try:
      group = int(input("group: "))
    except ValueError:
      print("invalid group!")
      return

    self.__srv_students.store(studentID, name, group)

  def __ui_delete_student(self):
    try:
      studentID = int(input("id: "))
    except ValueError:
      print("invalid id!")
      return

    self.__srv_students.delete(studentID)

  def __ui_modify_student(self, cmd):
    name = None 
    group = None

    try:
      studentID = int(input("id: "))
    except ValueError:
      print("invalid id!")
      return

    if "name" in cmd:
      name = input("new name: ")

    if "group" in cmd:
      try:
        group = int(input("new group: "))
      except ValueError:
        print("invalid group!")
        return

    self.__srv_students.modify(studentID, name, group)

  def __ui_search_student(self):
    try:
      studentID = int(input("id: "))
    except ValueError:
      print("invalid id!")
      return
    
    student_print = self.__srv_students.search(studentID)
    print(student_print)

  def __ui_add_lab_problem(self):
    try:
      lab = int(input("lab: "))
    except ValueError:
      print("invalid lab!")
      return

    try:
      problem = int(input("problem: "))
    except ValueError:
      print("invalid problem!")
      return

    description = input("description: ")
    
    try:
      deadline = datetime.datetime.strptime(input("deadline(day month year): "), "%d %m %Y").date()
    except ValueError:
      print("invalid deadline!")
      return

    self.__srv_lab_problems.store(lab, problem, description, deadline)

  def __ui_delete_lab_problem(self):
    try:
      lab = int(input("lab: "))
    except ValueError:
      print("invalid lab!")
      return

    try:
      problem = int(input("problem: "))
    except ValueError:
      print("invalid problem!")
      return

    self.__srv_lab_problems.delete(lab, problem)

  def __ui_modify_lab_problem(self, cmd):
    description = None
    deadline = None

    try:
      lab = int(input("lab: "))
    except ValueError:
      print("invalid lab!")
    
    try:
      problem = int(input("lab: "))
    except ValueError:
      print("invalid problem!")
    
    if "description" in cmd:
      description = input("description: ")

    if "deadline" in cmd:
      try:
        deadline = datetime.datetime.strptime(input("deadline(day month year): "), "%d %m %Y").date()
      except ValueError:
        print("invalid deadline!")
    
    self.__srv_lab_problems.modify(lab, problem, description, deadline)
      
  def __ui_search_lab_problem(self):
    try:
      lab = int(input("lab: "))
    except ValueError:
      print("invalid id!")
      return

    try:
      problem = int(input("problem: "))
    except ValueError:
      print("invalid problem!")
      return

    lab_problem_print = self.__srv_lab_problems.search(lab, problem)
    print(lab_problem_print)

  def __ui_grade_student(self):
    try:
      studentID = int(input("student id: "))
    except ValueError:
      print("invalid student id!")
      return
    
    try:
      lab = int(input("lab: "))
    except ValueError:
      print("invalid lab!")
      return

    try:
      problem = int(input("problem: "))
    except ValueError:
      print("invalid problem!")
      return

    try:
      grade_number = float(input("grade: "))
    except ValueError:
      print("invalid grade!")
      return
    
    self.__srv_grades.grade(studentID, lab, problem, grade_number)

  def __ui_delete_grade(self):
    try:
      studentID = int(input("student id: "))
    except ValueError:
      print("invalid student id!")
      return
    
    try:
      lab = int(input("lab: "))
    except ValueError:
      print("invalid lab!")
      return

    try:
      problem = int(input("problem: "))
    except ValueError:
      print("invalid problem!")
      return

    self.__srv_grades.delete_grade(studentID, lab, problem)

  def __ui_modify_grade(self):
    try:
      studentID = int(input("student id: "))
    except ValueError:
      print("invalid student id!")
      return
    
    try:
      lab = int(input("lab: "))
    except ValueError:
      print("invalid lab!")
      return

    try:
      problem = int(input("problem: "))
    except ValueError:
      print("invalid problem!")
      return

    try:
      grade_number = float(input("grade: "))
    except ValueError:
      print("invalid grade!")
      return
    
    self.__srv_grades.modify_grade(studentID, lab, problem, grade_number)


  def __ui_add_random_students(self):
    self.__srv_students.store_random_students()

  def __ui_statistics_lab_problem(self):
    try:
      lab = int(input("lab: "))
    except ValueError:
      print("invalid lab!")
      return

    try:
      problem = int(input("problem: "))
    except ValueError:
      print("invalid lab!")
      return


    student_odts = self.__srv_grades.get_students_by_lab_problem(lab, problem)
    if len(student_odts) == 0:
      print("No students!")
      return

    for student in student_odts:
      print(str(student))


  def __ui_statistics_average(self):
    student_odts = self.__srv_grades.get_students_with_small_average()
    
    if len(student_odts) == 0:
      print("No students!")
      return

    for student in student_odts:
      print(str(student))

  def run(self):
    while True:
      try:
        cmd = input(">").strip()
        if cmd == "exit":
          return
        elif cmd == "":
          continue
        elif cmd == "add student":
          self.__ui_add_student()
        elif cmd == "delete student":
          self.__ui_delete_student()
        elif cmd == "search student":
          self.__ui_search_student()
        elif cmd == "add lab problem":
          self.__ui_add_lab_problem()
        elif cmd == "delete lab problem":
          self.__ui_delete_lab_problem()
        elif cmd == "search lab problem":
          self.__ui_search_lab_problem()
        elif "modify student" in cmd:
          if "name" in cmd or "group" in cmd:
            self.__ui_modify_student(cmd)
          else:
            print("incomplete command!")
        elif "modify lab problem" in cmd:
          if "description" in cmd or "deadline" in cmd:
            self.__ui_modify_lab_problem(cmd)
          else:
            print("incomplete command!")
        elif cmd == "grade student":
          self.__ui_grade_student()
        elif cmd == "delete grade":
          self.__ui_delete_grade()
        elif cmd == "modify grade":
          self.__ui_modify_grade()
        elif cmd == "add random students":
          self.__ui_add_random_students()
        elif cmd == "statistics lab problem":
          self.__ui_statistics_lab_problem()
        elif cmd == "statistics average":
          self.__ui_statistics_average()
        else:
          print("invalid command!")
      except ValidationError as ve:
        print("validation error: " + str(ve))
      except RepositoryError as re:
        print("repo error: " + str(re))
      except IOError as ioe:
        print("Couldn't make a persistent modification right now") 
