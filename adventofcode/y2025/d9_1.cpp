#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

struct Point final {
  int64_t X = 0, Y = 0;
};

void Solve() {
  constexpr int kN = 496;
  std::array<Point, kN> pts;
  for (char _; auto& [x, y] : pts) {
    Scan(x, _, y);
    dbg(x,y);
  }

  int64_t ret = 0;
  for (int i = 0; i < kN; ++i) {
    for (int j = i + 1; j < kN; ++j) {
      ret = std::max(ret, (std::abs(pts[i].X - pts[j].X) + 1) * (std::abs(pts[i].Y - pts[j].Y) + 1));
    }
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
