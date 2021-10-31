import business.svgs_filter as s_filter

def ui_filter_score(par_l, undo_stage):
  cmd = input().lstrip().rstrip()
  if cmd == "filter_1":
    div = input("multiple of: ")
    s_filter.svg_filter_divisible_with(par_l, div, undo_stage)
  elif cmd == "filter_2":
    max_score = input("smaller than: ")
    s_filter.svg_filter_smaller_than(par_l, max_score, undo_stage)
  else:
    print("invalid command!")

