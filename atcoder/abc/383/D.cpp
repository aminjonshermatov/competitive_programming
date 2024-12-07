#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

// Linear Sieve
decltype(auto) Sieve(int n) {
  std::vector<int> spf(n + 1, 1), primes;
  for (int i = 2; i <= n; ++i) {
    if (spf[i] == 1) {
      spf[i] = i;
      primes.emplace_back(i);
    }
    for (auto p : primes) {
      if (i * p > n) {
        break;
      }
      spf[i * p] = p;
      if (p == spf[i]) {
        break;
      }
    }
  }
  return std::tuple(primes, spf);
}

void Solve() {
  int64_t n;
  Scan(n);

  int64_t lo = 0, hi = n;
  while (hi - lo > 1) {
    const auto mid = lo + (hi - lo) / 2;
    (__int128(mid) * mid >= n ? hi : lo) = mid;
  }
  assert(hi * hi >= n);
  dbg(hi);
  const auto [ps, spf] = Sieve(hi);
  dbg(ps.size());

  std::vector<int64_t> p2(ps.size(), -1), p8(ps.size(), -1);
  for (std::size_t i{0}; i < ps.size(); ++i) {
    if (__int128(ps[i]) * ps[i] > n) {
      continue;
    }
    p2[i] = int64_t(ps[i]) * ps[i];
    if (__int128(p2[i]) * p2[i] > n) {
      continue;
    }
    auto p4 = p2[i] * p2[i];
    if (__int128(p4) * p4 > n) {
      continue;
    }
    p8[i] = p4 * p4;
  }

  int64_t tot{0};
  { // 2 2
    for (std::size_t i{0}; i + 1 < p2.size() && p2[i] != -1 && p2[i + 1] != -1 && __int128(p2[i]) * p2[i + 1] <= n; ++i) {
      lo = i + 1, hi = p2.size();
      while (hi - lo > 1) {
        const auto mid = lo + (hi - lo) / 2;
        (p2[mid] != -1 && __int128(p2[i]) * p2[mid] <= n ? lo : hi) = mid;
      }
      tot += lo - i;
    }
  }
  { // 8
    for (std::size_t i{0}; i < p8.size() && p8[i] != -1; ++i) {
      ++tot;
    }
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
