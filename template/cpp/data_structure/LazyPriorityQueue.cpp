template <typename T, typename cmp = less<T>>
class LazyPriorityQueue {
  private:
  priority_queue<T, vector<T>, cmp> q;
  map<T, i32> lazy;
  i32 countall = 0;

  public:
  LazyPriorityQueue(vector<T> &arr) {
    for (auto x: arr) push(x);
  }
  LazyPriorityQueue() {}

  void push(T x) {
    q.push(x);
    countall++;
  }

  void remove(T x) {
    lazy[x]++;
    countall--;
  }

  bool empty() {
    return countall == 0;
  }

  T pop() {
    while (!q.empty()) {
      T tmp = q.top(); q.pop();
      if (lazy[tmp] == 0) {
        countall--;
        return tmp;
      }
      lazy[tmp]--;
    }
    throw runtime_error("Queue is empty.");
  }
};
