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
  int n; cin >> n;
  vector<int> as(n);
  i64 sm = 0, cnt = 0;
  bool neg = false;
  for (auto &a : as) {
    cin >> a;
    sm += abs(a);
    if (a > 0) {
      cnt += neg;
      neg = false;
    } else {
      neg |= a < 0;
    }
  }
  cnt += neg;
  cout << sm << ' ' << cnt << '\n';
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
