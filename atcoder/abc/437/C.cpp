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
  std::vector<int64_t> ws(n), ps(n);
  for (int i = 0; i < n; ++i) {
    Scan(ws[i], ps[i]);
  }

  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return (ps[i] + ws[i]) < (ps[j] + ws[j]);
  });
  const auto allP = std::ranges::fold_left(ps, int64_t{0}, std::plus{});
  dbg(allP);
  auto pos = 0;
  auto cur = int64_t{0};
  while (pos < n && cur + ps[ord[pos]] + ws[ord[pos]] <= allP) {
    cur += ps[ord[pos]] + ws[ord[pos]];
    ++pos;
  }
  dbg(ord,pos);
  std::cout << std::min(n - 1, pos) << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}
