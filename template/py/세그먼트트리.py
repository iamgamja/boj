import math


class 세그먼트트리:
  '''
  1-index
  '''

  def __init__(self, a, op):
    self.n = len(a)
    self.op = op
    self.tree = [None] * (2 ** (math.ceil(math.log2(self.n)) + 1))

    def tmp(idx=1, start=1, end=self.n):
      if start == end:
        self.tree[idx] = a[start-1]
      else:
        tmp(idx * 2, start, (start + end) // 2)
        tmp(idx * 2 + 1, (start + end) // 2 + 1, end)
        self.tree[idx] = self.op(self.tree[idx * 2], self.tree[idx * 2 + 1])
    tmp()

  def get(self, left, right):
    def tmp(idx=1, start=1, end=self.n):
      if left > end or right < start:
        return None
      if left <= start and end <= right:
        return self.tree[idx]
      lvalue = tmp(idx * 2, start, (start + end) // 2)
      rvalue = tmp(idx * 2 + 1, (start + end) // 2 + 1, end)
      if lvalue is None:
        return rvalue
      if rvalue is None:
        return lvalue
      return self.op(lvalue, rvalue)
    return tmp()

  def set(self, setIdx, value):
    def tmp(idx=1, start=1, end=self.n):
      if setIdx < start or setIdx > end:
        return
      if start == end:
        self.tree[idx] = value
        return
      tmp(idx * 2, start, (start + end) // 2)
      tmp(idx * 2 + 1, (start + end) // 2 + 1, end)
      self.tree[idx] = self.op(self.tree[idx * 2], self.tree[idx * 2 + 1])
    tmp()
