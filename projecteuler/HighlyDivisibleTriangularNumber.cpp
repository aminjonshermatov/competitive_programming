#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int LIMIT = 500;

void solve() {
  for (int cur = 1; ; ++cur) {
    int sm = cur * (cur + 1) / 2;
    int divs = 0;
    for (int d = 1; d * d <= sm; ++d) {
      auto [q, r] = div(sm, d);
      if (d > q) break;
      if (r == 0) {
        divs += 1 + (q != d);
      }
    }
    if (divs >= LIMIT) {
      cout << cur << ' ' << sm << '\n';
      return;
    }
  }
  assert(false);
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
