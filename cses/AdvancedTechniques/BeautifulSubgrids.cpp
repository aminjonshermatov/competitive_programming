#include <bits/stdc++.h>

#pragma GCC target("popcnt")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int NAX = 3000;
using i64 = int64_t;

void solve() {
  int n; cin >> n;
  vector<bitset<NAX>> as(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char c; cin >> c;
      as[i][j] = c - '0';
    }
  }
  i64 ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      i64 cnt = (as[i] & as[j]).count();
      ans += cnt * (cnt - 1) / 2;
    }
  }
  cout << ans << '\n';
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
