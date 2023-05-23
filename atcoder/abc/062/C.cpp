#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

int64_t solve(int64_t n, int64_t m) {
  if (n % 3 == 0) return 0;
  int64_t ans = m;
  array<int64_t, 3> pos{};
  for (int64_t i = 0; i < n; ++i) {
    pos = {i * (m / 2), i * (m - m / 2), (n - i) * m};
    sort(pos.begin(), pos.end());
    ans = min(ans, pos.back() - pos.front());
  }
  return ans;
}

void solve() {
  int64_t n, m; cin >> n >> m;
  cout << min(solve(n, m), solve(m, n)) << '\n';
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
