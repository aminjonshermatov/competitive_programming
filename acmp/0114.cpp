// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, k; cin >> n >> k;

  vector<vector<int>> cache(n, vector<int>(k, -1));
  auto dp = [&](auto f, int len, int prv) -> int {
    if (len >= n) return 1;
    if (~cache[len][prv]) return cache[len][prv];

    int cur = 0;
    for (int d = 0; d < k; ++d) {
      if (d == 0 && prv == 0) continue ;
      cur += f(f, len + 1, d);
    }
    return cache[len][prv] = cur;
  };
  cout << dp(dp, 0, 0);
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