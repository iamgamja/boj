template <typename T>
i32 sign(T val) {
  return (T(0) < val) - (val < T(0));
}
