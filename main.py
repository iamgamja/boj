import sys

# sys.setrecursionlimit(10**6)
from collections import deque
from collections import defaultdict
# from decimal import Decimal
# from fractions import Fraction


def input_(*f, t=0):
  '''
  t=0: 1
  t=1: [1, 2, 3]
  '''
  if t == 0:
    return f[0](sys.stdin.readline().rstrip())
  else:  # t == 1
    x = sys.stdin.readline().rstrip().split()
    if len(f) == 1:
      return list(map(f[0], x))
    else:
      assert(len(f) == len(x))
      for i in range(len(f)):
        x[i] = f[i](x[i])
      return x


islocal = len(sys.argv) >= 2 and '-l' in sys.argv

if islocal:
  def print_(*a, sep=' ', end='\n'):
    print('\033[92m', end='')
    print(*a, sep=sep, end='')
    print('\033[0m', end=end)

  def debug(*a):
    print('\033[90m[DEBUG]', *a, '[/DEBUG]\033[0m', sep='\n')

  def debug2dlist(a):
    debug('\n'.join(map(lambda x: ' '.join(map(str, x)), a)))
else:
  print_ = print
  def debug(*a): pass
  def debug2dlist(a): pass

if islocal:
  print_('[Running in Local]')


# Code

a, b = input_(int, t=1)
print_(a+b)
