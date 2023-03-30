// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

using i64 = ::int64_t ;

void solve() {
  int n, k; cin >> n >> k;

  map<pair<int, int>, i64> cache;
  auto dp = [&](auto f, int cur, int left) -> i64 {
    if (cur == n) return left == 0;
    if (left == 0) return cur == n;
    if (cache.count(make_pair(cur, left)) > 0) return cache[make_pair(cur, left)];
    return cache[make_pair(cur, left)] = f(f, cur + 1, left - 1) + f(f, cur - 1, left - 1);
  };

  cout << dp(dp, 0, k);
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