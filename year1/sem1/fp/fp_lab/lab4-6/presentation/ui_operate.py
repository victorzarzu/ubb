import business.svgs_operate as s_operate

def ui_operate_score(par_l):
  cmd = input().lstrip().rstrip()  
  if cmd == "avg_int":
    id_interval = input("id interval: ")
    average = s_operate.svg_participants_average_by_id_interval(par_l, id_interval)
    print("{:.2f}".format(average)) 
  elif cmd == "min_int":
    id_interval = input("id interval: ")
    minimum = s_operate.svg_minimum_score_by_interval(par_l, id_interval)
    print("{:.2f}".format(minimum))
  elif cmd == "mul_10":
    id_interval = input("id interval: ")
    ids = s_operate.svg_participant_ids_if_multiple(par_l, id_interval, 10)
    print(ids)
  else:
    print("invalid command!")

