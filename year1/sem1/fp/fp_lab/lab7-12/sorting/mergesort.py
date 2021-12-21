def mergesort(iterable, key = lambda x: x, cmp = lambda x, y: x < y, reverse = False):

  if reverse:
    reverse = lambda x: not x
  else:
    reverse = lambda x: x
  
  mergesortUtil(iterable, key, cmp, reverse, 0, len(iterable) - 1) 
  return iterable

def mergesortUtil(iterable, key, cmp, reverse, left, right):
  if left < right:
    mid = (left + right) >> 1
    mergesortUtil(iterable, key, cmp, reverse, left, mid)
    mergesortUtil(iterable, key, cmp, reverse, mid + 1, right)
    merge(iterable, left, mid, right, key, cmp, reverse)

def merge(iterable, left, mid, right, key, cmp, reverse):
  len_left = mid - left + 1
  len_right = right - mid 

  left_list = iterable[left:(mid + 1)] 
  right_list = iterable[(mid + 1):(right + 1)] 
  
  index_left = 0
  index_right = 0
  index_all = left

  while index_left < len_left and index_right < len_right:
    if reverse(cmp(key(left_list[index_left]), key(right_list[index_right]))):
      iterable[index_all] = left_list[index_left]
      index_left += 1
    else:
      iterable[index_all] = right_list[index_right]
      index_right += 1
    index_all += 1

  while index_left < len_left:
    iterable[index_all] = left_list[index_left]
    index_all += 1
    index_left += 1
  
  while index_right < len_right:
    iterable[index_all] = right_list[index_right]
    index_all += 1
    index_right += 1
