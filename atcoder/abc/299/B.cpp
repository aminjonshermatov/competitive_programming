// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;

void solve() {
  int n, t; cin >> n >> t;
  vector<int> C(n), R(n);
  for (auto &c : C) cin >> c;
  for (auto &r : R) cin >> r;

  vector<int> one, two;
  for (int i = 0; i < n; ++i) {
    if (C[i] == t) {
      one.push_back(i);
    } else if (C[i] == C[0]) {
      two.push_back(i);
    }
  }
  sort(one.begin(), one.end(), [&](int i, int j) {
    return R[i] > R[j];
  });
  sort(two.begin(), two.end(), [&](int i, int j) {
    return R[i] > R[j];
  });

  if (one.empty()) {
    assert(!two.empty());
    cout << two[0] + 1 << '\n';
  } else {
    cout << one[0] + 1 << '\n';
  }
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
