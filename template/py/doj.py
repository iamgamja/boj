from collections import deque,defaultdict
tok=iter(open(0).read().split()).__next__
def ii(*A):return[ii(*A[1:])for _ in range(A[0])]if A else int(tok())

###

