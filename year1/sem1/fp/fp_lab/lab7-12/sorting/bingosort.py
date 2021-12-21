def bingosort(iterable, key = lambda x : x, cmp = lambda x, y: x < y, reverse = False):

  if reverse:
    reverse = lambda x : x
  else:
    reverse = lambda x : not x
  
  last = len(iterable) - 1
  nextMax = iterable[last]
  
  for i in range(last - 1, -1, -1):
    if reverse(cmp(key(iterable[i]), key(nextMax))):
      nextMax = iterable[i]

  while last > 0 and iterable[last] == nextMax:
    last -= 1
  
  while last:
    prevMax = nextMax
    nextMax = iterable[last]

    for i in range(last - 1, -1, -1):
      if reverse(cmp(key(iterable[i]), key(nextMax))):
        if iterable[i] != prevMax:
          nextMax = iterable[i]
        else:
          iterable[i], iterable[last] = iterable[last], iterable[i]
          last -= 1

    while last > 0 and iterable[last] == nextMax:
      last -= 1
 
  return iterable
