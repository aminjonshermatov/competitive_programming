#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;
constexpr i64 mod = 1e9 + 7;

inline i64 mul(i64 a, i64 b) { return (a * b) % mod; }
i64 power(i64 a, i64 b) {
  i64 res = 1;
  while (b > 0) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

inline i64 inv(i64 a) { return power(a, mod - 2); }

vector<i64> fact {1}, ifact {1};

i64 F(i64 a) {
  while (fact.size() - 1 < a) {
    fact.emplace_back(mul(fact.back(), fact.size()));
    ifact.emplace_back(inv(fact.back()));
  }
  return fact[a];
}

void solve() {
  array<int, 26> cnt{};
  cnt.fill(0);
  string s; cin >> s;
  for (auto ch : s) {
    ++cnt[ch - 'a'];
  }

  i64 ans = F(s.size());
  for (int ch = 0; ch < 26; ++ch) {
    ans = mul(ans, ifact[cnt[ch]]);
  }
  cout << ans << '\n';
}

bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
