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
  for (auto &a : as) {
    cin >> a;
    a %= 3;
  }
  dbg(as);
  array<array<vector<int>, 3>, 3> cache{};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      cache[i][j].assign(n, -1);
    }
  }
  auto dp = [&](auto &f, int a, int b, int i) -> int {
    auto rem = (a + b + as[i]) % 3;
    if (rem != 0) rem = 3 - rem;
    if (i + 1 == n) {
      return rem;
    }
    if (~cache[a][b][i]) return cache[a][b][i];
    return cache[a][b][i] = rem + f(f, b, (as[i] + rem) % 3, i + 1);
  };
  int ans = 1e9;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      auto tmp = i + j + dp(dp, (as[0] + i) % 3, (as[1] + j) % 3, 2);
      ans = min(ans, tmp);
      dbg("fuck", i, j, tmp);
    }
  }
  cout << ans << '\n';
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
