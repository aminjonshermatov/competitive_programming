#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;
constexpr i64 P = 47, mod = 10000001041ll;
inline i64 add(i64 a, i64 b) { return (a + b) % mod; }
inline i64 mul(i64 a, i64 b) { return (a * b) % mod; }
inline i64 sub(i64 a, i64 b) { return (a + mod - b) % mod; }

void solve() {
  string t, p;
  cin >> t >> p;

  i64 p_hash = 0;
  for (auto ch : p) {
    p_hash = add(mul(p_hash, P), ch - 'a' + 1);
  }
  i64 pw = 1;
  for (int i = 1; i < p.size(); ++i) {
    pw = mul(pw, P);
  }

  int cnt = 0;
  i64 t_hash = 0;
  for (int i = 0; i < t.size(); ++i) {
    if (i >= p.size()) {
      t_hash = sub(t_hash, mul(t[i - p.size()] - 'a' + 1, pw));
    }
    t_hash = add(mul(t_hash, P), t[i] - 'a' + 1);
    cnt += i + 1 >= p.size() && add(p_hash, mod) == add(t_hash, mod);
  }
  cout << cnt << '\n';
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
