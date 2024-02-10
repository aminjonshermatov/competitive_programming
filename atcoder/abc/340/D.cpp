#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

void solve() {
  int n;
  std::cin >> n;
  std::vector<std::vector<std::pair<int, i64>>> g(n);
  for (int i = 0; i + 1 < n; ++i) {
    int a, b, x;
    std::cin >> a >> b >> x;
    --x;
    g[i].emplace_back(i + 1, a);
    g[i].emplace_back(x, b);
  }
  using T = std::pair<i64, int>;
  std::priority_queue<T, std::vector<T>, std::greater<>> pq;
  constexpr auto inf = std::numeric_limits<i64>::max() / 2;
  std::vector<i64> dist(n, inf);
  pq.emplace(dist[0] = 0, 0);
  while (!pq.empty()) {
    auto [d, v] = pq.top();
    pq.pop();
    if (d != dist[v]) {
      continue;
    }
    for (auto [u, w] : g[v]) {
      if (d + w < dist[u]) {
        pq.emplace(dist[u] = d + w, u);
      }
    }
  }
  dbg(dist);
  std::cout << dist[n - 1] << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}