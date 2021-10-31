import infrastructure.comparators
from validation.validations import validate_score_print
from infrastructure.computes import compute_average
import infrastructure.comparators as comparators
import domain.undos as undos
from infrastructure.constants import oo

def create_participant(id_number, score_l):
  """ function that creates a participant
  params: id_number - an integer; score_l - a list of floats 
  output: a dictionary item
  """
  return {
    'id': id_number,
    'score': score_l,
    'score_avg': compute_average(score_l)
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
  params: par_l - a list of list of floats; participant - a participant item; undo - list of undo_operation items
  return: -
  """ 

  par_l.append(participant)

def remove_participant_from_list(par_l):
  """
  function that deletes the last participant from the par_l list
  params: par_l - a list of participant items
  return: -
  """
  par_l.pop()

def change_participant_by_id(par_l, id_number, participant, undo_stage):
  """
  function that changes the participant with id_number in par_l list with participant
  params: par_l - a list of participant items; id_numer - an integer; participant - a participant item; undo_stage - a list of undo_operation_items
  return: -
  """
  participant_score = get_participant_score(get_participant_by_id(par_l, id_number))[:]
  undo_operation = undos.create_undo_operation(replace_participant_score_by_id, [par_l, id_number, participant_score, []])
  undos.add_undo_operation_in_undo_stage(undo_stage, undo_operation)

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

def insert_score_by_participant_id(par_l, id_number, score_l, undo_stage):
  """
  function that adds the scores in the score_l into the score list coresponding to the id_number-th participant
  params: par_l - a list of participant items; id_number - integer; score_l - a list of floats; undo_stage - a list of undo_operation items
  return: -
  """
  participant = get_participant_by_id(par_l, id_number)
  participant_score = get_participant_score(participant)
  participant_score.extend(score_l)
  participant = create_participant(id_number, participant_score)
  change_participant_by_id(par_l, id_number, participant, undo_stage)
  
def delete_participant_score_by_id(par_l, id_number, undo_stage):
  """
  function that deletes the score list of the id_numer-th participant
  params: par_l - a list of participant items; id_number - an integer; undo_stage - a list of undo_operation items
  return: -, if the deletion is complete
  """
  participant = create_participant(id_number, [0])
  change_participant_by_id(par_l, id_number, participant, undo_stage)

def delete_participant_score_by_id_interval(par_l, id_interval, undo_stage):
  """
  function that deletes the score list of the participants that have an id in id_interval
  par_l: par_l - a list of participant; id_interval - a list of 2 integers; undo_stage - list of undo_operation items
  return -, if the deletion is complete
  """
  for i in range(id_interval[0], id_interval[1] + 1):
    delete_participant_score_by_id(par_l, i, undo_stage)

def replace_participant_score_by_id(par_l, id_number, score_l, undo_stage):
  """
  function that replaces the score in the par_l of the id_number-th participant with score_l score list
  params: par_l - a list of lists of floats; id_numer - an integer; score_l - a list of floats; undo_stage - a list of undo_operation items
  return: -
  """
  
  participant = create_participant(id_number, score_l)
  change_participant_by_id(par_l, id_number, participant, undo_stage)

def filter_participants_by_comparer(par_l, comparer, argument, undo_stage):
  """
  function that modifies par_l filtering participants with a score that satisfies the comparer
  params: par_l - a list of participant items; comparer - a comparer function; argument - a float number; undo_stage - a list of undo_operation items
  return: -  
  """
  for participant in par_l:
    participant_score_avg = get_participant_score_avg(participant)
    participant_id = get_participant_id(participant)
    if not comparer(participant_score_avg, argument):
      participant_modify = create_participant(participant_id, [oo])
      change_participant_by_id(par_l, participant_id, participant_modify, undo_stage)
