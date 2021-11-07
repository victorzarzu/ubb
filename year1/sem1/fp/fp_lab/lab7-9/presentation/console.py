from errors.errors import ValidationError, RepositoryError

class Console:
  def __init__(self, srv_students):
    self.__srv_students = srv_students


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
          print("validation error + str(ve)")
        except RepositoryError as re:
          print("repo error: " + str(re))
      else:
        print("invalid command!")
