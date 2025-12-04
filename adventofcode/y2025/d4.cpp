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
  auto ret = 0;
  for (;;) {
    auto ng = g;
    auto inter = 0;
    for (int i = 0; i < g.size(); ++i) {
      for (int j = 0; j < g[i].size(); ++j) {
        if (g[i][j] != '@') {
          continue;
        }
        auto loc = 0;
        for (auto di = -1; di <= 1; ++di) {
          for (auto dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) {
              continue;
            }
            const auto ni = i + di;
            const auto nj = j + dj;
            if (std::clamp<int>(ni, 0, g.size() - 1) == ni && std::clamp<int>(nj, 0, g[i].size() - 1) == nj) {
              loc += g[ni][nj] == '@';
            }
          }
        }
        if (loc < 4) {
          ++inter;
          ng[i][j] = '.';
        }
      }
    }
    if (inter == 0) {
      break;
    }
    ret += inter;
    std::swap(g, ng);
  }

  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
