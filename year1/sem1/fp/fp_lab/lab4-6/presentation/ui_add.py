import business.svgs_add as s_add
  
def ui_add_score(par_l, max_scores):
  cmd = input().rstrip().lstrip()
  if cmd == "add":
    score_l = input("scores: ")
    s_add.svg_add_score(par_l, score_l, max_scores)
  elif cmd == "insert":
    id_number = input("id: ") 
    score_l = input("scores: ")
    s_add.svg_insert_score(par_l, score_l, id_number, max_scores)
  else:
    print("invalid command!")
