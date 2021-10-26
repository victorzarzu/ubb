import business.svgs_print as s_print
import domain.participants as participants
import infrastructure.comparators as comparators
from infrastructure.strings import create_string_for_print

def ui_print_score(par_l):
  participants_stats = par_l[:]
  cmd = input().lstrip().rstrip()
  try:
    if cmd == "print_1":
      max_score = input("smaller than: ")
      participants_ = s_print.svg_create_participants_stats_by_comparer(participants_stats, comparators.comparer_smaller, max_score)
      stats = create_string_for_print(participants_)
      print(stats)
    elif cmd == "print_2":
      sort_mode = input("asc or desc: ")
      s_print.svg_sort_participants_stats_by_sort_mode(participants_stats, participants.get_participant_score_avg, sort_mode) 
      stats = create_string_for_print(participants_stats)
      print(stats)
    elif cmd == "print_3":
      min_score = input("bigger than: ")
      sort_mode = input("asc or desc: ")
      participants_ = s_print.svg_create_participants_stats_by_comparer(participants_stats, comparators.comparer_bigger, min_score)
      s_print.svg_sort_participants_stats_by_sort_mode(participants_, participants.get_participant_score_avg, sort_mode) 
      stats = create_string_for_print(participants_)
      print(stats)
    else:
      print("invalid command!")
  except Exception as ex:
    print(ex)
  pass
