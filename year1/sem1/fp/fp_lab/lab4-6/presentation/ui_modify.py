import business.svgs_modify as s_modify

def ui_modify_score(par_l, max_scores, undo_stage):
  cmd = input().lstrip().rstrip()
  if cmd == "del_id":
    id_number = input("id: ")
    s_modify.svg_delete_participant_score(par_l, id_number, undo_stage)
  elif cmd == "del_int_id":
    id_interval = input("id interval: ")
    s_modify.svg_delete_participant_interval_score(par_l, id_interval, undo_stage)
  elif cmd == "replace_id":
    id_number = input("id: ")
    score_l = input("scores: ")
    s_modify.svg_replace_participant_score(par_l, id_number, score_l, max_scores, undo_stage)
  else:
    print("invalid command!")
