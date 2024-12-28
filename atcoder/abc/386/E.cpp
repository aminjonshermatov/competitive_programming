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
  int n, k;
  Scan(n, k);
  std::vector<int64_t> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }
  std::ranges::sort(as);
  as.erase(std::ranges::unique(as).begin(), as.end());
  n = int(as.size());
  auto flip = false;
  const auto tot = std::accumulate(as.begin(), as.end(), int64_t{0}, [](auto acc, auto a) { return acc ^ a; });
  if (2 * k > n) {
    flip = true;
    k = n - k;
  }
  int64_t ret = 0;
  auto rec = [&](auto&& self, int pos, int len, int64_t val) -> void {
    if (len == k) {
      ret = std::max(ret, (flip ? tot : 0) ^ val);
      return;
    }
    if (pos >= n) {
      return;
    }
    for (int i = pos; i < n; ++i) {
      self(self, i + 1, len + 1, val ^ as[i]);
    }
  };
  rec(rec, 0, 0, 0);
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
