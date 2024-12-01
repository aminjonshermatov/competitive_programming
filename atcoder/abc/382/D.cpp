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

  std::vector<std::vector<int>> all;
  std::vector<int> cur;
  auto rec = [&](auto&& self, int pos, int x) -> bool {
    if (pos >= n) {
      all.emplace_back(cur);
      return true;
    }
    if (x > m) {
      return false;
    }
    auto f = false;
    for (int z = x; z <= m; ++z) {
      cur.emplace_back(z);
      if (!self(self, pos + 1, z + 10)) {
        cur.pop_back();
        break;
      }
      f = true;
      cur.pop_back();
    }
    return f;
  };
  rec(rec, 0, 1);
  Println(all.size());
  for (auto& as : all) {
    for (auto a : as) {
      Print(a);
    }
    Println();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
