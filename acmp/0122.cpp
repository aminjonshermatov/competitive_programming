// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve1() {
  int n; cin >> n;
  vector<int> A(n);
  for (auto &a : A) cin >> a;

  vector<int> dp(n, 1);
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (A[j] < A[i]) dp[i] = max(dp[i], dp[j] + 1);
    }
  }

  cout << *max_element(dp.begin(), dp.end()) << '\n';
}

void solve2() {
  int n; cin >> n;
  vector<int> A(n);
  for (auto &a : A) cin >> a;

  vector<int> dp;
  for (auto a : A) {
    auto it = lower_bound(dp.begin(), dp.end(), a);
    if (it == dp.end()) dp.emplace_back(a);
    else *it = a;
  }
  cout << dp.size() << '\n';
}

void solve() {
  //solve1();
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