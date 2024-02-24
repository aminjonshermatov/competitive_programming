#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, m;
  std::cin >> n >> m;
  using i64 = int64_t;
  using T = std::array<i64, 5>;
  std::vector<std::vector<T>> g(n);
  for (int i = 0; i < m; ++i) {
    i64 l, d, k, c, a, b;
    std::cin >> l >> d >> k >> c >> a >> b;
    --a, --b;
    g[b].emplace_back(T{a, l, d, k, c});
  }
  std::vector<i64> dist(n, -1);
  std::priority_queue<std::pair<i64, int>> pq;
  pq.emplace(5E18, n - 1);
  while (!pq.empty()) {
    auto [y, v] = pq.top();
    pq.pop();
    if (dist[v] != -1) {
      continue;
    }
    dist[v] = y;
    for (auto [u, l, d, k, c] : g[v]) {
      auto x = y - c;
      if (x < l) {
        continue;
      }
      pq.emplace(l + std::min(k - 1, (x - l) / d) * d, u);
    }
  }
  for (int v = 0; v + 1 < n; ++v) {
    if (dist[v] == -1) {
      std::cout << "Unreachable\n";
    } else {
      std::cout << dist[v] << '\n';
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}