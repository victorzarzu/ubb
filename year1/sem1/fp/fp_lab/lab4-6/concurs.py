from add import ui_add_score
from modify import ui_modify_score

from validations import validate_score, validate_sort_mode
from conversions import convert_score
from computes import compute_average
from add import get_score_by_participant_id
import comparares

epsilon = 0.00000001

def create_participant(id_number, score):
  """
  function that creates a participant
  params: id_number - an integer; score - a float
  output: a dictionary item
  """
  return {
    'id': id_number,
    'score': score
  }

def get_participant_id(participant):
  """
  funtion that returns the id of a participant
  params: participant - a participant item
  return: an integer representing the participant id
  """
  return participant['id']

def get_participant_score(participant):
  """
  funtion that returns the score of a participant
  params: participant - a participant item
  return: an score representing the participant score
  """
  return participant['score']

def add_participant_in_participants_stats(participants_stats, participant):
  """
  function that adds a participant in the participants_stats list
  params: participants_stats - a list of participant items; participant - a participant item
  return: -
  """
  participants_stats.append(participant)

def sort_participants_stats(participants_stats, sort_mode, sort_key):
  """
  function that sorts the participants_stats array by score in sort_mode order
  params: participants_stats - a list of participant items; sort_mode - a string
  return: -
  """
  participants_stats.sort(key = sort_key) if sort_mode == "asc" else participants_stats.sort(key = sort_key, reverse = True)


def create_participants_list_with_score_that_satisfies_comparer(participants_stats, max_score, comparer):
  """
  function that returns the list of participants that have a score smaller than max_score
  params: participants_stats - a list of participant items; max_score - a float
  return: a list of participant items
  """
  max_score = convert_score(max_score)
  validate_score(max_score)
  participants_stats_with_score_smaller = []
  for participant in participants_stats:
    if comparer(get_participant_score(participant), max_score):
      add_participant_in_participants_stats(participants_stats_with_score_smaller, participant)
  return participants_stats_with_score_smaller

def print_participants_stats(participants_stats):
  """
  function that prints the id and score of all participants in participants_stats list
  params: participants_stats - a list of participant items
  return: -
  """
  stats = ""
  for participant in participants_stats:
    stats += "id : " + str(get_participant_id(participant)) + "\n"
    stats += "score : " + str(get_participant_score(participant)) + "\n"
  stats = stats[:-1]
  print(stats)

def create_participants_stats(par_l):
  """
  function that creates participants_stats based on par_l list
  params: par_l - a list of lists of floats
  return: a list of participant items
  """
  participants_stats = []
  for index in range(len(par_l)):
    average_score = compute_average(par_l[index])
    participant = create_participant(index, average_score)
    add_participant_in_participants_stats(participants_stats, participant)
  return participants_stats

def create_ordered_participants_stats(participants_stats, sort_mode, sort_key):
  """
  function that computes and returns a list of participants that is sorted in sort_mode order
  params: participants_stats - a list of participant items; sort_mode - a string
  return: a list of participant items sorted in the desired order
  """
  validate_sort_mode(sort_mode)
  sort_participants_stats(participants_stats, sort_mode, sort_key)
  return participants_stats

def create_ordered_participants_stats_bigger(participants_stats, sort_mode, sort_key, min_score, comparer):
  """
  function that computes and returns the list of participants that have a score bigger than min_score and are orderd in sort_mod mode
  params: participants_stats - a list of participant items; sort_mode - a string; min_score - a float
  return: a list of participants items that are sorted in the desired order and have a score biffer than min_score
  """
  validate_sort_mode(sort_mode)
  min_score = convert_score(min_score)
  validate_score(min_score)
  participants_bigger = create_participants_list_with_score_that_satisfies_comparer(participants_stats, min_score, comparer)
  sort_participants_stats(participants_bigger, sort_mode, sort_key)
  return participants_bigger

def ui_print_score(par_l):
  participants_stats = create_participants_stats(par_l)
  cmd = input().lstrip().rstrip()
  if cmd == "print_1":
    try:
      max_score = input("smaller than: ")
      participants = create_participants_list_with_score_that_satisfies_comparer(participants_stats, max_score, comparares.comparer_smaller)
      print_participants_stats(participants)
    except Exception as ex:
      print(ex)
      return
  elif cmd == "print_2":
    try:
      sort_mode = input("asc or desc: ")
      participants = create_ordered_participants_stats(participants_stats, sort_mode, get_participant_score)
      print_participants_stats(participants)
    except Exception as ex:
      print(ex)
  elif cmd == "print_3":
    try:
      min_score = input("bigger than: ")
      sort_mode = input("asc or desc: ")
      participants = create_ordered_participants_stats_bigger(participants_stats, sort_mode, get_participant_score, min_score, comparares.comparer_bigger)
      print_participants_stats(participants)
    except Exception as ex:
      print(ex)
  else:
    print("invalid command!")

def create_participant_test():
  participant = create_participant(4, 8.9)
  assert participant == {'id': 4, 'score': 8.9}

  participant = create_participant(0, 7.6)
  assert participant == {'id': 0, 'score': 7.6}

def add_participant_in_participants_stats_test():
  participants_stats = []
  participant = create_participant(4, 8.9)
  add_participant_in_participants_stats(participants_stats, participant) 
  assert len(participants_stats) == 1
  assert get_participant_id(participants_stats[0]) == get_participant_id(participant)
  assert abs(get_participant_score(participants_stats[0]) - get_participant_score(participant)) < epsilon
  
def sort_participants_stats_test():
  participants_stats = []
  add_participant_in_participants_stats(participants_stats, create_participant(4, 8.9))
  add_participant_in_participants_stats(participants_stats, create_participant(2, 8.89))
  add_participant_in_participants_stats(participants_stats, create_participant(3, 5))
  sort_participants_stats(participants_stats, "asc", get_participant_score)
  assert participants_stats == [{'id': 3, 'score': 5}, {'id': 2, 'score': 8.89}, {'id': 4, 'score': 8.9}]
  sort_participants_stats(participants_stats, "desc", get_participant_score)
  assert participants_stats == [{'id': 4, 'score': 8.9}, {'id': 2, 'score': 8.89}, {'id': 3, 'score': 5}]

def create_participants_stats_test():
  par_l = [[6, 6], [5, 5], [1, 2], [8, 9]]
  participants_stats = create_participants_stats(par_l)
  assert len(participants_stats) == 4

def create_participants_list_with_score_that_satisfies_comparer_test():
  participants_stats = []
  add_participant_in_participants_stats(participants_stats, create_participant(4, 8.9))
  add_participant_in_participants_stats(participants_stats, create_participant(2, 8.89))
  add_participant_in_participants_stats(participants_stats, create_participant(3, 5))
  add_participant_in_participants_stats(participants_stats, create_participant(7, 6.35))
  participants_with_score_smaller = create_participants_list_with_score_that_satisfies_comparer(participants_stats, 6.4, comparares.comparer_smaller)
  assert len(participants_with_score_smaller) == 2
  #print_participants_stats(participants_with_score_smaller)

def create_ordered_participants_stats_test():
  participants_stats = []
  add_participant_in_participants_stats(participants_stats, create_participant(4, 8.9))
  add_participant_in_participants_stats(participants_stats, create_participant(2, 8.89))
  add_participant_in_participants_stats(participants_stats, create_participant(3, 5))
  add_participant_in_participants_stats(participants_stats, create_participant(7, 6.35))
  participants_stats = create_ordered_participants_stats(participants_stats, "asc", get_participant_score)
  assert participants_stats == [{'id': 3, 'score': 5},  {'id': 7, 'score': 6.35}, {'id': 2, 'score': 8.89}, {'id': 4, 'score': 8.9}]

def create_ordered_participants_stats_bigger_test():
  participants_stats = []
  add_participant_in_participants_stats(participants_stats, create_participant(4, 8.9))
  add_participant_in_participants_stats(participants_stats, create_participant(2, 8.89))
  add_participant_in_participants_stats(participants_stats, create_participant(3, 5))
  add_participant_in_participants_stats(participants_stats, create_participant(7, 6.35))
  participants_stats = create_ordered_participants_stats_bigger(participants_stats, "asc", get_participant_score, 6.34, comparares.comparer_bigger)
  assert participants_stats == [{'id': 7, 'score': 6.35}, {'id': 2, 'score': 8.89}, {'id': 4, 'score': 8.9}]
  participants_stats = create_ordered_participants_stats_bigger(participants_stats, "desc", get_participant_score, 6.34, comparares.comparer_bigger)
  assert participants_stats == [{'id': 4, 'score': 8.9}, {'id': 2, 'score': 8.89}, {'id': 7, 'score': 6.35}]

create_participant_test()
add_participant_in_participants_stats_test()
sort_participants_stats_test()
create_participants_stats_test()
create_participants_list_with_score_that_satisfies_comparer_test()
create_ordered_participants_stats_test()
create_ordered_participants_stats_bigger_test()

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
