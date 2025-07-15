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
  std::vector<std::pair<int, int>> es(n - 1);
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i + 1 < n; ++i) {
    auto& [u, v] = es[i];
    Scan(u, v);
    --u, --v;
    g[u].emplace_back(i);
    g[v].emplace_back(n - 1 + i);
  }

  constexpr auto kInf = std::numeric_limits<int>::max() / 2;
  std::vector dist(k, std::vector(2 * (n - 1), kInf));
  std::vector cnt(k, std::vector(n, 0));
  std::queue<std::pair<int, int>> que;
  auto push = [&](const int eId, const int d) -> void {
    const auto s = d % k;
    if (dist[s][eId] == kInf) {
      dbg(eId,s);
      dist[s][eId] = d;
      que.emplace(eId, d);
    }
  };
  for (auto eId : g[0]) {
    push(eId, 1);
  }
  while (!que.empty()) {
    const auto [eId, d] = que.front();
    que.pop();
    int v;
    {
      auto [x, y] = es[eId % (n - 1)];
      v = eId < (n - 1) ? y : x;
    }
    if (++cnt[d % k][v] > 2) {
      continue;
    }
    for (const auto neId : g[v]) {
      if (d % k != 0 && eId % (n - 1) == neId % (n - 1)) {
        continue;
      }
      push(neId, d + 1);
    }
  }
  std::vector ret(n, kInf);
  for (int i = 0; i < 2 * (n - 1); ++i) {
    int v;
    auto [x, y] = es[i % (n - 1)];
    v = i < (n - 1) ? y : x;
    ret[v] = std::min(ret[v], dist[0][i]);
  }
  for (int i = 1; i < n; ++i) {
    const auto d = ret[i];
    if (d == kInf) {
      Print(-1);
    } else {
      assert(d % k == 0);
      Print(d / k);
    }
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
