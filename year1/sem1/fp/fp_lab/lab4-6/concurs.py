from presentation.ui_add import ui_add_score
from presentation.ui_print import ui_print_score
from presentation.ui_modify import ui_modify_score
#from print import ui_print_score
from presentation.ui_filter import ui_filter_score
from presentation.ui_operate import ui_operate_score

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
    elif cmd == "4":
      try:
        ui_operate_score(par_l)
      except Exception as ex:
        print(ex)
    elif cmd == "5":
      try:
        ui_filter_score(par_l)
      except Exception as ex:
        print(ex)
    else:
      print("invalid command!")

def main():
  ui()


main()
