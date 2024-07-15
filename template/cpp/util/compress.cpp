template<typename A>
/** 좌표압축 */
function<i32(A)> compress(vector<A> v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  return [v = move(v)](A x) {
    return lower_bound(v.begin(), v.end(), x) - v.begin();
  };
}
