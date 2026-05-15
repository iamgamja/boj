from math import isqrt, log, factorial, comb, gcd, lcm
from decimal import Decimal
from fractions import Fraction
from itertools import *
from functools import *
from collections import *
import math, random, operator
from tqdm import tqdm, trange

def _gen_tokens():
  while 1:
    yield from input().split()
_tokens = _gen_tokens()
tok = _tokens.__next__
def ii(*args):
  '''
  ii() -> int
  ii(N) -> list[int]
  ii(R, C) -> list[list[int]]
  '''
  if len(args) == 0: return int(tok())
  return [ii(*args[1:]) for _ in range(args[0])]

def zi(N, *args):
  if len(args) == 0: return [0]*N
  return [zi(*args) for _ in range(N)]


class ITER:
  def __init__(self, it):
    self.it = iter(it)

  def __iter__(self):
    return self.it

  def __next__(self):
    return next(self.it)


  @staticmethod
  def range(*args):
    return ITER(range(*args))

  @staticmethod
  def tqdm(*args, **kargs):
    return ITER(tqdm(range(*args), **kargs))

  @staticmethod
  def count(*args):
    return ITER(count(*args))


  def map(self, f, *args):
    return ITER(map(f, self.it, *args))

  def starmap(self, f):
    return ITER(starmap(f, self.it))

  def filter(self, predicate=None):
    return ITER(filter(predicate, self.it))

  def starfilter(self, predicate):
    return ITER(filter(lambda x: predicate(*x), self.it))

  def filterfalse(self, predicate=None):
    return ITER(filterfalse(predicate, self.it))

  def compress(self, selectors):
    return ITER(compress(self.it, selectors))


  def islice(self, *args):
    return ITER(islice(self.it, *args))

  def __getitem__(self, key):
    if isinstance(key, slice): return self.islice(key.start, key.stop, key.step)
    else: return next(self.islice(key, key+1))
    
  def drop(self, n=1):
    return self[n:]
    
  def dropwhile(self, predicate=lambda x: x):
    return ITER(dropwhile(predicate, self.it))

  def dropwhilefalse(self, predicate=lambda x: x):
    return ITER(dropwhile(lambda x: not predicate(x), self.it))

  def take(self, n=1):
    return self[:n]
    
  def takewhile(self, predicate=lambda x: x):
    return ITER(takewhile(predicate, self.it))

  def takewhilefalse(self, predicate=lambda x: x):
    return ITER(takewhile(lambda x: not predicate(x), self.it))


  def chain(self, *iterables):
    return ITER(chain(self.it, *iterables))

  def prechain(self, *iterables):
    return ITER(chain(*iterables, self.it))

  def append(self, x):
    return self.chain([x])

  def prepend(self, x):
    return self.prechain([x])

  def zip(self, *iterables):
    return ITER(zip(self.it, *iterables))

  def zip_longest(self, *iterables, fillvalue=None):
    return ITER(zip_longest(self.it, *iterables, fillvalue=fillvalue))
    
  def interleave(self, *iterables):
    return self.zip(*iterables).flat()

  def interleave_longest(self, *iterables, fillvalue=None):
    return self.zip_longest(*iterables, fillvalue=fillvalue).flat()


  def flat(self):
    return ITER(chain.from_iterable(self.it))

  def accumulate(self, func=None, initial=None):
    return ITER(accumulate(self.it, func, initial=initial))

  def presum(self):
    return self.accumulate()

  def batched(self, n, strict=False):
    return ITER(batched(self.it, n, strict=strict))
    
  def groupby(self, key=None):
    return ITER(groupby(self.it, key))

  def pairwise(self):
    return ITER(pairwise(self.it))

  def pairwise_loop(self):
    first = next(self.it)
    return (self
      .prepend(first)
      .append(first)
      .pairwise()
    )

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
    
  def cycle(self):
    return ITER(cycle(self.it))

  def tee(self, n=2):
    return tuple(ITER(it) for it in tee(self.it, n))

  def copy(self):
    self.it, it2 = tee(self.it)
    return ITER(it2)


  def sort(self, key=None, reverse=False):
    return ITER(sorted(self.it, key=key, reverse=reverse))

  def sorted(self, key=None, reverse=False):
    return sorted(self.it, key=key, reverse=reverse)

  def reverse(self):
    return ITER(self.collect()[::-1])
    
  def reversed(self):
    return self.collect()[::-1]

  def product(self, *iterables, repeat=1):
    return ITER(product(self.it, *iterables, repeat=repeat))

  def starproduct(self, repeat=1):
    return ITER(product(*self.it, repeat=repeat))

  def permutations(self, r=None):
    return ITER(permutations(self.it, r))

  def combinations(self, r):
    return ITER(combinations(self.it, r))

  def combinations_with_replacement(self, r):
    return ITER(combinations_with_replacement(self.it, r))


  def all(self, predicate=lambda x: x):
    return all(self.map(predicate))

  def starall(self, predicate):
    return all(self.starmap(predicate))

  def any(self, predicate=lambda x: x):
    return any(self.map(predicate))

  def starany(self, predicate):
    return any(self.starmap(predicate))

  def len(self):
    return sum(1 for _ in self.it)

  def reduce(self, f, initial=None):
    if initial is None: return reduce(f, self.it)
    return reduce(f, self.it, initial=initial)

  def min(self, key=None):
    return min(self.it, key=key)

  def max(self, key=None):
    return max(self.it, key=key)

  def sum(self):
    return sum(self.it)

  def mul(self):
    return self.reduce(operator.mul, 1)

  def collect(self, cls=list):
    return cls(self.it)

  def join(self, sep=''):
    return sep.join(map(str, self.it))


@total_ordering
class Point:
  INF = 1<<128
  def __init__(self, x=0, y=0):
    self.x = x
    self.y = y

  def __repr__(self):
    return f"(x={self.x}, y={self.y})"

  
  def normalize(self):
    g = gcd(self.x, self.y)
    return self // g if g else Point()
  

  def __add__(self, other):
    return Point(self.x + other.x, self.y + other.y)

  def __sub__(self, other):
    return Point(self.x - other.x, self.y - other.y)

  def __neg__(self):
    return Point(-self.x, -self.y)

  def __mul__(self, other):
    return Point(self.x * other, self.y * other)

  def __truediv__(self, other):
    return Point(self.x / other, self.y / other)

  def __floordiv__(self, other):
    return Point(self.x // other, self.y // other)


  def __iadd__(self, other):
    self.x += other.x
    self.y += other.y
    return self

  def __isub__(self, other):
    self.x -= other.x
    self.y -= other.y
    return self

  def __imul__(self, other):
    self.x *= other
    self.y *= other
    return self
    
  def __itruediv__(self, other):
    self.x /= other
    self.y /= other
    return self

  def __ifloordiv__(self, other):
    self.x //= other
    self.y //= other
    return self


  def dot(self, other):
    return self.x * other.x + self.y * other.y
    
  def cross(self, other):
    return self.x * other.y - self.y * other.x


  def __eq__(self, other):
    if not isinstance(other, Point): return False
    return self.x == other.x and self.y == other.y

  def __lt__(self, other):
    if self.x != other.x:
      return self.x < other.x
    return self.y < other.y

class Line:
  def __init__(self, p: Point, d: Point): self.p = p; self.d = d.normalize()
  def __repl__(self): return f"Line(p={self.p}, d={self.d})"
class Ray:
  def __init__(self, p: Point, d: Point): self.p = p; self.d = d.normalize()
  def __repl__(self): return f"Ray(p={self.p}, d={self.d})"
class Segment:
  def __init__(self, p: Point, q: Point): self.p = p; self.q = q; self.d = q - p
  def __repl__(self): return f"Segment(p={self.p}, q={self.q})"

def sign(n):
  return (n > 0) - (n < 0)

def ccw(a: Point, b: Point, c: Point):
  return (b - a).cross(c - a)

def sccw(a: Point, b: Point, c: Point):
  return sign(ccw(a, b, c))
  
def intersects(A, B, inclusive=True):
  '''
  A, B must be Point, Line, Ray, Segment.
  inclusive는 Point에서 무시됨.
  '''
  if isinstance(A, Ray):
    A = Segment(A.p, A.p + A.d * Point.INF)
  elif isinstance(A, Line):
    A = Segment(A.p - A.d * Point.INF, A.p + A.d * Point.INF)
  if isinstance(B, Ray):
    B = Segment(B.p, B.p + B.d * Point.INF)
  elif isinstance(B, Line):
    B = Segment(B.p - B.d * Point.INF, B.p + B.d * Point.INF)

  if isinstance(A, Point):
    if isinstance(B, Point): return A == B

    p, q = B.p, B.q
    # A가 선분 pq 위에 있는지 확인
    if ccw(p, q, A) != 0: return False
    if inclusive:
      return min(p, q) <= A <= max(p, q)
    else:
      return min(p, q) < A < max(p, q)
  if isinstance(B, Point):
    return intersects(B, A, inclusive)

  # A,B is Segment
  a1, a2, b1, b2 = A.p, A.q, B.p, B.q
  r1 = sccw(a1, a2, b1) * sccw(a1, a2, b2)
  r2 = sccw(b1, b2, a1) * sccw(b1, b2, a2)
    
  if r1 == 0 and r2 == 0: # 일직선이거나 한 점을 공유
    if A.d.cross(B.d) != 0: # 한 점 공유
      return inclusive
    else: # 일직선
      if inclusive:
        return not (max(a1, a2) < min(b1, b2) or max(b1, b2) < min(a1, a2))
      else:
        return not (max(a1, a2) <= min(b1, b2) or max(b1, b2) <= min(a1, a2))
  
  if inclusive:
    return r1 <= 0 and r2 <= 0
  else:
    return r1 < 0 and r2 < 0


def dijk(G, start, *, N):
  D = [float('inf')]*N
  D[start] = 0

  candidates = set(range(N))

  while candidates:
    now = ITER(candidates).min(key=lambda x: D[x])
    candidates -= {now}

    for nxt, w in G[now]:
      D[nxt] = min(D[nxt], D[now] + w)

  return D

def gen_pythagorean_triple(N):
  '''
  find all (a,b,c) where a < b < c <= N
  '''
  # N >= c = m²+n² > m²
  for m in trange(2, isqrt(N)+1, desc='gen_pythagorean_triple'):
    # 0 < n < m
    # m, n은 홀짝 다름
    for n in range(2 if m&1 else 1, m, 2):
      # n, m은 서로소
      if gcd(n, m) != 1: continue

      a = m**2 - n**2
      b = 2 * m * n
      c = m**2 + n**2
      a, b = sorted([a,b])

      for k in ITER.count(1).takewhile(lambda k: k*c<=N):
        yield (k*a, k*b, k*c)

def toBase(n: int, b: int) -> str:
  if n == 0: return '0'

  res = []
  while n:
    n, m = divmod(n, b)
    res.append(m)

  return ITER(res[::-1]).join()

def roman2int(s):
  '''
  https://projecteuler.net/about=roman_numerals
  s는 valid여야 함.
  '''
  res = 0

  if 'IV' in s: res += 4; s = s.replace('IV', '')
  if 'IX' in s: res += 9; s = s.replace('IX', '')
  if 'XL' in s: res += 40; s = s.replace('XL', '')
  if 'XC' in s: res += 90; s = s.replace('XC', '')
  if 'CD' in s: res += 400; s = s.replace('CD', '')
  if 'CM' in s: res += 900; s = s.replace('CM', '')

  CS = {
    'I': 1,
    'V': 5,
    'X': 10,
    'L': 50,
    'C': 100,
    'D': 500,
    'M': 1000,
  }
  for c in CS:
    res += s.count(c) * CS[c]

  return res

def int2roman(n):
  '''
  https://projecteuler.net/about=roman_numerals
  valid하고 최소인 문자열 반환.
  '''
  res = ''
  
  x, n = divmod(n, 1000)
  res += 'M' * x

  x, n = divmod(n, 100)
  if x == 9: res += 'CM'
  elif x == 4: res += 'CD'
  else: res += 'D' * (x//5) + 'C' * (x%5)

  x, n = divmod(n, 10)
  if x == 9: res += 'XC'
  elif x == 4: res += 'XL'
  else: res += 'L' * (x//5) + 'X' * (x%5)

  x, n = divmod(n, 1)
  if x == 9: res += 'IX'
  elif x == 4: res += 'IV'
  else: res += 'V' * (x//5) + 'I' * (x%5)

  return res

def sqrt_to_continued_fraction(n):
  d = isqrt(n) # sqrt(n)의 정수 부분
  if issquare(n): return ITER([d])

  res = [d]
  a, b, c = 1, -d, 1 # (a sqrt(n) + b) / c
  h = [(a,b,c)]

  while 1:
    # 역수를 취하면
    # c / (a sqrt(n) + b)
    # c (a sqrt(n) - b) / (a^2 n - b^2)
    # (ac sqrt(n) - bc) / (a^2 n - b^2)
    a, b, c = a*c, -b*c, a**2*n-b**2

    # (a sqrt(n) + b) / c 에서 정수부분 분리
    # d < sqrt(n) < d+1
    # ad+b < a sqrt(n) + b < ad+a+b
    # (ad+b) / c < (a sqrt(n) + b) / c < (ad+a+b) / c

    # ((a*d+b)//c)만큼 분리 (=:k)
    # (a sqrt(n)+b) / c - k
    # = (a sqrt(n) + b - ck) / c
    k = (a*d+b) // c
    res.append(k)
    b -= c * k

    g = gcd(a,b,c)
    a//=g; b//=g; c//=g

    if (a,b,c) in h:
      idx = h.index((a,b,c))
      # 주기 = len(h) - idx

      left, right = ITER(res[:idx+1]), ITER(res[idx+1:])
      return left.chain(right.cycle())

    h.append((a,b,c))

@cache
def partition_number(n, mod=None):
  ''' 분할수 '''
  if n < 0: return 0
  if n == 0: return 1

  res = 0
  for k in count(1):
    if n - k*(3*k-1)//2 < 0: break
    res += (-1)**(k+1&1) * ( partition_number(n - k*(3*k+1)//2) + partition_number(n - k*(3*k-1)//2) )
    if mod: res %= mod
  return res

def continued_fraction_to_fraction(it, n):
  it = it.take(n).reverse()

  res = Fraction(next(it))
  for a in it: res = a + 1/res

  return res

def ispal(s: int | str) -> bool:
  s = str(s)
  return s == s[::-1]

def issquare(n: int | str) -> bool:
  n = int(n)
  return isqrt(n)**2 == n

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
    keys, values, items = fac.keys(), fac.values(), fac.items()
    for tp in ITER(values).map(lambda v: range(v+1)).starproduct():
      yield ITER(keys).zip(tp).starmap(operator.pow).mul()


class Tracker:
  def __init__(self, *, f=lambda x: x, checker=lambda x: True, checkery=lambda y: True, debug=False):
    self.f = f
    self.checker = checker
    self.checkery = checkery
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
    if not self.checker(x): return

    y = self.f(x)
    if not self.checkery(y): return

    if self.debug: print('!', x, '->', y)
    
    self.cnt += 1
    if self.cnt == 1:
      self.mx_x, self.mx = x, y
      self.mn_x, self.mn = x, y
      self.can_calculate = isinstance(y, (int, float, Decimal, Fraction))
      if self.can_calculate:
        self.sum = 0
        self.mul = 1

    if y > self.mx:
      self.mx_x, self.mx = x, y
    if y < self.mn:
      self.mn_x, self.mn = x, y

    if self.can_calculate:
      self.sum += y
      self.mul *= y
      if self.sum > 2**100: self.sum = float('inf')
      if self.sum < -2**100: self.sum = -float('inf')
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

thousand = 1_000
million = 1_000_000
billion = 1_000_000_000

###

