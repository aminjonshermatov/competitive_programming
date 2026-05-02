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
  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    Scan(u, v);
    --u, --v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  int w;
  Scan(w);
  std::vector<std::string> infos(n);
  for (auto& info : infos) {
    Scan(info);
  }

  std::vector st(w, std::vector(n, -1));
  auto dfs = [&](this auto self, int city, int day) -> int {
    assert(std::clamp(day, 0, w - 1) == day);
    if (infos[city][day] != 'o') {
      assert(infos[city][day] == 'x');
      return 0;
    }
    auto& loc = st[day][city];
    if (loc == 2) {
      return 1;
    }
    if (loc != -1) {
      return loc;
    }
    loc = 2;
    const auto nday = (day + 1) % w;
    auto can = self(city, nday);
    for (auto u : g[city]) {
      can |= self(u, nday);
    }
    return loc = can;
  };

  for (int ini = 0; ini < n; ++ini) {
    if (dfs(ini, 0)) {
      Println("Yes");
      return;
    }
  }
  Println("No");
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
