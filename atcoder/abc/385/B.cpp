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
  int n, m, i, j;
  Scan(n, m, i, j);
  --i, --j;
  std::vector<std::string> g(n);
  for (auto& r : g) {
    Scan(r);
  }
  auto ok = [n, m](int a, int b) {
    return std::clamp(a, 0, n - 1) == a && std::clamp(b, 0, m - 1) == b;
  };
  std::string t;
  Scan(t);
  std::set<std::pair<int, int>> uniq;
  if (g[i][j] == '@') {
    uniq.emplace(i, j);
  }
  for (auto c : t) {
    auto nxt = [&] {
      auto ni = i, nj = j;
      switch (c) {
        case 'U':
          --ni;
          break;
        case 'D':
          ++ni;
          break;
        case 'L':
          --nj;
          break;
        case 'R':
          ++nj;
          break;
        default:
          assert(false);
      }
      return std::pair(ni, nj);
    };
    const auto [ni, nj] = nxt();
    if (ok(ni, nj) && g[ni][nj] != '#') {
      if (g[ni][nj] == '@') {
        uniq.emplace(ni, nj);
      }
      i = ni;
      j = nj;
    }
  }
  Println(i + 1, j + 1, uniq.size());
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
