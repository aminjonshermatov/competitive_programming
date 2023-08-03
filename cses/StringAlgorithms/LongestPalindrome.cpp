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
  string s;
  cin >> s;

  const auto n = int(s.size());
  vector<i64> pw(n + 1), hl(n), hr(n);
  pw[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pw[i] = mul(pw[i - 1], P);
  }
  for (i64 h = 0, i = 0; i < n; ++i) {
    hl[i] = h = add(mul(h, P), s[i] - 'a' + 1);
  }
  for (i64 h = 0, i = n - 1; i >= 0; --i) {
    hr[i] = h = add(mul(h, P), s[i] - 'a' + 1);
  }

  auto getL = [&](int l, int r) -> i64 {
    if (!(0 <= l && l <= r && r < n)) {
      dbg(l, r);
    }
    assert(0 <= l && l <= r && r < n);
    return sub(hl[r], l > 0 ? mul(hl[l - 1], pw[r - l + 1]) : 0);
  };
  auto getR = [&](int l, int r) -> i64 {
    assert(0 <= l && l <= r && r < n);
    return sub(hr[l], r + 1 < n ? mul(hr[r + 1], pw[r - l + 1]) : 0);
  };

  int idx = 0, len = 1;
  for (int i = 0; i < n; ++i) {
    { // odd-length
      int lo = 1, hi = min(i + 1, n - i) + 1;
      while (hi - lo > 1) {
        auto mid = lo + (hi - lo) / 2;
        auto lhs = getL(i - mid + 1, i);
        auto rhs = getR(i, i + mid - 1);
        (add(lhs, mod) == add(rhs, mod) ? lo : hi) = mid;
      }
      auto nlen = lo * 2 - 1;
      if (nlen > len) {
        idx = i - lo + 1;
        len = nlen;
      }
    }
    if (i + 1 < n) { // even-length
      int lo = 0, hi = min(i + 1, n - i - 1) + 1;
      while (hi - lo > 1) {
        auto mid = lo + (hi - lo) / 2;
        auto lhs = getL(i - mid + 1, i);
        auto rhs = getR(i + 1, i + mid);
        (add(lhs, mod) == add(rhs, mod) ? lo : hi) = mid;
      }
      auto nlen = lo * 2;
      if (nlen > len) {
        idx = i - lo + 1;
        len = nlen;
      }
    }
  }
  assert(idx + len <= n);
  for (int i = 0; i < len; ++i) {
    cout << s[idx + i];
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
