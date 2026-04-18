from collections import deque,defaultdict
import os
_nt=iter(os.read(0,os.fstat(0).st_size).split()).__next__
tok=lambda:_nt().decode()
def ii(N=-1):return int(tok())if N<0 else[ii()for _ in range(N)]

def main():
  pass

main()