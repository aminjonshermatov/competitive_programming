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
  int q;
  Scan(q);

  for (auto isP = 0, vol = 0; q-- > 0;) {
    char a;
    Scan(a);

    if (a == '1') {
      ++vol;
    } else if (a == '2') {
      vol = std::max(vol - 1, 0);
    } else {
      assert(a == '3');
      isP ^= 1;
    }
    Println(isP && vol >= 3 ? "Yes" : "No");
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
