class 우선순위큐:
  def __init__(self, op):
    self.tree = [None]
    self.op = op  # op(a, b): a가 b보다 우선순위가 높다면 True

  def append(self, x):
    l = len(self.tree)
    self.tree.append(x)
    while 1:
      if l == 1:  # root, 변경이 필요하지 않음
        break
      elif not self.op(x, self.tree[l // 2]):  # 변경이 필요하지 않음
        break
      else:
        self.tree[l], self.tree[l // 2] = self.tree[l // 2], self.tree[l]
        l //= 2

  def pop(self):
    if len(self.tree) == 1:
      return None

    r = self.tree[1]
    self.tree[1] = self.tree[-1]
    del self.tree[-1]
    l = 1
    while 1:
      if l * 2 >= len(self.tree):  # 단말 노드, 변경이 필요하지 않음
        break
      elif l * 2 + 1 >= len(self.tree):  # 왼쪽 자식만 있음
        if self.op(self.tree[l], self.tree[l * 2]):  # 변경이 필요하지 않음
          break
        else:
          self.tree[l], self.tree[l * 2] = self.tree[l * 2], self.tree[l]
          break  # 마지막 변경이므로 break
      elif self.op(self.tree[l], self.tree[l * 2]) and self.op(self.tree[l], self.tree[l * 2 + 1]):  # 변경이 필요하지 않음
        break
      else:
        if self.op(self.tree[l * 2], self.tree[l * 2 + 1]):
          self.tree[l], self.tree[l * 2] = self.tree[l * 2], self.tree[l]
          l = l * 2
        else:
          self.tree[l], self.tree[l * 2 +
                                  1] = self.tree[l * 2 + 1], self.tree[l]
          l = l * 2 + 1
    return r
