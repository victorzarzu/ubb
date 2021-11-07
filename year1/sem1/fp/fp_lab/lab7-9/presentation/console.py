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

  def run(self):
    while True:
      cmd = input(">").lstrip().rstrip()
      if cmd == "exit":
        return
      elif cmd == "":
        continue
      elif cmd == "add student":
        try:
          self.__ui_add_student()
        except ValidationError as ve:
          print("validation error " + str(ve))
        except RepositoryError as re:
          print("repo error: " + str(re))
      elif cmd == "add lab problem":
        try:
          self.__ui_add_lab_problem()
        except ValidationError as ve:
          print("validation error: " + str(ve))
        except RepositoryError as re:
          print("repo error: " + str(re))
      else:
        print("invalid command!")
