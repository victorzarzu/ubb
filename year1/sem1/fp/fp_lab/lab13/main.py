number = int(input("numar elemente: "))
array = [int(input()) for i in range(0, number)]
mod = int(input("divizibilitate cu: "))

def subsecvente(array, mod):
  subsecvente_recursiv(array, mod, 0, len(array), {})
  #subsecvente_iterativ(array, mod)

def subsecvente_recursiv(array, mod, left, right, h):
  if (left, right) in h:
    return

  if left == right:
    return

  if not sum(array[left:right]) % mod:
    print(array[left:right])
  
  h[(left, right)] = True

  subsecvente_recursiv(array, mod, left + 1, right, h)
  subsecvente_recursiv(array, mod, left, right - 1, h)

def subsecvente_iterativ(array, mod):
  for i in range(0, len(array)):
    for j in range(i + 1, len(array) + 1):
      if not sum(array[i:j]) % mod:
        print(array[i:j])

subsecvente(array, mod)
