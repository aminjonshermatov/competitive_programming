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
  std::vector<std::string> g;
  for (std::string s; ; s.clear()) {
    std::getline(std::cin, s);
    if (s.empty()) {
      break;
    }
    g.emplace_back(s);
  }
  const auto n = int(g.size());
  const int m = std::ranges::max(g, {}, &std::string::size).size();
  for (auto& s : g) {
    assert(s.size() == m);
  }

  auto sI = -1, sJ = -1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == 'S') {
        sI = i, sJ = j;
      }
    }
  }
  std::vector dp(m, 0LL);
  dp[sJ] = 1;
  for (int i = sI + 1; i < n; ++i) {
    std::vector ndp(m, 0LL);
    for (int j = 0; j < m; ++j) {
      if (g[i - 1][j] == '.' || g[i - 1][j] == 'S') {
        ndp[j] += dp[j];
        if (j > 0 && g[i][j - 1] == '^') {
          ndp[j] += dp[j - 1];
        }
        if (j + 1 < m && g[i][j + 1] == '^') {
          ndp[j] += dp[j + 1];
        }
      }
    }
    assert(std::ranges::all_of(ndp, [](const auto x) { return x >= 0; }));
    std::swap(dp, ndp);
  }
  Println(std::ranges::fold_left(dp, 0LL, std::plus{}));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
