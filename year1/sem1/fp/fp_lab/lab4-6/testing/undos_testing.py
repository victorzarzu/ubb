from domain.undos import create_undo_operation, get_undo_operation_function, get_undo_operation_parameters, add_undo_operation_in_undo_stage, undo_wrapper, execute_undo_stage, add_undo_stage_in_undo, get_last_undo_stage, execute_last_undo_stage

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

def run_undos_tests():
  get_undo_operation_function_test()
  get_undo_operation_parameters_test()
  create_undo_operation_test()
  add_undo_operation_in_undo_stage_test()
  undo_wrapper_test()
  execute_undo_stage_test()
  add_undo_stage_in_undo_test()
  get_last_undo_stage_test()
execute_last_undo_stage_test()
