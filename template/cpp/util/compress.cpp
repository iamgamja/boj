template<typename A>
/** 좌표압축 */
function<i32(A)> compress(vector<A> v) {
  sort(ALL(v));
  v.erase(unique(ALL(v)), v.end());
  return [v = move(v)](A x) {
    return lower_bound(ALL(v), x) - v.begin();
  };
}
