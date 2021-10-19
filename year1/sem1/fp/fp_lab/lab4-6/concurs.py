from add import ui_add_score
from modify import ui_modify_score
from order import ui_print_score

def ui():
  par_l = []
  max_scores = 10
  while True:
    cmd = input().rstrip().lstrip()
    if cmd == "exit":
      break
    if cmd == "1":
      try:
        ui_add_score(par_l, max_scores)
      except Exception as ex:
        print(ex)
    elif cmd == "2":
      try:
        ui_modify_score(par_l, max_scores)
      except Exception as ex:
        print(ex)
    elif cmd == "3":
      try:
        ui_print_score(par_l)
      except Exception as ex:
        print(ex)
    else:
      print("comanda invalida!")

def main():
  ui()


main()
