#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;
constexpr i64 P = 97, mod = 1000001269ll;
inline i64 add(i64 a, i64 b) { return (a + b) % mod; }
inline i64 mul(i64 a, i64 b) { return (a * b) % mod; }
inline i64 sub(i64 a, i64 b) { return (a + mod - b) % mod; }

void solve() {
  string t;
  cin >> t;

  const auto n = int(t.size());
  vector<i64> pw(n + 1), hs(n);
  pw[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pw[i] = mul(pw[i - 1], P);
  }
  for (i64 h = 0, i = 0; i < n; ++i) {
    hs[i] = h = add(mul(h, P), t[i] - 'a' + 1);
  }

  auto get = [&](int l, int r) -> i64 {
    assert(l >= 0 && l <= r && r < n);
    return sub(hs[r], l > 0 ? mul(hs[l - 1], pw[r - l  +1]) : 0);
  };

  for (int len = 1; len <= n; ++len) {
    bool ok = true;
    for (int i = len - 1; i - len + 1 < n; i += len) {
      ok &= add(get(0, min(i, n - 1) - i + len - 1), mod) == add(get(i - len + 1, min(i, n - 1)), mod);
    }
    if (ok) {
      cout << len << ' ';
    }
  }
  cout << '\n';
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
