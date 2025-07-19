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
  int64_t n;
  int m;
  Scan(n, m);
  std::vector<std::pair<int64_t, int64_t>> es(m);
  for (auto& [a, b] : es) {
    Scan(a, b);
  }
  std::ranges::sort(es, [](auto& l, auto& r) {
    return l.second - l.first > r.second - r.first;
  });
  auto tot = int64_t{};
  for (auto [a, b] : es) {
    if (n < a) {
      continue;
    }
    const auto cnt = (n - a) / (a - b) + 1;
    dbg(a,b,cnt);
    tot += cnt;
    n += (b - a) * cnt;
  }
  Println(tot);
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
