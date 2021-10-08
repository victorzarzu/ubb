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


def get_max_len_operation1(int_list):
  """
  It computes and returns the length of the longest ascending subsequence
  params: int_list - a list of integers
  return: integer
  """

  max_len = 0
  for i in range(len(int_list)):
    j = i + 1
    while j < len(int_list) and int_list[j] > int_list[j - 1]:
      j += 1
    
    max_len = max(max_len, j - i)

  return max_len


def add_list_to_list_of_list(lists, int_list):
  """
  It appends a list to a list of lists
  params: lists - a list of lists of integers; int_list - a list of integers
  return: -
  """
  lists.append(int_list)


def get_longest_lists1(max_len, int_list):
  """
  It returns a list of the longest ascending lists in int_list
  params: max_len - integer; int_list - list of integers
  return: a list of lists of integers
  """

  lists = []
  for i in range(0, len(int_list)):
    j = i + 1
    while j < len(int_list) and int_list[j] > int_list[j - 1]: j += 1
    if j - i == max_len:
      add_list_to_list_of_list(lists, int_list[i:j])           

  return lists


def print_list_of_lists(lists):
  """
  It prints all lists in the argument
  params: lists - a list of lists of integers
  return: -
  """

  for l in lists:
    print(l, end = ' ')

def operation1(int_list):
  """
  Computes and prints the longest ascending subsequences of the argument
  params: a list of integers
  return: - 
  """

  max_len = get_max_len_operation1(int_list) 
  lists = get_longest_lists1(max_len, int_list)
  print_list_of_lists(lists)


def get_max_len_operation2(int_list):
  """
  It computes and returns the length of the longest constant subsequence
  params: int_list - a list of integers
  return: integer
  """

  max_len = 0
  for i in range(len(int_list)):
    j = i + 1
    while j < len(int_list) and int_list[j] == int_list[j - 1]:
      j += 1
    
    max_len = max(max_len, j - i)

  return max_len

def get_longest_lists2(max_len, int_list):
  """
  It returns a list of the longest constant lists in int_list
  params: max_len - integer; int_list - list of integers
  return: a list of lists of integers
  """

  lists = []
  for i in range(0, len(int_list)):
    j = i + 1
    while j < len(int_list) and int_list[j] == int_list[j - 1]: j += 1
    if j - i == max_len:
      add_list_to_list_of_list(lists, int_list[i:j])           

  return lists

def operation2(int_list):
  """
  Computes and prints the longest subsequences of the argument that has equal elements
  params: a list of integers
  return: -
  """

  max_len = get_max_len_operation2(int_list)
  lists = get_longest_lists2(max_len, int_list)
  print_list_of_lists(lists)


def read_and_operation(op):
    """
    It reads the list and gives control to the operation function
    params: op - interger
    return: -
    """


    if op == 0: exit() 
    if op != 1 and op != 2:
      print("Invalid command!")
      return

    try:
      int_list = read_list()
    except:
      return

    if op == 1:
      operation1(int_list)
    elif op == 2:
      operation2(int_list)
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

  functionality()

ui()
