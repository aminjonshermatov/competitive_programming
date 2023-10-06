#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> as(n);
  for (auto &a : as) {
    cin >> a;
  }

  array<vector<int>, 2> cache{};
  for (int which = 0; which < 2; ++which) {
    cache[which].assign(k + 1, -1);
  }
  const auto dp = [&](auto &f, bool which, int left) -> bool {
    int loc = cache[which][left];
    if (loc != -1) return loc;
    loc = false;
    for (auto a : as) {
      if (a > left) break;
      loc |= !f(f, !which, left - a);
    }
    return cache[which][left] = loc;
  };
  cout << (dp(dp, 0, k) ? "First" : "Second") << '\n';
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
