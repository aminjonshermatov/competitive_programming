#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

std::vector<int64_t> xs;

void Solve() {
  int64_t n;
  Scan(n);

  assert(xs.front() * xs.front() <= n);
  std::size_t lo = 0, hi = xs.size();
  while (hi - lo > 1) {
    const auto mid = std::midpoint(lo, hi);
    (xs[mid] * xs[mid] <= n ? lo : hi) = mid;
  }
  Println(xs[lo] * xs[lo]);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  constexpr int64_t kLimit = 1E6;
  std::array<int, kLimit + 1> spf{};
  spf.fill(-1);
  for (auto i = 2; i <= kLimit; ++i) {
    if (spf[i] != -1) {
      continue;
    }
    for (auto j = i; j <= kLimit; j += i) {
      if (spf[j] == -1) {
        spf[j] = i;
      }
    }
  }

  for (auto x = 6; x <= kLimit; ++x) {
    auto tmp = x;
    auto p1 = spf[tmp];
    while (tmp != 1 && tmp % p1 == 0) {
      tmp /= p1;
    }
    if (tmp == 1) {
      continue;
    }
    auto p2 = spf[tmp];
    while (tmp != 1 && tmp % p2 == 0) {
      tmp /= p2;
    }
    if (tmp == 1) {
      xs.emplace_back(x);
    }
  }

  int t;
  Scan(t);
  while (t-- > 0) {
    Solve();
  }
}
