#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

static constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
static constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
static constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

static void Solve() {
  int n;
  Scan(n);
  std::vector as(n, 0), bs(n, 0);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  for (int i = 0; i < n; ++i) {
    Scan(bs[i]);
  }
  for (; !as.empty() && as.back() == bs.back(); as.pop_back(), bs.pop_back()) {}
  if (as.empty()) {
    Println("Yes");
    return;
  }
  std::ranges::reverse(as);
  std::ranges::reverse(bs);
  for (; !as.empty() && as.back() == bs.back(); as.pop_back(), bs.pop_back()) {}
  {
    auto cs = as;
    cs.insert(cs.begin(), cs.back());
    cs.pop_back();
    if (cs == bs) {
      Println("Yes");
      return;
    }
  }
  std::ranges::reverse(as);
  std::ranges::reverse(bs);
  {
    auto cs = as;
    cs.insert(cs.begin(), cs.back());
    cs.pop_back();
    if (cs == bs) {
      Println("Yes");
      return;
    }
  }
  Println("No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
