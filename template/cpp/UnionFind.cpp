class UnionFind {
  private:
  const int none = INT_MIN;
  vector<int> nodes;
  vector<int> parent;
  vector<int> depth;

  public:
  // [s, e]
  DisJointSet(int s, int e) {
    for (int i = 0; i < s; i++) { // index를 맞추기 위한
      nodes.push_back(none);
      parent.push_back(none);
      depth.push_back(none);
    }

    for (int i = s; i <= e; i++) {
      nodes.push_back(i);
      parent.push_back(none);
      depth.push_back(1);
    }
  }

  int find(int target) {
    if (parent[target] == none)
      return target;
    return parent[target] = find(parent[target]);
  }

  // O(logN)
  void merge(int a, int b) {
    int ar = find(a);
    int br = find(b);

    if (ar == br) return;

    if (depth[ar] > depth[br])
      parent[br] = ar; // a에 b 합치기
    else
      parent[ar] = br; // b에 a 합치기

    if (depth[ar] == depth[br])
      depth[br]++; // 만약 같았다면 b에 a를 합쳤을 것이고, 깊이가 1 증가할 것
  }
};
