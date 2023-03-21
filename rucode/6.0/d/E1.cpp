//
// Created by aminjon on 3/21/23.
//
#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n; cin >> n;
  vector<vector<int>> poss;
  vector<int> cur;

  auto rec = [&](auto f, int sum, int last) -> void {
    if (sum == 0) {
      poss.emplace_back(cur);
      return ;
    }

    for (int k = 1; k <= last; ++k) {
      if (sum - k < 0) break ;
      cur.emplace_back(k);
      f(f, sum - k, k);
      cur.pop_back();
    }
  };

  rec(rec, n, n);

  for (auto &p : poss) {
    for (auto x : p) cout << x << ' ';
    cout << '\n';
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}