import comparators
from computes import compute_average

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
  par_l
  participant = create_participant(len(par_l), [6.2, 7, 7, 1, 4.5, 1.99], compute_average([6.2, 7, 7, 1, 4.5, 1.99]))
  add_participant_in_list(par_l, participant)
  participant = create_participant(len(par_l), [7, 8, 9], compute_average([7, 8, 9]))
  change_participant_by_id(par_l, 0, participant)
  assert get_participant_by_id(0) == participant

create_pariticipant_test()
get_participant_id_test()
get_participant_score_test()
get_participant_score_avg_test()
get_participant_by_id_test()
add_participant_in_list_test()
