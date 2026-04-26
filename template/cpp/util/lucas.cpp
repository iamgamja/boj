#include "../default.hpp"

#include "modint.cpp"

const i32 MOD = 10'007; // O(MOD) 전처리 필요하므로 MOD가 크면 안된다.

using modint = ModInt<MOD>;
vector<modint> fac(MOD);
vector<modint> facinv(MOD);

void init() {
  fac[0] = 1;
  for (i32 i=1; i<MOD; i++) fac[i] = fac[i-1] * i;
  facinv[MOD-1] = fac[MOD-1].inv();
  for (i32 i=MOD-2; i>=0; i--) facinv[i] = facinv[i+1] * (i+1);
}

modint comb(i32 n, i32 k) {
  if (n < k) return 0;
  return fac[n] * facinv[k] * facinv[n-k];
}

modint lucas(i64 n, i64 k) {
  // MOD진법으로 나타냈을 때 자릿수마다 구해 곱할 수 있다.
  modint res = 1;

  while (n && k) {
    res *= comb(n % MOD, k % MOD);
    n /= MOD; k /= MOD;
  }

  return res;
}