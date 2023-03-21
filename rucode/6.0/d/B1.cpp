//
// Created by aminjon on 3/20/23.
//
#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n; cin >> n;
  vector<string> poss;
  string cur;
  auto rec = [&](auto f, int open, int closed) -> void {
    if (open + closed >= 2 * n) {
      poss.emplace_back(cur);
      return ;
    }

    if (open < n) {
      cur.push_back('(');
      f(f, open + 1, closed);
      cur.pop_back();
    }
    if (open - closed > 0 && closed < n) {
      cur.push_back(')');
      f(f, open, closed + 1);
      cur.pop_back();
    }
  };
  rec(rec, 0, 0);
  for (auto &s : poss) cout << s << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  solve();
}