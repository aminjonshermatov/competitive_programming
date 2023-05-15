#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<vector<int>> g(n, vector<int>(n));
  for (auto &r : g) {
    for (auto &x : r) {
      cin >> x;
    }
  }

  auto up = [&]() -> int {
    int ans = 0;
    for (int i = 0; i + 3 < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int cur = 1;
        for (int k = 0; k < 4; ++k) {
          cur *= g[i + k][j];
        }
        ans = max(ans, cur);
      }
    }
    return ans;
  };
  auto down = [&]() -> int {
    int ans = 0;
    for (int i = n - 4; i >= 0; --i) {
      for (int j = 0; j < n; ++j) {
        int cur = 1;
        for (int k = 0; k < 4; ++k) {
          cur *= g[i + k][j];
        }
        ans = max(ans, cur);
      }
    }
    return ans;
  };
  auto left = [&]() -> int {
    int ans = 0;
    for (int j = 0; j + 3 < n; ++j) {
      for (int i = 0; i < n; ++i) {
        int cur = 1;
        for (int k = 0; k < 4; ++k) {
          cur *= g[i][j + k];
        }
        ans = max(ans, cur);
      }
    }
    return ans;
  };
  auto right = [&]() -> int {
    int ans = 0;
    for (int j = n - 4; j >= 0; --j) {
      for (int i = 0; i < n; ++i) {
        int cur = 1;
        for (int k = 0; k < 4; ++k) {
          cur *= g[i][j + k];
        }
        ans = max(ans, cur);
      }
    }
    return ans;
  };
  auto diag1 = [&]() -> int {
    int ans = 0;
    for (int i = 0; i + 3 < n; ++i) {
      for (int j = 0; j + 3 < n; ++j) {
        int cur = 1;
        for (int k = 0; k < 4; ++k) {
          cur *= g[i + k][j + k];
        }
        ans = max(ans, cur);
      }
    }
    return ans;
  };
  auto diag2 = [&]() -> int {
    int ans = 0;
    for (int i = 3; i < n; ++i) {
      for (int j = 0; j + 3 < n; ++j) {
        int cur = 1;
        for (int k = 0; k < 4; ++k) {
          cur *= g[i - k][j + k];
        }
        ans = max(ans, cur);
      }
    }
    return ans;
  };

  cout << max({up(), down(), left(), right(), diag1(), diag2()}) << '\n';
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
