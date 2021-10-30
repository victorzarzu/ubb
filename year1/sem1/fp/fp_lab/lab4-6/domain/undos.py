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

def create_undo_operation_test():
  undo_operation = create_undo_operation(get_undo_operation_function, [1, 2])
  function = get_undo_operation_function(undo_operation)
  parameters = get_undo_operation_parameters(undo_operation)

  assert function == get_undo_operation_function 
  assert parameters == [1, 2]

def get_undo_operation_function_test():
  undo_operation = create_undo_operation(create_undo_operation, [1, 2])
  function = get_undo_operation_function(undo_operation)
  assert function == create_undo_operation

  undo_operation = create_undo_operation(get_undo_operation_function, [5, 6])
  function = get_undo_operation_function(undo_operation)
  assert function == get_undo_operation_function
 
def get_undo_operation_parameters_test():
  undo_operation = create_undo_operation(get_undo_operation_function, [1, 2])
  parameters = get_undo_operation_parameters(undo_operation)
  assert parameters == [1, 2] 

  undo_operation = create_undo_operation(create_undo_operation, [5, 6])
  parameters = get_undo_operation_parameters(undo_operation)
  assert parameters == [5, 6]
 
def add_undo_operation_in_undo_stage_test():
  undo = []
  undo_operation = create_undo_operation(create_undo_operation, [1, 2])
  add_undo_operation_in_undo_stage(undo, undo_operation)
  assert len(undo) == 1

  undo_parameters = get_undo_operation_parameters(undo[0])
  assert undo_parameters == [1, 2]

def undo_wrapper_test():
  undo = []
  undo_operation = create_undo_operation(create_undo_operation, [6, 7, 9])
  undo_wrapper(add_undo_operation_in_undo_stage, [undo, undo_operation])
  assert len(undo) == 1

  undo_opeartion = undo[0]
  undo_operation_function = get_undo_operation_function(undo_operation)
  assert undo_operation_function == create_undo_operation
  undo_operation_parameters = get_undo_operation_parameters(undo_operation) 
  assert undo_operation_parameters == [6, 7, 9]

def execute_undo_stage_test():
  undo_stage = []
  undo = []
  undo_operation = create_undo_operation(add_undo_operation_in_undo_stage, [undo, create_undo_operation(get_undo_operation_function, [1, 3])])
  add_undo_operation_in_undo_stage(undo_stage, undo_operation)
  undo_operation = create_undo_operation(add_undo_operation_in_undo_stage, [undo, create_undo_operation(get_undo_operation_function, [1, 3])])
  add_undo_operation_in_undo_stage(undo_stage, undo_operation)
  execute_undo_stage(undo_stage)

  assert len(undo) == 2

def add_undo_stage_in_undo_test():
  undo_stage = []
  undo = []
  undo_operation = create_undo_operation(add_undo_operation_in_undo_stage, [undo, create_undo_operation(get_undo_operation_function, [1, 3])])
  add_undo_operation_in_undo_stage(undo_stage, undo_operation)
  undo_operation = create_undo_operation(add_undo_operation_in_undo_stage, [undo, create_undo_operation(get_undo_operation_function, [2, 3])])
  add_undo_operation_in_undo_stage(undo_stage, undo_operation)
  add_undo_stage_in_undo(undo, undo_stage)

  assert len(undo) == 1

  undo_stage = []
  undo_operation = create_undo_operation(add_undo_operation_in_undo_stage, [undo, create_undo_operation(get_undo_operation_function, [1, 3])])
  add_undo_operation_in_undo_stage(undo_stage, undo_operation)
  add_undo_stage_in_undo(undo, undo_stage)

  assert len(undo) == 2
  undo_stage = undo[1]
  undo_operation = undo_stage[0]
  undo_operation_parameters = get_undo_operation_parameters(undo_operation)
  assert undo_operation_parameters == [undo, create_undo_operation(get_undo_operation_function, [1, 3])]


def get_last_undo_stage_test():
  undo_stage = []
  undo = []
  undo_operation = create_undo_operation(add_undo_operation_in_undo_stage, [undo, create_undo_operation(get_undo_operation_function, [1, 3])])
  add_undo_operation_in_undo_stage(undo_stage, undo_operation)
  undo_operation = create_undo_operation(add_undo_operation_in_undo_stage, [undo, create_undo_operation(get_undo_operation_function, [2, 3])])
  add_undo_operation_in_undo_stage(undo_stage, undo_operation)
  add_undo_stage_in_undo(undo, undo_stage)

  undo_operation = get_last_undo_stage(undo)[1]
  assert len(undo) == 0
  undo_operation_parameters = get_undo_operation_parameters(undo_operation)
  assert undo_operation_parameters == [undo, create_undo_operation(get_undo_operation_function, [2, 3])]


def execute_last_undo_stage_test():
  undo_stage = []
  undo = []
  undo1 = []
  undo_operation = create_undo_operation(add_undo_operation_in_undo_stage, [undo, create_undo_operation(get_undo_operation_function, [1, 3])])
  add_undo_operation_in_undo_stage(undo_stage, undo_operation)
  undo_operation = create_undo_operation(add_undo_operation_in_undo_stage, [undo, create_undo_operation(get_undo_operation_function, [2, 3])])
  add_undo_operation_in_undo_stage(undo_stage, undo_operation)
  add_undo_stage_in_undo(undo1, undo_stage)

  execute_last_undo_stage(undo1)
  assert len(undo1) == 0
  assert len(undo) == 2
  
  undo_operation = undo[0]
  undo_operation_parameters = get_undo_operation_parameters(undo_operation)
  assert undo_operation_parameters == [1, 3]

get_undo_operation_function_test()
get_undo_operation_parameters_test()
create_undo_operation_test()
add_undo_operation_in_undo_stage_test()
undo_wrapper_test()
execute_undo_stage_test()
add_undo_stage_in_undo_test()
get_last_undo_stage_test()
execute_last_undo_stage_test()
