#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

#define ing lone long

void brut(int n) {
  vector<int> pw(n + 1);
  pw[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pw[i] = pw[i - 1] * 10;
  }
  auto is_pal = [&](string s) {
    for (int i = 0; i < s.size() / 2; ++i) {
      if (s[i] != s[s.size() - i - 1]) {
        return false;
      }
    }
    return true;
  };
  for (int k = 1; k < n; ++k) {
    for (int x = pw[n - 1]; x < pw[n]; ++x) {
      auto s = to_string(x);
      bool ok = true;
      for (int i = 0; i < n && ok; ++i) {
        for (int j = i + k; j < n && ok; ++j) {
          ok &= !is_pal(s.substr(i, j - i + 1));
        }
      }
      if (ok) {
        int sm = 0;
        for (auto tmp = x; tmp > 0; ) {
          sm += tmp % 10;
          tmp /= 10;
        }
        dbg(n, k, x, sm);
        break;
      }
    }
  }

}

void solve() {
  int64_t n, k; cin >> n >> k;
  auto x = k + 2 + (k - 1) / 2;
  int64_t cnt = n / x;
  dbg(x, cnt);
  auto sm = cnt * 3;
  auto left = n - cnt * x;
  if (left > k + 1) sm += 3;
  else if (left > 0) sm += 1;
  // sm += n > cnt * (k + 2);
  cout << sm << '\n';
}

bool is_multi = true;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
  return 0;
}
