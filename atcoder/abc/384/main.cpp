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
  std::vector<int64_t> as(n), bs(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  for (int i = 0; i < n; ++i) {
    Scan(bs[i]);
  }

  std::vector g(n, std::vector(n, int64_t{}));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cerr << std::llabs(as[i] - bs[j]) << ' ';
    }
    std::cerr << std::endl;
  }


}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
