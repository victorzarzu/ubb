import infrastructure.comparators
from validation.validations import validate_score_print
from infrastructure.computes import compute_average
import infrastructure.comparators as comparators

oo = 0x3f3f3f3f

def create_participant(id_number, score_l, score_avg):
  """ function that creates a participant
  params: id_number - an integer; score_l - a float list; score_avg - a float
  output: a dictionary item
  """
  return {
    'id': id_number,
    'score': score_l,
    'score_avg': score_avg
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
  return: a list of floats representing the participant score
  """
  return participant['score']

def get_participant_score_avg(participant):
  """
  funtion that returns the average score of a participant
  params: participant - a participant item
  return: a float representing the average score of the participant
  """
  return participant['score_avg']

def get_participant_by_id(par_l, id_number):
  """
  a function that returns the list of scores of the id_number-th participant
  params: par_l - a list of list of floats; id_number - an integer
  return: a list of floats, if the id_number is a correct id
  raises: Exception with text
          "invalid contest id!" if the id_number is not a valid id
  """
  return par_l[id_number]

def add_participant_in_list(par_l, participant):
  """
  function that adds a participant to par_l
  params: par_l - a list of list of floats; participant - a participant item
  return: -
  """
  par_l.append(participant)


def change_participant_by_id(par_l, id_number, participant):
  """
  function that changes the participant with id_number in par_l list with participant
  params: par_l - a list of participant items; id_numer - an integer; participant - a participant item
  return: -
  """
  par_l[id_number] = participant

def participant_to_str(participant):
  """
  functions that makes a displayable participant string
  params: participant - a participant item
  return: a string
  """
  par_str = ""
  participant_id = get_participant_id(participant)
  participant_score_avg = get_participant_score_avg(participant)
  if validate_score_print(participant_score_avg):
    par_str += "id: " + str(participant_id) + "\n"
    par_str += "score: " + "{:.2f}".format(participant_score_avg) + "\n"
  return par_str
 

def insert_score_by_participant_id(par_l, id_number, score_l):
  """
  function that adds the scores in the score_l into the score list coresponding to the id_number-th participant
  params: par_l - a list of participant items; id_number - integer; score_l - a list of floats
  return: -
  """
  participant = get_participant_by_id(par_l, id_number)
  participant_score = get_participant_score(participant)
  participant_score.extend(score_l)
  participant = create_participant(id_number, participant_score, compute_average(participant_score))
  change_participant_by_id(par_l, id_number, participant)
  
def delete_participant_score_by_id(par_l, id_number):
  """
  function that deletes the score list of the id_numer-th participant
  params: par_l - a list of participant items; id_number - an integer
  return: -, if the deletion is complete
  """
  participant = create_participant(id_number, [], 0)
  change_participant_by_id(par_l, id_number, participant)

def delete_participant_score_by_id_interval(par_l, id_interval):
  """
  function that deletes the score list of the participants that have an id in id_interval
  par_l: par_l - a list of participant; id_interval - a list of 2 integers
  return -, if the deletion is complete
  """
  for i in range(id_interval[0], id_interval[1] + 1):
    delete_participant_score_by_id(par_l, i)

def replace_participant_score_by_id(par_l, id_number, score_l):
  """
  function that replaces the score in the par_l of the id_number-th participant with score_l score list
  params: par_l - a list of lists of floats; id_numer - an integer; score_l - a list of floats
  return: -
  """
  participant = create_participant(id_number, score_l, compute_average(score_l))
  change_participant_by_id(par_l, id_number, participant)

def filter_participants_by_comparer(par_l, comparer, argument):
  """
  function that modifies par_l filtering participants with a score that satisfies the comparer
  params: par_l - a list of participant items; comparer - a comparer function; argument - a float number 
  return: -  
  """
  for participant in par_l:
    participant_score_avg = get_participant_score_avg(participant)
    participant_id = get_participant_id(participant)
    if not comparer(participant_score_avg, argument):
      participant_modify = create_participant(participant_id, [], oo)
      change_participant_by_id(par_l, participant_id, participant_modify)


def create_pariticipant_test():
  participant = create_participant(4, [8.9], 8.9)
  assert participant == {'id': 4, 'score': [8.9], 'score_avg': 8.9}
  participant = create_participant(0, [7.6], 7.6)
  assert participant == {'id': 0, 'score': [7.6], 'score_avg': 7.6}

def get_participant_id_test():
  participant = create_participant(6, [5, 2, 1, 7], 3.75)
  participant_id = get_participant_id(participant)
  assert participant_id == 6

  participant = create_participant(0, [10, 10, 10], 10)
  participant_id = get_participant_id(participant)
  assert participant_id == 0

def get_participant_score_test():
  participant = create_participant(6, [5, 2, 1, 7], 3.75)
  participant_score = get_participant_score(participant)
  assert participant_score == [5, 2, 1, 7]

  participant = create_participant(0, [10, 10, 10], 10)
  participant_score = get_participant_score(participant)
  assert participant_score == [10, 10, 10] 

def get_participant_score_avg_test():
  participant = create_participant(6, [5, 2, 1, 7], 3.75)
  participant_score_avg = get_participant_score_avg(participant)
  assert participant_score_avg == 3.75

  participant = create_participant(0, [10, 10, 10], 10)
  participant_score_avg = get_participant_score_avg(participant)
  assert participant_score_avg == 10 


def get_participant_by_id_test():
  par_l = []
  add_participant_in_list(par_l, create_participant(len(par_l), [5, 5, 5, 5, 7], compute_average([5, 5, 5, 5, 5, 7])))
  add_participant_in_list(par_l, create_participant(len(par_l), [9, 9.9, 9.423, 5, 1, 9], compute_average([9, 9.9, 9.423, 5, 1, 9])))
  add_participant_in_list(par_l, create_participant(len(par_l), [1, 2, 3, 4, 5, 6], compute_average([1, 2, 3, 4, 5, 6])))
  add_participant_in_list(par_l, create_participant(len(par_l), [1], 1))

  participant = get_participant_by_id(par_l, 2)
  
  participant_id = get_participant_id(participant)
  assert participant_id == 2
  participant_score = get_participant_score(participant)
  assert participant_score == [1, 2, 3, 4, 5, 6]
  participant_score_avg = get_participant_score_avg(participant)
  assert participant_score_avg == 3.5

def add_participant_in_list_test():
  par_l = []
  participant = create_participant(len(par_l), [6.2, 7, 7, 1, 4.5, 1.99], compute_average([6.2, 7, 7, 1, 4.5, 1.99]))
  add_participant_in_list(par_l, participant)
  assert len(par_l) == 1
  assert par_l[0] == {'id': 0, 'score': [6.2, 7, 7, 1, 4.5, 1.99], 'score_avg': compute_average([6.2, 7, 7, 1, 4.5, 1.99])}

def change_participant_by_id_test():
  par_l = []
  participant = create_participant(len(par_l), [6.2, 7, 7, 1, 4.5, 1.99], compute_average([6.2, 7, 7, 1, 4.5, 1.99]))
  add_participant_in_list(par_l, participant)
  participant = create_participant(len(par_l), [7, 8, 9], compute_average([7, 8, 9]))
  change_participant_by_id(par_l, 0, participant)
  assert get_participant_by_id(0) == participant

def participant_to_str_test():
  participant = create_participant(0, [1, 2, 3], 2)
  par_str = participant_to_str(participant)
  assert par_str == "id: 0\nscore: 2.00\n"

def insert_score_by_participant_id_test():
  par_l = []
  add_participant_in_list(par_l, create_participant(len(par_l), [5, 5, 5, 5, 7], compute_average([5, 5, 5, 5, 5, 7])))
  add_participant_in_list(par_l, create_participant(len(par_l), [9, 9.9, 9.423, 5, 1, 9], compute_average([9, 9.9, 9.423, 5, 1, 9])))
  add_participant_in_list(par_l, create_participant(len(par_l), [1, 2, 3, 4, 5, 999], compute_average([1, 2, 3, 4, 5, 999])))
  add_participant_in_list(par_l, create_participant(len(par_l), [1], 1))


  insert_score_by_participant_id(par_l, 0, [5, 9.1, 6.7])
  participant = get_participant_by_id(par_l, 0)
  assert get_participant_score(participant) == [5, 5, 5, 5, 7, 5, 9.1, 6.7]

def delete_participant_score_by_id_test():
  par_l = []
  participant = create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  add_participant_in_list(par_l, participant)
  participant = create_participant(1, [1.6, 1.8, 1, 10], compute_average([1.6, 1.8, 1, 10]))
  add_participant_in_list(par_l, participant)
  participant = create_participant(2, [6, 7.66, 9.9999, 1], compute_average([6, 7.66, 9.9999, 1]))
  add_participant_in_list(par_l, participant)
  delete_participant_score_by_id(par_l, 1)

  assert len(par_l) == 3
  assert par_l == [{'id': 0, 'score': [1, 6, 9, 10], 'score_avg': 6.5}, {'id': 1, 'score': [], 'score_avg': 0}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': 6.164975}]

  delete_participant_score_by_id(par_l, 0)
  assert par_l == [{'id': 0, 'score': [], 'score_avg': 0}, {'id': 1, 'score': [], 'score_avg': 0}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': 6.164975}]


def delete_participant_score_by_id_interval_test():
  par_l = []
  participant = create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  add_participant_in_list(par_l, participant)
  participant = create_participant(1, [5], compute_average([5]))
  add_participant_in_list(par_l, participant)
  participant = create_participant(2, [9], compute_average([9]))

  add_participant_in_list(par_l, participant)
  participant = create_participant(3, [5, 6], compute_average([5, 6]))
  add_participant_in_list(par_l, participant)
  participant = create_participant(4, [1, 6.77, 4, 7, 7, 9], compute_average([1, 6.77, 4, 7, 7, 9]))
  add_participant_in_list(par_l, participant)

  delete_participant_score_by_id_interval(par_l, [1, 3])
  assert par_l == [{'id': 0, 'score': [1, 6, 9, 10], 'score_avg': compute_average([1, 6, 9, 10])}, {'id': 1, 'score' : [], 'score_avg': 0}, {'id': 2, 'score' : [], 'score_avg': 0}, {'id': 3, 'score' : [], 'score_avg': 0}, {'id': 4, 'score': [1, 6.77, 4, 7, 7, 9], 'score_avg': compute_average([1, 6.77, 4, 7, 7, 9])}]

def replace_participant_score_by_id_test():
  par_l = []
  participant = create_participant(0, [1, 6, 9, 10], compute_average([1, 6, 9, 10]))
  add_participant_in_list(par_l, participant)
  participant = create_participant(1, [1.6, 1.8, 1, 10], compute_average([1.6, 1.8, 1, 10]))
  add_participant_in_list(par_l, participant) 
  participant = create_participant(2, [6, 7.66, 9.9999, 1], compute_average([6, 7.66, 9.9999, 1]))
  add_participant_in_list(par_l, participant)

  replace_participant_score_by_id(par_l, 0, [1, 1])
  assert par_l == [{'id': 0, 'score' : [1, 1], 'score_avg': compute_average([1, 1])}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg' : compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [6, 7.66, 9.9999, 1], 'score_avg': compute_average([6, 7.66, 9.9999, 1])}]

  replace_participant_score_by_id(par_l, 2, [1, 6])
  assert par_l == [{'id': 0, 'score' : [1, 1], 'score_avg': compute_average([1, 1])}, {'id': 1, 'score': [1.6, 1.8, 1, 10], 'score_avg' : compute_average([1.6, 1.8, 1, 10])}, {'id': 2, 'score': [1, 6], 'score_avg': compute_average([1, 6])}]

def filter_participants_by_comparer_test():
  par_l = []
  participant = create_participant(len(par_l), [8, 9, 9], compute_average([8, 9, 9]))
  add_participant_in_list(par_l, participant)
  participant = create_participant(len(par_l), [1, 1, 1, 1], compute_average([1, 1, 1, 1]))
  add_participant_in_list(par_l, participant)
  participant = create_participant(len(par_l), [6, 7, 8], compute_average([6, 7, 8]))
  add_participant_in_list(par_l, participant)
  filter_participants_by_comparer(par_l, comparators.comparer_smaller, 7.001)
  assert par_l == [{'id': 0, 'score': [], 'score_avg': oo}, {'id': 1, 'score': [1, 1, 1, 1], 'score_avg': 1}, {'id': 2, 'score': [6, 7, 8], 'score_avg': 7}]
  filter_participants_by_comparer(par_l, comparators.comparer_divisible, compute_average([8, 9, 9]) / 7)
  assert par_l == [{'id': 0, 'score': [], 'score_avg': oo}, {'id': 1, 'score': [], 'score_avg': oo}, {'id': 2, 'score': [], 'score_avg': oo}]

delete_participant_score_by_id_test()
delete_participant_score_by_id_interval_test()
replace_participant_score_by_id_test()
create_pariticipant_test()
get_participant_id_test()
get_participant_score_test()
get_participant_score_avg_test()
get_participant_by_id_test()
add_participant_in_list_test()
participant_to_str_test()
insert_score_by_participant_id_test()
filter_participants_by_comparer_test()
