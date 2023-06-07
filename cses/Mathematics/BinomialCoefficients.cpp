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
  i64 ans = 1;
  while (b > 0) {
    if (b & 1) ans = mul(ans, a);
    a = mul(a, a);
    b >>= 1;
  }
  return ans;
}

inline i64 inv(i64 a) { return power(a, mod - 2); }

vector<i64> fact = {1};
vector<i64> ifact = {1};

i64 C(i64 n, i64 k) {
  if (k < 0 || k > n) return 0;
  while (fact.size() - 1 < n) {
    fact.emplace_back(mul(fact.size(), fact.back()));
    ifact.emplace_back(inv(fact.back()));
  }
  return mul(fact[n], mul(inv(fact[k]), inv(fact[n - k])));
}

void solve() {
  i64 n, k; cin >> n >> k;
  cout << C(n, k) << '\n';
}

bool is_multi = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
