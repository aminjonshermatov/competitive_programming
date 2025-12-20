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
  int n;
  Scan(n);

  std::vector<std::vector<std::pair<int, int>>> g(n + 1);
  for (int i = 1; i <= n; ++i) {
    int p, y;
    Scan(p, y);
    // p->i
    g[p].emplace_back(i, y);
  }

  std::vector<int> ret;
  [&](this auto dfs, std::vector<int> vs) -> void {
    std::map<int, std::vector<int>> go;
    for (auto v : vs) {
      ret.emplace_back(v);
      for (const auto [u, w] : g[v]) {
        go[w].emplace_back(u);
      }
    }
    for (auto us : go | std::ranges::views::values) {
      std::ranges::sort(us);
      dfs(us);
    }
  }(std::vector{0});
  assert(ret.size() == n + 1);
  for (int i = 1; i <= n; ++i) {
    Print(ret[i]);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
