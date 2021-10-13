def read_list():
  """
  It reads a list of numbers separated by blanks and returns it
  params: -
  return: a list of numbers
  """

  try:
    int_list = [int(x) for x in input().split()]
  except ValueError:
    print("The numbers are not integers")

  return int_list


def add_list_to_list_of_list(lists, int_list):
  """
  It appends a list to a list of lists
  params: lists - a list of lists of integers; int_list - a list of integers
  return: -
  """
  lists.append(int_list)


def operation1_comparer(x, y, diff):
  """
  Returns if x is smaller than y
  params: x, y - integers
  return: True if x < y, False otherwise
  """
  return x > y

def operation2_comparer(x, y, diff):
  """
  Returns if x and y are equal 
  params: x, y - integers
  return: True if x = y, False otherwise
  """
  return x == y

def operation3_comparer(x, y, diff):
  if x in diff: return True
  elif not x in diff and len(diff) < 3: 
    diff.append(x)
    return True
  return False

def print_list_of_lists(lists):
  """
  It prints all lists in the argument
  params: lists - a list of lists of integers
  return: -
  """

  for l in lists:
    print(l, end = ' ')

def get_max_len_test():
  assert get_max_len([1, 2, 3, 6, 0, 6], operation1_comparer) == 4
  assert get_max_len([0, 0, -1, 2, 1, 0, 5], operation1_comparer) == 2
  assert get_max_len([-2, 0, 3, 2, 1, 0, 5], operation1_comparer) == 3
  assert get_max_len([1, 1, 1, 1], operation1_comparer) == 1
  assert get_max_len([6, 6, 5, 1, 1, 6, 7, 7], operation2_comparer) == 2
  assert get_max_len([1, 1, 1, 2, 2, 5, 5], operation2_comparer) == 3
  assert get_max_len([0, 1, 0, 1, 0, 1], operation2_comparer) == 1

def get_longest_lists_test():
  assert get_longest_lists(get_max_len([1, 2, 3, 6, 0, 6], operation1_comparer), [1, 2, 3, 6, 0, 6], operation1_comparer) == [[1, 2, 3, 6]]
  assert get_longest_lists(get_max_len([0, 0, -1, 2, 1, 0, 5], operation1_comparer), [0, 0, -1, 2, 1, 0, 5], operation1_comparer) == [[-1, 2], [0, 5]]
  assert get_longest_lists(get_max_len([-2, 0, 3, 2, 1, 0, 5], operation1_comparer), [-2, 0, 3, 2, 1, 0, 5], operation1_comparer) == [[-2, 0, 3]]
  assert get_longest_lists(get_max_len([1, 1, 1, 1], operation1_comparer), [1, 1, 1, 1], operation1_comparer) == [[1], [1], [1], [1]]
  assert get_longest_lists(get_max_len([6, 6, 5, 1, 1, 6, 7, 7], operation2_comparer), [6, 6, 5, 1, 1, 6, 7, 7], operation2_comparer) == [[6, 6], [1, 1], [7, 7]]
  assert get_longest_lists(get_max_len([1, 1, 1, 2, 2, 5, 5], operation2_comparer), [1, 1, 1, 2, 2, 5, 5], operation2_comparer) == [[1, 1, 1]]
  assert get_longest_lists(get_max_len([0, 1, 0, 1, 0, 1], operation2_comparer), [0, 1, 0, 1, 0, 1], operation2_comparer) == [[0], [1], [0], [1], [0], [1]]

def get_max_len(int_list, comparer):
  """
  It computes and returns the length of the longest subsequence that satisfies the comparer
  params: int_list - a list of integers; comparer - a function
  return: integer
  """

  max_len = 0
  for i in range(len(int_list)):
    j = i + 1
    diff = [int_list[i]]
    while j < len(int_list) and comparer(int_list[j], int_list[j - 1], diff):
      j += 1
    
    max_len = max(max_len, j - i)

  return max_len

def get_longest_lists(max_len, int_list, comparer):
  """
  It returns a list of the longest ascending lists in int_list
  params: max_len - integer; int_list - list of integers; comparer - a function
  return: a list of lists of integers
  """

  lists = []
  for i in range(0, len(int_list)):
    j = i + 1
    diff = [int_list[i]]
    while j < len(int_list) and comparer(int_list[j], int_list[j - 1], diff): j += 1
    if j - i == max_len:
      add_list_to_list_of_list(lists, int_list[i:j])           

  return lists

def operation(int_list, comparer):
  """
  Computes and prints the longest subsequences that satisfies the comparer 
  params: int_list - a list of integers, comparer - a function
  return: - 
  """
  max_len = get_max_len(int_list, comparer)
  lists = get_longest_lists(max_len, int_list, comparer)
  print_list_of_lists(lists)

def read_and_operation(op):
    """
    It reads the list and gives control to the operation function
    params: op - interger
    return: -
    """

    if op == 0: exit() 
    if op > 3:
      print("Invalid command!")
      return

    try:
      int_list = read_list()
    except:
      return

    if op == 1:
      operation(int_list, operation1_comparer)
    elif op == 2:
      operation(int_list, operation2_comparer)
    elif op == 3:
      operation(int_list, operation3_comparer)
    else:
      print("Invalid command")
    print()
    


def functionality():
  """
  It manages the operations
  params: -
  return: -
  """

  while True:
    op = int(input()) 
    read_and_operation(op) 

def ui():

  """
  It displays the UI
  params: -
  return: -
  """

  print("Input: a list of interger numbers separated by blanks")
  print("Operation 0 => exit") 
  print("Operation 1 => the longest ascending subsequence in the input list") 
  print("Operation 2 => the longest subsequence that has equal elements") 
  print("Operation 3 => the longest subsequence that has a maximum of three different items") 

  functionality()

get_max_len_test()
get_longest_lists_test()

ui()
