#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

constexpr auto inf = numeric_limits<i64>::max();

void solve() {
  i64 x, y, z;
  cin >> x >> y >> z;
  string s;
  cin >> s;
  const int n(s.size());

  vector<array<i64, 2>> cache(n, {-1, -1});
  auto dp = [&](auto &f, int i, int capslock) -> i64 {
    if (i >= n) return 0;
    if (~cache[i][capslock]) return cache[i][capslock];
    i64 loc = inf;
    if (s[i] == 'A') {
      if (capslock) {
        loc = min({loc, f(f, i + 1, capslock) + x, f(f, i + 1, 1 ^ capslock) + z + y});
      } else {
        loc = min({loc, f(f, i + 1, capslock) + y, f(f, i + 1, 1 ^ capslock) + z + x});
      }
    } else {
      if (capslock) {
        loc = min({loc, f(f, i + 1, capslock) + y, f(f, i + 1, 1 ^ capslock) + z + x});
      } else {
        loc = min({loc, f(f, i + 1, capslock) + x, f(f, i + 1, 1 ^ capslock) + z + y});
      }
    }
    return cache[i][capslock] = loc;
  };
  cout << dp(dp, 0, 0) << '\n';
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
