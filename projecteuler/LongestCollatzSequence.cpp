#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;

void solve() {
  map<i64, i64> cache;
  auto f = [&](auto &f, i64 x) -> i64 {
    if (x == 1) return 1;
    if (auto it = cache.find(x); it != cache.end()) return it->second;
    return cache[x] = 1 + (x & 1 ? f(f, 3 * x + 1) : f(f, x / 2));
  };

  pair<i64, i64> ans{-1, -1};
  for (i64 cur = 1; cur < 1e6; ++cur) {
    auto c = f(f, cur);
    if (c > ans.first) {
      ans = pair(c, cur);
    }
  }
  cout << ans.first << ' ' << ans.second << '\n';
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
