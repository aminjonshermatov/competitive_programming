#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = int64_t;

void solve() {
  int h, w, n; cin >> h >> w >> n;
  vector<vector<int>> g(h + 1, vector<int>(w + 1, 1));
  for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    g[a][b] = 0;
  }
  vector<vector<int>> pref(h + 1, vector<int>(w + 1, 0));
  for (int i = 1; i <= h; ++i) {
    for (int j = 1; j <= w; ++j) {
      pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + g[i][j];
    }
  }

  auto can = [&](int i, int j, int l) -> bool {
    auto sm = pref[i + l - 1][j + l - 1] - pref[i - 1][j + l - 1] - pref[i + l - 1][j - 1] + pref[i - 1][j - 1];
    return sm == l * l;
  };

  i64 ans = 0;
  for (int i = 1; i <= h; ++i) {
    for (int j = 1; j <= w; ++j) {
      int lo = 0, hi = min(h - i + 1, w - j + 1) + 1;
      while (hi - lo > 1) {
        auto mid = lo + (hi - lo) / 2;
        (can(i, j, mid) ? lo : hi) = mid;
      }
      ans += lo;
    }
  }
  cout << ans << '\n';
}

// #define MEASURE_TIME
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
  cerr << endl
       << "Time: " << elapsed_ms.count() << " ms\n";
#endif
  return 0;
}