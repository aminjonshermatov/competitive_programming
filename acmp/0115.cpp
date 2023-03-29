// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve1() {
  int n, m; cin >> n >> m;
  vector<vector<int>> M(n, vector<int>(m));
  for (auto &r : M) {
    for (auto &x : r) {
      cin >> x;
    }
  }

  vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + M[i - 1][j - 1];
    }
  }

  auto sum = [&](int i1, int j1, int i2, int j2) -> int {
    assert(i1 >= i2);
    assert(j1 >= j2);
    return pref[i1 + 1][j1 + 1] - pref[i1 + 1][j2] - pref[i2][j1 + 1] + pref[i2][j2];
  };

  int ans =  numeric_limits<int>::min();
  for (int i1 = 0; i1 < n; ++i1) {
    for (int j1 = 0; j1 < m; ++j1) {
      for (int i2 = 0; i2 <= i1; ++i2) {
        for (int j2 = 0; j2 <= j1; ++j2) {
          ans = max(ans, sum(i1, j1, i2, j2));
        }
      }
    }
  }
  cout << ans << '\n';
}

inline constexpr auto ninf = numeric_limits<int>::min();
void solve2() {
  int n, m; cin >> n >> m;
  vector<vector<int>> M(n, vector<int>(m));
  for (auto &r : M) {
    for (auto &x : r) {
      cin >> x;
    }
  }

  int ans = ninf;
  for (int l = 0; l < m; ++l) {
    vector<int> col_sum(n, 0);
    for (int r = l; r < m; ++r) {
      for (int i = 0; i < n; ++i) {
        col_sum[i] += M[i][r];
      }

      int cur = -1e7;
      for (auto s : col_sum) {
        cur = max(s, cur + s);
        ans = max(ans, cur);
      }
    }
  }

  cout << ans << '\n';
}

void solve() {
  solve2();
}

//#define MEASURE_TIME
bool is_multi = false;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
#ifdef MEASURE_TIME
  auto start = chrono::steady_clock::now();
#endif
  int T = 1;
  if (is_multi) cin >> T;
  for (int tc = 1; tc <= T; ++tc) solve();
#ifdef MEASURE_TIME
  auto finish = chrono::steady_clock::now();
  auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(finish - start);
  cerr << endl << "Time: " << elapsed_ms.count() << " ms\n";
#endif
  return 0;
}