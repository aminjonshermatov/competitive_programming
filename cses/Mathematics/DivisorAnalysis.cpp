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

inline i64 mul(i64 a, i64 b, i64 md = mod) { return (a * b) % md; }
inline i64 sub(i64 a, i64 b, i64 md = mod) { return (a + md - b) % md; }

i64 power(i64 a, i64 b, i64 md = mod) {
  i64 ans = 1;
  while (b > 0) {
    if (b & 1) ans = mul(ans, a, md);
    a = mul(a, a, md);
    b >>= 1;
  }
  return ans;
}

inline i64 divm(i64 a, i64 b, i64 md = mod) { return (a * power(b, md - 2)) % md; }

void solve() {
  int n; cin >> n;
  i64 c1 = 1, c2 = 1, sm = 1, pr = 1;
  for (int i = 0; i < n; ++i) {
    i64 p, a; cin >> p >> a;
    c1 = mul(c1, a + 1);
    sm = mul(sm, divm(sub(power(p, a + 1), 1), sub(p, 1)));
    // pr = mul(power(pr, a + 1), power(power(p, divm(mul(a, a + 1), 2)), c2));
    pr = mul(power(pr, a + 1), power(power(p, a * (a + 1) / 2), c2));
    c2 = mul(c2, a + 1, mod - 1);
  }
  cout << c1 << ' ' << sm << ' ' << pr << '\n';
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
