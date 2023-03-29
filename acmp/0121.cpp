// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n; cin >> n;
  vector<int> coordinates(n);
  for (auto &x : coordinates) {
    cin >> x;
  }

  sort(coordinates.begin(), coordinates.end());
  vector<int> edges;
  edges.reserve(n - 1);
  for (int i = 1; i < n; ++i) {
    edges.emplace_back(coordinates[i] - coordinates[i - 1]);
  }

  vector<array<int, 2>> cache(n, array<int, 2>{-1,-1});
  auto dp = [&](auto f, int idx, bool usedPrev) -> int {
    if (idx >= n - 1) return usedPrev ? 0 : 1e7;
    if (~cache[idx][usedPrev]) return cache[idx][usedPrev];
    int res = f(f, idx + 1, true) + edges[idx];
    if (usedPrev) res = min(res, f(f, idx + 1, false));
    return cache[idx][usedPrev] = res;
  };

  cout << dp(dp, 0, false) << '\n';
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