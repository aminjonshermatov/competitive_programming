#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int n;
  cin >> n;
  vector<i64> as(n);
  for (auto &a : as) {
    cin >> a;
  }

  array<vector<vector<pair<i64, i64>>>, 2> cache{};
  array<vector<vector<bool>>, 2> seen{};
  for (int i = 0; i < 2; ++i) {
    cache[i].assign(n, vector<pair<i64, i64>>(n));
    seen[i].assign(n, vector<bool>(n, false));
  }
  const auto dp = [&](auto &f, int l, int r, bool is_second) -> pair<i64, i64> {
    if (l >= r) {
      return is_second ? pair(i64(0), as[l]) : pair(as[l], i64(0));
    }
    if (seen[is_second][l][r]) {
      return cache[is_second][l][r];
    }
    seen[is_second][l][r] = true;
    if (!is_second) {
      auto [px, py] = f(f, l + 1, r, !is_second);
      px += as[l];
      auto [sx, sy] = f(f, l, r - 1, !is_second);
      sx += as[r];
      cache[is_second][l][r] = px - py > sx - sy ? pair(px, py) : pair(sx, sy);
    } else {
      auto [px, py] = f(f, l + 1, r, !is_second);
      py += as[l];
      auto [sx, sy] = f(f, l, r - 1, !is_second);
      sy += as[r];
      cache[is_second][l][r] = px - py < sx - sy ? pair(px, py) : pair(sx, sy);
    }
    return cache[is_second][l][r];
  };
  auto [x, y] = dp(dp, 0, n - 1, false);
  dbg(x, y);
  cout << x - y << '\n';
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
