#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  i64 n, k;
  cin >> n >> k;
  vector<i64> ps(k);
  for (auto &p : ps) cin >> p;

  i64 cnt = 0;
  for (int mask = 1; mask < (1 << k); ++mask) {
    i64 cur = n;
    for (int i = 0; i < k; ++i) {
      if (mask >> i & 1) {
        cur /= ps[i];
      }
    }

    if (__builtin_popcount(mask) & 1) {
      cnt += cur;
    } else {
      cnt -= cur;
    }
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
