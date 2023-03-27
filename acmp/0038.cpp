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
  vector<int> A(n);
  for (auto &a : A) {
    cin >> a;
  }

  auto add = [&](pair<int, int> &p, int which, int val) {
    (which == 0 ? p.first : p.second) += val;
  };
  auto get = [&](pair<int, int> &p, int which) {
    return which == 0 ? p.first : p.second;
  };

  vector<vector<array<bool, 2>>> seen(n, vector<array<bool, 2>>(n, {false, false}));
  vector<vector<array<pair<int, int>, 2>>> cache(n, vector<array<pair<int, int>, 2>>(n, {pair{0, 0}, pair{0, 0}}));
  auto dp = [&](auto f, int l, int r, int which) -> pair<int, int> {
    assert(l <= r);
    if (l == r) {
      auto ret = pair{0, 0};
      add(ret, which, A[l]);
      return ret;
    }
    if (seen[l][r][which]) {
      return cache[l][r][which];
    }

    auto lhs = f(f, l, r - 1, 1 - which);
    add(lhs, which, A[r]);
    auto rhs = f(f, l + 1, r, 1 - which);
    add(rhs, which, A[l]);
    seen[l][r][which] = true;
    return cache[l][r][which] = get(lhs, which) > get(rhs, which) ? lhs : rhs;
  };

  auto res = dp(dp, 0, n - 1, 0);
  if (res.first < res.second) {
    cout << 2;
  } else if (res.first > res.second) {
    cout << 1;
  } else {
    cout << 0;
  }
  cout << '\n';
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