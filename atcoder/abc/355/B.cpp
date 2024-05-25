#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n, m;
  scan(n, m);
  std::vector<int> as(n), bs(m);
  for (auto&& a : as) {
    scan(a);
  }
  for (auto&& b : bs) {
    scan(b);
  }
  std::ranges::sort(as);
  std::ranges::sort(bs);
  std::vector<int> cs(n + m);
  std::ranges::merge(as, bs, cs.begin());
  for (int i = 0; i + 1 < n + m; ++i) {
    if (std::ranges::find(as, cs[i]) != as.end() && std::ranges::find(as, cs[i + 1]) != as.end()) {
      println("Yes");
      return;
    }
  }
  println("No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}