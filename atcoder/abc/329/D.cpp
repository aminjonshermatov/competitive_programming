#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::set<std::pair<int, int>> s;
  for (int i = 1; i <= n; ++i) {
    s.emplace(0, -i);
  }
  dbg(s);
  std::vector<int> votes(n + 1, 0);
  for (int i = 0; i < m; ++i) {
    int a;
    std::cin >> a;
    auto it = s.lower_bound(std::pair(votes[a], -a));
    auto p = *it;
    s.erase(it);
    assert(p.second == -a);
    p.first = ++votes[a];
    s.emplace(p);
    std::cout << -s.rbegin()->second << ' ';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}