from math import isqrt, log
from decimal import Decimal
from fractions import Fraction
from itertools import *
from functools import *
from collections import *
import operator

try: from tqdm import tqdm
except: tqdm = lambda x, *args, **kargs: x

def _gen_tokens():
  while 1:
    yield from input().split()
_tokens = _gen_tokens()
tok = _tokens.__next__
def ii(*args) -> int | list:
  '''
  ii() -> int
  ii(N) -> list[int]
  ii(R, C) -> list[list[int]]
  '''
  if len(args) == 0: return int(tok())
  return [ii(*args[1:]) for _ in range(args[0])]


class ITER:
  def __init__(self, it):
    self.it = iter(it)

  def __iter__(self):
    return self.it

  def __next__(self):
    return next(self.it)

  def map(self, f, *args):
    return ITER(map(f, self.it, *args))

  def starmap(self, f):
    return ITER(starmap(f, self.it))

  def filter(self, predicate):
    return ITER(filter(predicate, self.it))

  def starfilter(self, predicate):
    return ITER(filter(lambda x: predicate(*x), self.it))

  def all(self, predicate=None):
    if predicate is None:
      return all(self.it)
    return self.map(predicate).all()

  def starall(self, predicate):
    return self.starmap(predicate).all()

  def any(self, predicate=None):
    if predicate is None:
      return any(self.it)
    return self.map(predicate).any()

  def starany(self, predicate):
    return self.starmap(predicate).any()

  def accumulate(self, func=None, initial=None):
    return ITER(accumulate(self.it, func, initial))

  def batched(self, n, strict=False):
    return ITER(batched(self.it, n, strict=strict))

  def chain(self, *iterables):
    return ITER(chain(self.it, *iterables))

  def prechain(self, *iterables):
    return ITER(chain(*iterables, self.it))

  def interleave(self, *iterables):
    return ITER(chain.from_iterable(zip(self.it, *iterables)))

  def interleave_longest(self, *iterables, fillvalue=None):
    return ITER(chain.from_iterable(zip_longest(self.it, *iterables, fillvalue=fillvalue)))

  def flat(self):
    return ITER(chain.from_iterable(self.it))

  def windows(self, n):
    def _gen(it):
      window = deque(maxlen=n)
      for _ in range(n-1):
        try: window.append(next(it))
        except StopIteration: return

      for x in it:
        window.append(x)
        yield tuple(window)

    return ITER(_gen(self.it))

  def compress(self, selectors):
    return ITER(compress(self.it, selectors))

  def cycle(self):
    return ITER(cycle(self.it))

  def dropwhile(self, predicate):
    return ITER(dropwhile(predicate, self.it))

  def filterfalse(self, predicate):
    return ITER(filterfalse(predicate, self.it))

  def groupby(self, key=None):
    return ITER(groupby(self.it, key))

  def islice(self, *args):
    return ITER(islice(self.it, *args))

  def pairwise(self):
    return ITER(pairwise(self.it))

  def takewhile(self, predicate):
    return ITER(takewhile(predicate, self.it))

  def tee(self, n=2):
    return tuple(ITER(it) for it in tee(self.it, n))

  def copy(self):
    self.it, it2 = self.tee()
    return it2

  def zip(self, *iterables):
    return ITER(zip(self.it, *iterables))

  def zip_longest(self, *iterables, fillvalue=None):
    return ITER(zip_longest(self.it, *iterables, fillvalue=fillvalue))

  def drop(self, n=1):
    return self.islice(n, None)

  def take(self, n=1):
    return self.islice(n)
  
  def __getitem__(self, key):
    if isinstance(key, slice):
      return self.islice(key.start, key.stop, key.step)
    else:
      return next(self.islice(key, key+1))

  def __setitem__(self, key, value):
    def _gen_updater(old_it, key, replacement):
      if isinstance(key, slice):
        start, stop, step = key.start or 0, key.stop, key.step or 1
        if step != 1:
          raise ValueError("Extended slices with step != 1 are not supported for assignment")
          
        for _ in range(start):
          yield next(old_it)
        
        yield from replacement
        
        if stop is not None:
          for _ in range(max(0, stop - start)):
            try: next(old_it)
            except StopIteration: break
        
        yield from old_it
      else:
        for _ in range(key):
          yield next(old_it)
          
        yield replacement
          
        try: next(old_it)
        except StopIteration: pass
              
        yield from old_it

    self.it = _gen_updater(self.it, key, value)

  def __delitem__(self, key):
    def _gen_deleter(old_it, key):
      if isinstance(key, slice):
        start, stop, step = key.start or 0, key.stop, key.step or 1
        if step != 1:
          raise ValueError("Extended slices with step != 1 are not supported for deletion")
          
        for _ in range(start):
          yield next(old_it)
        
        if stop is not None:
          for _ in range(max(0, stop - start)):
            try: next(old_it)
            except StopIteration: break
        
        yield from old_it
      else:
        for _ in range(key):
          yield next(old_it)
          
        try: next(old_it)
        except StopIteration: pass
              
        yield from old_it

    self.it = _gen_deleter(self.it, key)

  def len(self):
    return sum(1 for _ in self.it)

  def reduce(self, f, init=None):
    return reduce(f, self.it, init)

  def sum(self):
    return sum(self.it)

  def mul(self):
    return self.reduce(operator.mul)

  def collect(self, cls=list):
    return cls(self.it)

  def join(self, sep=''):
    return sep.join(map(str, self.it))

  def sort(key=None):
    return ITER(sorted(self.it, key=key))

  def sorted(key=None):
    return sorted(self.it, key=key)

  def product(self, *iterables, repeat=None):
    return ITER(product(self.it, *iterables, repeat=repeat))

  def permutations(self, r=None):
    return ITER(permutations(self.it, r))

  def combinations(self, r):
    return ITER(combinations(self.it, r))

  def combinations_with_replacement(self, r):
    return ITER(combinations_with_replacement(self.it, r))

  @staticmethod
  def range(*args):
    return ITER(range(*args))

  @staticmethod
  def tqdm(*args, **kargs):
    return ITER(tqdm(range(*args), **kargs))

  @staticmethod
  def count(*args):
    return ITER(count(*args))

def toBase(n: int, b: int) -> str:
  if n == 0: return '0'

  res = []
  while n:
    n, m = divmod(n, b)
    res.append(m)

  return ''.join(map(str, res[::-1]))

def ispal(s: int | str) -> bool:
  s = str(s)
  return s == s[::-1]

def issquare(n: int | str) -> bool:
  n = int(n)
  return isqrt(n)**2 == n

'''
def isprime(n: int | str) -> bool:
  n = int(n)
  if n <= 1: return False

  for i in range(2, isqrt(n)+1):
    if n%i==0: return False
  return True

def factorize(n: int) -> Counter:
  res = Counter()

  for i in range(2, isqrt(n)+1):
    while n%i==0:
      res[i] += 1
      n //= i
  if n != 1: res[n] += 1

  return res

def countFactor(n: int) -> int:
  fac = factorize(n)

  res = 1
  for v in fac.values():
    res *= v+1

  return res
  
def primeFactors(self, n):
  return self.factorize(n).keys()

def factors(n: int):
  fac = factorize(n)
  keys, values = list(fac.keys()), fac.values()
  L = len(keys)

  for it in product(*[range(v+1) for v in values]):
    yield reduce(operator.mul, starmap(operator.pow, zip(keys, it)), 1)

def sumProperFactor(n: int) -> int:
  return sum(factors(n)) - n
'''

class Sieve:
  def __init__(self, N):
    self.p = [i for i in range(N+1)] # 최소 소인수
    self.primes = []
    
    self.tau = [0]*(N+1) # τ, 약수의 개수
    self.sigma = [0]*(N+1) # σ, 약수의 합
    self.mu = [0]*(N+1) # μ, 뫼비우스 함수
    self.phi = [0]*(N+1) # φ, n 미만의 n와 서로소인 정수 개수
    self.c = [0]*(N+1) # n의 최소 소인수의 지수
    self.tau[1] = self.sigma[1] = self.mu[1] = self.phi[1] = 1
    
    for i in tqdm(range(2, N+1), desc="Init Sieve"):
      if self.p[i] == i:
        self.primes.append(i)
        
        self.c[i] = 1
        self.tau[i] = 2
        self.sigma[i] = i+1
        self.mu[i] = -1
        self.phi[i] = i-1

      for p in self.primes:
        x = i*p
        
        if x > N: break
        self.p[x] = p
        if i % p == 0:
          self.c[x] = self.c[i] + 1
          self.tau[x] = self.tau[i] * (self.c[i]+2) // (self.c[i]+1)
          self.sigma[x] = self.sigma[i] * (pow(p, self.c[i]+2) - 1) // (pow(p, self.c[i]+1) - 1)
          self.mu[x] = 0
          self.phi[x] = self.phi[i] * p
          break
        else:
          self.c[x] = 1
          self.tau[x] = self.tau[i] * self.tau[p]
          self.sigma[x] = self.sigma[i] * self.sigma[p]
          self.mu[x] = self.mu[i] * self.mu[p]
          self.phi[x] = self.phi[i] * self.phi[p]

  def isprime(self, n):
    if n <= 1: return False
    return self.p[n] == n

  def factorize(self, n):
    res = Counter()
    while n > 1:
      res[self.p[n]] += 1
      n //= self.p[n]
    return res
    
  def primeFactors(self, n):
    return self.factorize(n).keys()
    
  def factors(self, n):
    fac = self.factorize(n)
    keys, values, items = list(fac.keys()), fac.values(), fac.items()
    L = len(keys)

    for it in product(*[range(v+1) for v in values]):
      yield ITER(keys).zip(it).starmap(operator.pow).mul()

class Tracker:
  def __init__(self, *, f=lambda x: x, filter=lambda x: True, debug=False):
    self.f = f
    self.filter = filter
    self.debug = debug
    self.can_calculate = True

    self.mx = None
    self.mx_x = None

    self.mn = None
    self.mn_x = None

    self.sum = None
    self.mul = None
    
    self.cnt = 0

  def update(self, x):
    if not self.filter(x): return

    y = self.f(x)

    if self.debug: print('!', x, '->', y)
    
    self.cnt += 1
    if self.cnt == 1:
      self.mx_x, self.mx = x, y
      self.mn_x, self.mn = x, y
      self.can_calculate = isinstance(y, (int, float, Decimal, Fraction))
      if self.can_calculate:
        self.sum = y
        self.mul = y

    if y > self.mx:
      self.mx_x, self.mx = x, y
    if y < self.mn:
      self.mn_x, self.mn = x, y

    if self.can_calculate:
      self.sum += y
      self.mul *= y
      if self.mul > 2**100: self.mul = float('inf')
      if self.mul < -2**100: self.mul = -float('inf')

  def updates(self, it):
    for x in it: self.update(x)

  def __str__(self):
    return '\n'.join([
      f"min: {self.mn_x} -> {self.mn}",
      f"max: {self.mx_x} -> {self.mx}",
      f"cnt: {self.cnt}",
      f"sum: {self.sum}",
      f"mul: {self.mul}",
    ])

###

