def read_list():
  """
  It reads a list of numbers separated by blanks and returns it
  params: -
  return: a list of numbers
  """

  int_list = [int(x) for x in input().split()]
  return int_list


def operation1(int_list):
  """
  Computes and prints the longest ascending subsequences of the argument
  params: a list of integers
  return: - 
  """

  lists = []
  max_len = 0
  for i in range(0, len(int_list)):
    curr = [int_list[i]]
    j = i + 1
    while j < len(int_list) and int_list[j] > int_list[j - 1]:
      curr.append(int_list[j])
      j += 1

    max_len = max(max_len, j - i)
    
    if len(curr) >= max_len:
      lists.append(curr)

  for l in lists:
    if len(l) == max_len:
      print(l, end = ' ')

def operation2(int_list):
  """
  Computes and prints the longest subsequences of the argument that has equal elements
  params: a list of integers
  return: -
  """

  lists = []
  max_len = 0
  for i in range(0, len(int_list)):
    curr = [int_list[i]]
    j = i + 1
    while j < len(int_list) and int_list[j] == int_list[j - 1]:
      curr.append(int_list[j])
      j += 1

    max_len = max(max_len, j - i)
    
    if len(curr) >= max_len:
      lists.append(curr)

  for l in lists:
    if len(l) == max_len:
      print(l, end = ' ')

def functionality():
  """
  It manages the operations
  params: -
  return: -
  """

  while True:
    op = int(input()) 
    if op == 0: break
    int_list = read_list()
    if op == 1:
      operation1(int_list)
    elif op == 2:
      operation2(int_list)
    print()

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
