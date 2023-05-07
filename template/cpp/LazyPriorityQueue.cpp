#ifndef mainfile
#include <bits/stdc++.h>
using namespace std;
#endif

template <typename T, typename cmp = less<T>>
class LazyPriorityQueue {
  private:
  priority_queue<T, vector<T>, cmp> q;
  map<T, int> lazy;
  map<T, int> count;

  public:
  LazyPriorityQueue(vector<T> arr = {}) {
    for (T x : arr) {
      q.push(x);
    }
  };

  void push(T x) {
    q.push(x);
    count[x]++;
  }

  T pop() {
    while (!q.empty()) {
      T tmp = q.top();
      q.pop();
      if (lazy[tmp] == 0) {
        count[tmp]--;
        return tmp;
      }
      lazy[tmp]--;
    }
    throw runtime_error("Queue is empty.");
  }

  bool canRemove(T x) {
    return count[x] != 0;
  }

  void remove(T x) {
    assert(canRemove(x));

    lazy[x]++;
    count[x]--;
  }
};
