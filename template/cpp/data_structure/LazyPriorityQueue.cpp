template <typename T, typename cmp = less<T>>
class LazyPriorityQueue {
  private:
  priority_queue<T, vector<T>, cmp> q;
  map<T, i32> lazy;
  map<T, i32> count;
  i32 countall = 0;

  public:
  LazyPriorityQueue(vector<T> &arr = {}) {
    for (auto x: arr) push(x);
  }

  void push(T x) {
    q.push(x);
    count[x]++;
    countall++;
  }

  void remove(T x) {
    lazy[x]++;
    count[x]--;
    countall--;
  }

  bool empty() {
    return countall != 0;
  }

  T pop() {
    while (!q.empty()) {
      T tmp = q.top(); q.pop();
      if (lazy[tmp] == 0) {
        count[tmp]--;
        countall--;
        return tmp;
      }
      lazy[tmp]--;
      countall--;
    }
    throw runtime_error("Queue is empty.");
  }
};
