import business.svgs_filter as s_filter

def ui_filter_score(par_l):
  cmd = input().lstrip().rstrip()
  if cmd == "filter_1":
    div = input("divisible with: ")
    s_fiter.svg_filter_divisible_with(par_l, div)
  elif cmd == "filter_2":
    max_score = input("smaller than: ")
    s_filter.svg_filter_smaller_than(par_l, max_score)
  else:
    print("invalid command!")

