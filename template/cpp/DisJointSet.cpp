namespace DisJointSet {
constexpr int none = -1;
vector<int> nodes;
vector<int> parent;
vector<int> depth;

// [ {s}, {s+1}, ..., {e} ]
void init(int s, int e) {
  for (int i = s; i <= e; i++) {
    nodes.push_back(i);
    parent.push_back(none);
    depth.push_back(1);
  }
}

int getRoot(int target) {
  if (parent[target] == none)
    return target;
  return parent[target] = getRoot(parent[target]);
}

void add(int a, int b) {
  int ar = getRoot(a);
  int br = getRoot(b);

  if (ar == br)
    return; // 이미 같은 집합임

  if (depth[ar] > depth[br])
    parent[br] = ar; // a에 b 합치기
  else
    parent[ar] = br; // b에 a 합치기

  if (depth[ar] == depth[br])
    depth[br]++; // 만약 같았다면 b에 a를 합쳤을 것이고, 깊이가 1 증가할 것
}
} // namespace DisJointSet
