#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#define _GLIBCXX_DEBUG
#else
#define dbg(...) 42
#endif

using namespace std;

constexpr int N = 15;

void solve() {
  array<vector<int>, N> A{};
  for (int i = 0; i < N; ++i) {
    A[i].resize(i + 1);
    for (auto &x : A[i]) cin >> x;
  }

  for (int i = 1; i < N; ++i) {
    for (int j = 0; j < A[i].size(); ++j) {
      auto mx = A[i - 1][j];
      if (j > 0) mx = max(mx, A[i - 1][j - 1]);
      A[i][j] += mx;
    }
  }

  cout << *max_element(A.back().begin(), A.back().end()) << '\n';
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
