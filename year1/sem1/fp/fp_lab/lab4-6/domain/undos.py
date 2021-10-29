import domain.participants as participants 

def create_undo_operation(function, parameters):
  """
  function that creates an undo item
  params: funcion - a function; parameters - a list of different types
  return: an undo item
  """
  return{
    'function': function,
    'parameters': parameters 
  }

def get_undo_function(undo):
  """
  function that returns the function of the undo item
  params: undo - an undo item
  returns: a function
  """
  return undo['function']

def get_undo_parameters(undo):
  """
  function that returns the parameters of the undo item
  params: undo - an undo item
  returns: a list of different types
  """
  return undo['parameters']

def inverse_of_the_function(function):
  """
  function that returns the inverse of the operation function
  params: operation - a function
  return: a function
  """
  if function == participants.add_participant_in_list:
    return participants.remove_participant_from_list
  elif function in [participants.insert_score_by_participant_id, participants.delete_participant_score_by_id, participants.replace_participant_score_by_id, participants.filter_participants_by_comparer]:
    return participants.replace_participant_score_by_id

def undo_wrapper(function, args):
  """
  function that executes the function with the args parameters 
  params: function - a function; args - a list of paramerts for the function 
  return: -
  """
  function(*args)

def create_undo_operation_test():
  undo = create_undo_operation(participants.add_participant_in_list, [1, 2])
  function = get_undo_function(undo)
  parameters = get_undo_parameters(undo)

  assert function == participants.add_participant_in_list
  assert parameters == [1, 2]

def get_undo_function_test():
  undo = create_undo_operation(participants.add_participant_in_list, [1, 2])
  function = get_undo_function(undo)
  assert function == participants.add_participant_in_list

  undo = create_undo_operation(participants.replace_participant_score_by_id, [5, 6])
  function = get_undo_function(undo)
  assert function == participants.replace_participant_score_by_id
 
def get_undo_parameters_test():
  undo = create_undo_operation(participants.add_participant_in_list, [1, 2])
  parameters = get_undo_parameters(undo)
  assert parameters == [1, 2] 

  undo = create_undo_operation(participants.replace_participant_score_by_id, [5, 6])
  parameters = get_undo_parameters(undo)
  assert parameters == [5, 6]
 
def inverse_of_the_function_test():
  inverse = inverse_of_the_function(participants.add_participant_in_list)
  assert inverse == participants.remove_participant_from_list

  inverse = inverse_of_the_function(participants.filter_participants_by_comparer)
  assert inverse == participants.replace_participant_score_by_id

  inverse = inverse_of_the_function(participants.delete_participant_score_by_id)
  assert inverse == participants.replace_participant_score_by_id

def undo_wrapper_test():
  par_l = []
  participant = participants.create_participant(0, [6, 7, 9])
  undo_wrapper(participants.add_participant_in_list, [par_l, participant])
  assert len(par_l) == 1

  participant = participants.get_participant_by_id(par_l, 0)
  participant_id = participants.get_participant_id(participant)
  assert participant_id == 0
  participant_score = participants.get_participant_score(participant)
  assert participant_score == [6, 7, 9]

get_undo_function_test()
get_undo_parameters_test()
create_undo_operation_test()
inverse_of_the_function_test()
undo_wrapper_test()
