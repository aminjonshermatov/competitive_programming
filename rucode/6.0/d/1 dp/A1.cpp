//
// Created by aminjon on 3/20/23.
//
#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n, k;
  cin >> n >> k;

  vector<vector<int>> poss;
  vector<int> cur;
  vector<bool> used(n, false);
  auto rec = [&](auto f) -> void {
    if (cur.size() >= n) {
      poss.emplace_back(cur);
      return ;
    }
    for (int i = 1; i <= n; ++i) {
      if (used[i]) continue ;
      if (cur.empty() || abs(cur.back() - i) >= k) {
        cur.push_back(i);
        used[i] = true;
        f(f);
        used[i] = false;
        cur.pop_back();
      }
    }
  };
  rec(rec);
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