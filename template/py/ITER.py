from itertools import *
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
  def trange(*args, **kargs):
    return ITER(trange(*args, **kargs))

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

  def enumerate(self):
    return ITER.count(0).zip(self.it)
  
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
