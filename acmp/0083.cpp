// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t;

void solve() {
  int n, m; cin >> n >> m;
  if (n > m) swap(n, m);
  // suppose n <= m

  auto check = [&](int m1, int m2) -> bool {
    auto m = m1 & m2;
    m &= (1 << n) - 1;
    while (m > 0) {
      if ((m & 3) == 3) return false;
      m >>= 1;
    }
    m = (~m1) & (~m2);
    m &= (1 << n) - 1;
    while (m > 0) {
      if ((m & 3) == 3) return false;
      m >>= 1;
    }
    return true;
  };

  vector<i64> dp(1 << n, 1);
  for (int j = 1; j < m; ++j) {
    vector<i64> ndp(1 << n, 0);
    for (int mask1 = 0; mask1 < (1 << n); ++mask1) {
      for (int mask2 = 0; mask2 < (1 << n); ++mask2) {
        if (check(mask1, mask2)) {
          ndp[mask2] += dp[mask1];
        }
      }
    }
    ndp.swap(dp);
  }

  cout << accumulate(dp.begin(), dp.end(), i64(0)) << '\n';
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