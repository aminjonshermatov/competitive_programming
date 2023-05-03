// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;

constexpr i64 mod = 1e9 + 7;

i64 mul(i64 a, i64 b) {
  return (a * b) % mod;
}

i64 power(i64 a, i64 b) {
  i64 ans = 1;
  while (b > 0) {
    auto [q, r] = lldiv(b, 2);
    if (r) ans = mul(ans, a);
    a = mul(a, a);
    b = q;
  }
  return ans;
}

void solve() {
  i64 a, b; cin >> a >> b;
  cout << power(a, b) << '\n';
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
