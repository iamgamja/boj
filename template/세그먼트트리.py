class 세그먼트트리:
  '''
  1-index
  '''

  def __init__(self, a, op):
    self.a = [None] + a
    self.op = op
    self.tree = [None] * (2 ** (math.ceil(math.log2(len(self.a)-1))+1))

    def tmp(idx=1, start=1, end=len(self.a)-1):
      if start == end:
        self.tree[idx] = self.a[start]
      else:
        tmp(idx*2, start, (start+end)//2)
        tmp(idx*2+1, (start+end)//2+1, end)
        self.tree[idx] = self.op(self.tree[idx*2], self.tree[idx*2+1])
    tmp()

  def get(self, left, right):
    def tmp(idx=1, start=1, end=len(self.a)-1):
      if left > end or right < start:
        return None
      if left <= start and end <= right:
        return self.tree[idx]
      lvalue = tmp(idx*2, start, (start+end)//2)
      rvalue = tmp(idx*2+1, (start+end)//2+1, end)
      if lvalue is None:
        return rvalue
      if rvalue is None:
        return lvalue
      return self.op(lvalue, rvalue)
    return tmp()

  def set(self, setIdx, value):
    diff = value - self.a[setIdx]
    self.a[setIdx] = value

    def tmp(idx=1, start=1, end=len(self.a)-1):
      if setIdx < start or setIdx > end:
        return
      self.tree[idx] += diff
      if start != end:
        tmp(idx*2, start, (start+end)//2)
        tmp(idx*2+1, (start+end)//2+1, end)
    tmp()
