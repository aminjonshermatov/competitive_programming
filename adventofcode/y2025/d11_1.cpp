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
  std::map<std::string, std::set<std::string>> g;
  for (std::string s; ; s.clear()) {
    std::getline(std::cin, s);
    if (s.empty()) {
      break;
    }
    const auto pos = s.find(':');
    assert(pos != std::string::npos);
    assert(s[pos + 1] == ' ');
    const auto src = s.substr(0, pos);
    for (const auto dst : s.substr(pos + 2, s.size() - pos - 2) | std::ranges::views::split(' ')) {
      g[src].emplace(std::string(dst.data(), dst.size()));
    }
  }

  const std::string kSource  = "you", kSink = "out";
  decltype(g) ig;
  {
    std::set<std::string> vis;
    [&](this auto dfs, const std::string& v) -> void {
      assert(vis.emplace(v).second);
      vis.emplace(v);
      for (const auto& u : g[v]) {
        if (!vis.contains(u)) {
          dfs(u);
        }
      }
    }(kSource);
    decltype(g) newG;
    for (const auto& [v, us] : g) {
      if (!vis.contains(v)) {
        continue;
      }
      for (const auto& u : us) {
        if (vis.contains(u)) {
          newG[v].emplace(u);
          ig[u].emplace(v);
        }
      }
    }
    std::swap(g, newG);
  }
  std::map<std::string, int> deg;
  for (const auto& [x, y] : ig) {
    deg[x] = y.size();
  }
  std::map<std::string, int> dp;
  dp[kSource] = 1;
  deg[kSource] = 0;
  [&](this auto dfs, const std::string& v) -> void {
    assert(deg[v] == 0);
    for (const auto& u : g[v]) {
      dp[u] += dp[v];
      --deg[u];
      if (deg[u] == 0) {
        dfs(u);
      }
    }
  }(kSource);
  Println(dp[kSink]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
