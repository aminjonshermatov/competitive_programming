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
  std::map<int, std::vector<int>> ids;
  for (int i = 0; i < n; ++i) {
    int x;
    Scan(x);
    ids[x].emplace_back(i);
  }
  auto ret = 0;
  for (const auto& [_, is] : ids) {
    for (int len = 1; len <= is.back() - is.front() + 1; ++len) {
      std::set<int> vis;
      for (auto x : is) {
        if (vis.contains(x)) {
          continue;
        }
        auto loc = 1;
        vis.emplace(x);
        for (;;) {
          auto it = std::ranges::lower_bound(is, x + len);
          if (it == is.end() || *it != x + len) {
            break;
          }
          ++loc;
          vis.emplace(x + len);
          x += len;
        }
        ret = std::max(ret, loc);
      }
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
