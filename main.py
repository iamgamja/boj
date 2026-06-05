from collections import deque,defaultdict
import os
_nt=iter(os.read(0,os.fstat(0).st_size).split()).__next__
tok=lambda:_nt().decode()
def ii(*A):return[ii(*A[1:])for _ in range(A[0])]if A else int(tok())

###

