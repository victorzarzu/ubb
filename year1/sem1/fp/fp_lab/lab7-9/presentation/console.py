from errors.errors import ValidationError, RepositoryError
import datetime

class Console:
  def __init__(self, srv_students, srv_lab_problems):
    self.__srv_students = srv_students
    self.__srv_lab_problems = srv_lab_problems

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

    self.__srv_students.add_student(studentID, name, group)

  def __ui_delete_student(self):
    try:
      studentID = int(input("id: "))
    except ValueError:
      print("invalid id!")
      return

    self.__srv_students.delete_student(studentID)

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

    self.__srv_lab_problems.add_lab_problem(lab, problem, description, deadline)

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

    self.__srv_lab_problems.delete_lab_problem(lab, problem)

  def run(self):
    while True:
      try:
        cmd = input(">").lstrip().rstrip()
        if cmd == "exit":
          return
        elif cmd == "":
          continue
        elif cmd == "add student":
          self.__ui_add_student()
        elif cmd == "delete student":
          self.__ui_delete_student()
        elif cmd == "add lab problem":
          self.__ui_add_lab_problem()
        elif cmd == "delete lab problem":
          self.__ui_delete_lab_problem()
        else:
          print("invalid command!")
      except ValidationError as ve:
         print("validation error " + str(ve))
      except RepositoryError as re:
         print("repo error: " + str(re))

