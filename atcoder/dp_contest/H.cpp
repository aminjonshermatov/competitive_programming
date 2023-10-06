#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int mod = 1e9 + 7;
inline void add(int &a, int b) {
  if ((a += b) >= mod) {
    a -= mod;
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<string> g(n);
  for (auto &r : g) {
    cin >> r;
  }

  vector<int> dp(m, 0);
  dp[0] = 1;
  for (int j = 1; j < m && g[0][j] == '.'; ++j) {
    dp[j] = 1;
  }
  for (int i = 1; i < n; ++i) {
    vector ndp(m, 0);
    for (int j = 0; j < m; ++j) {
      if (g[i][j] != '.') continue;
      add(ndp[j], dp[j]);
      if (j > 0) {
        add(ndp[j], ndp[j - 1]);
      }
    }
    dp.swap(ndp);
  }
  cout << dp.back() << '\n';
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
