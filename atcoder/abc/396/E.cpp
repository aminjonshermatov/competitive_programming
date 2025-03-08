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
  int n, m;
  Scan(n, m);
  std::vector g(n, std::vector<std::pair<int, int>>{});
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    Scan(u, v, w);
    --u, --v;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  std::vector vis(n, false);
  std::vector vals(n, 0);
  auto bfs = [&](const int from) {
    assert(!vis[from]);
    std::queue<int> que;
    std::vector<int> comp;
    vis[from] = true;
    vals[from] = 0;
    comp.emplace_back(from);
    for (que.emplace(from); !que.empty(); que.pop()) {
      const auto v = que.front();
      for (const auto [u, w] : g[v]) {
        if (!vis[u]) {
          vis[u] = true;
          vals[u] = vals[v] ^ w;
          comp.emplace_back(u);
          que.emplace(u);
        } else if (vals[u] != (vals[v] ^ w)) {
          return std::vector<int>{};
        }
      }
    }
    return comp;
  };
  std::vector ret(n, 0);
  for (int v = 0; v < n; ++v) {
    if (vis[v]) {
      continue;
    }
    const auto comp = bfs(v);
    if (comp.empty()) {
      Println(-1);
      return;
    }
    dbg(comp,vis);
    for (int b = 30; b >= 0; --b) {
      auto cnt1 = 0;
      for (const auto u : comp) {
        cnt1 += vals[u] >> b & 1;
      }
      if (cnt1 < std::ssize(comp) - cnt1) {
        for (const auto u : comp) {
          if (vals[u] >> b & 1) {
            ret[u] |= 1 << b;
          }
        }
      } else {
        for (const auto u : comp) {
          if (~vals[u] >> b & 1) {
            ret[u] |= 1 << b;
          }
        }
      }
    }
  }
  for (auto a : ret) {
    Print(a);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
