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

def get_undo_operation_function(undo):
  """
  function that returns the function of the undo item
  params: undo - an undo item
  returns: a function
  """
  return undo['function']

def get_undo_operation_parameters(undo):
  """
  function that returns the parameters of the undo item
  params: undo - an undo item
  returns: a list of different types
  """
  return undo['parameters']
  
def undo_wrapper(function, args):
  """
  function that executes the function with the args parameters 
  params: function - a function; args - a list of paramerts for the function 
  return: -
  """
  function(*args)

def add_undo_operation_in_undo_stage(undo_stage, undo_operation):
  """
  function that adds an undo operation in an undo stage
  params: undo_stage - a list of undo_operation items; undo_operation - an undo_operation item
  return: -
  """
  undo_stage.append(undo_operation)

def execute_undo_stage(undo_stage):
  """
  function that executes all undo_operation's from undo stage
  params: undo_stage - a list of undo_operation items
  return: -
  """
  for undo_operation in undo_stage:
    function = get_undo_operation_function(undo_operation)
    parameters = get_undo_operation_parameters(undo_operation)
    undo_wrapper(function, parameters)

def add_undo_stage_in_undo(undo, undo_stage):
  """
  function that adds an undo_stage in undo
  params: undo - a list of undo_stage items; undo_stage - a list of undo_operation items
  return: -
  """
  if not undo_stage == []:
    undo.append(undo_stage)

def get_last_undo_stage(undo):
  """
  function that returns and pops the last undo_stage from undo
  params: undo - a list of undo stages
  return: an undo_stage
  """
  if len(undo) == 0:
    print("no previous actions!")
    return []

  return undo.pop()

def execute_last_undo_stage(undo):
  """
  function that executes the last undo stage
  params: undo - a list of undo stages
  return: -
  """
  last_undo_stage = get_last_undo_stage(undo)
  if not last_undo_stage == []:
    execute_undo_stage(last_undo_stage)

