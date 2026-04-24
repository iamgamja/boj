#include "../default.hpp"

/**
 * S[i]를 중심으로 하는 팰린드롬의 최대 길이는 P[(i+1)*2]
 * S[i], S[i+1]을 중심으로 하는 팰린드롬의 최대 길이는 P[(i+1)*2 + 1]
 */
VI manacher(const string &s_) {
  string s = "^#";
  for (const auto &c: s_) s += c, s += "#";
  s += "$";

  VI P(s.size());

  i32 C = 0, R = 0;
  
  for (i32 i=1; i<s.size()-1; i++) {
    if (i < R) P[i] = min(R - i, P[2*C - i]);

    while (s[i - P[i] - 1] == s[i + P[i] + 1]) P[i]++;

    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }

  return P;
}