i32 lis(vector<i32> &a) {
  vector<i32> M;
  for (auto x: a) {
    auto it = lower_bound(M.begin(), M.end(), x);
    if (it == M.end()) M.push_back(x);
    else *it = x;
  }
  return M.size();
}
