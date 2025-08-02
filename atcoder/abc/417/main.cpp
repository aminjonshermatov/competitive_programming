#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void Solve() {
  int n, m, x, y;
  Scan(n, m, x, y);
  --x, --y;

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;

    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  for (int i = 0; i < n; ++i) {
    std::ranges::sort(g[i]);
  }

  std::vector nxt(n, -1), dst(n, n);
  using T = std::tuple<int, int>;
  auto pq = std::priority_queue(std::greater<T>{}, std::vector<T>{});
  nxt[y] = -1;
  pq.emplace(dst[x] = x, x);
  while (!pq.empty()) {
    const auto [d, v] = pq.top();
    pq.pop();
    if (dst[v] != d || v == y) {
      continue;
    }
    dbg(d,v);
    for (auto u : g[v]) {
      if (v < dst[u]) {
        nxt[v] = u;
        pq.emplace(dst[u] = v, u);
      }
    }
  }
  std::vector<int> path;
  dbg(nxt);
  for (auto i = x; i != y; i = nxt[i]) {
    dbg(i);
    path.emplace_back(i);
  }
  path.emplace_back(y);
  for (auto a : path) {
    Print(a + 1);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);


  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}
