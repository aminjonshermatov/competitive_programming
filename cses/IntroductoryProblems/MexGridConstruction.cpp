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

  std::vector<std::set<int>> avj(n);
  std::ranges::generate(avj, [n] {
    std::set<int> xs;
    for (int i = 0; i < 2 * n + 1; ++i) {
      xs.emplace(i);
    }
    return xs;
  });

  for (int i = 0; i < n; ++i) {
    std::set<int> avi;
    for (int j = 0; j < 2 * n + 1; ++j) {
      avi.emplace(j);
    }
    for (int j = 0; j < n; ++j) {
      auto it = avi.begin();
      while (it != avi.end() && !avj[j].contains(*it)) {
        it = std::next(it);
      }
      assert(it != avi.end() && avj[j].contains(*it));
      Print(*it);
      avj[j].erase(*it);
      avi.erase(it);
    }
    Println();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
