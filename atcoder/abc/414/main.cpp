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
  int n, k;
  Scan(n, k);
  std::vector<std::vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }

  const int b = std::__lg(std::max(2, n) * 2 - 1) + 1;

  std::vector chs(k + 1, std::vector(n, std::vector<int>{}));
  std::vector jmp(b, std::vector(n, -1));
  std::vector tin(n, 0), tout(n, 0);
  auto timer = 0;
  auto dfs = [&](auto&& self, int v, int fa) -> void {
    jmp[0][v] = fa;
    for (int i = 1; i < b && jmp[i - 1][v] != -1; ++i) {
      jmp[i][v] = jmp[i - 1][jmp[i - 1][v]];
    }
    tin[v] = timer++;
    for (int h = 1, x = fa; x != -1 && h <= k; ++h, x = jmp[0][x]) {
      chs[h][x].emplace_back(v);
    }
    for (const auto u : g[v]) {
      if (u != fa) {
        self(self, u, v);
      }
    }
    tout[v] = timer;
  };
  dfs(dfs, 0, -1);

  auto isAccessor = [&tin, &tout](const int u, const int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  };
  auto lca = [&](int u, const int v) {
    if (isAccessor(u, v)) {
      return u;
    }
    if (isAccessor(v, u)) {
      return v;
    }
    for (int i = b - 1; i >= 0; --i) {
      if (jmp[i][u] != -1 && !isAccessor(jmp[i][u], v)) {
        u = jmp[i][u];
      }
    }
    return jmp[0][u];
  };

  constexpr auto kInf = std::numeric_limits<int>::max() / 2;
  std::vector dist(n, kInf);
  std::queue<int> que;
  dist[0] = 0;
  que.emplace(0);
  while (!que.empty()) {
    const auto v = que.front();
    que.pop();
    for (const auto u : chs[k][v]) {
      if (dist[v] + 1 < dist[u]) {
        dist[u] = dist[v] + 1;
        que.emplace(u);
      }
    }

    for (int upH = 1, x = jmp[0][v]; x != -1 && upH < k; ++upH, x = jmp[0][x]) {
      for (const auto u : chs[k - upH][x]) {
        if (dist[v] + 1 < dist[u] && lca(u, v) == x) {
          dist[u] = dist[v] + 1;
          que.emplace(u);
        }
      }
    }
  }
  for (int i = 1; i < n; ++i) {
    Print(dist[i] == kInf ? -1 : dist[i]);
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
