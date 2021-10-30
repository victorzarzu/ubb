from presentation.ui_add import ui_add_score
from presentation.ui_print import ui_print_score
from presentation.ui_modify import ui_modify_score
#from print import ui_print_score
from presentation.ui_filter import ui_filter_score
from presentation.ui_operate import ui_operate_score
import domain.undos as undos

def ui():
  par_l = []
  undo = []
  max_scores = 10
  while True:
    undo_stage = []
    try:
      cmd = input().rstrip().lstrip()
      if cmd == "exit":
        break
      if cmd == "1":
        ui_add_score(par_l, max_scores, undo_stage)
      elif cmd == "2":
        ui_modify_score(par_l, max_scores, undo_stage)
      elif cmd == "3":
        ui_print_score(par_l)
      elif cmd == "4":
        ui_operate_score(par_l)
      elif cmd == "5":
        ui_filter_score(par_l, undo_stage)
      elif cmd == "6":
        undos.execute_last_undo_stage(undo)  
      else:
        print("invalid command!")

      undos.add_undo_stage_in_undo(undo, undo_stage)
    except Exception as ex:
      print(ex)
  
def main():
  ui()


main()
