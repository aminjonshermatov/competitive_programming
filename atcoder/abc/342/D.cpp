#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

// Linear Sieve
decltype(auto) sieve(int n) {
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

using i64 = int64_t;

void solve() {
  const auto [ps, spf] = sieve(200010);
  int n;
  std::cin >> n;
  i64 zeros = 0;
  std::vector<std::vector<int>> as;
  for (int i = 0; i < n; ++i) {
    i64 x;
    std::cin >> x;
    if (x == 0) {
      ++zeros;
    } else {
      std::map<i64, int> cnt{};
      while (x > 1) {
        cnt[spf[x]] ^= 1;
        x /= spf[x];
      }
      std::vector<int> tmp;
      for (auto [a, b] : cnt) {
        if (b == 1) {
          tmp.emplace_back(a);
        }
      }
      if (tmp.empty()) {
        tmp.emplace_back(1);
      }
      as.emplace_back(tmp);
    }
  }
  i64 tot = zeros * (n - zeros) + zeros * (zeros - 1) / 2;
  std::map<std::vector<int>, int> cnt{};
  for (auto& a : as) {
    tot += cnt[a];
    ++cnt[a];
  }
  std::cout << tot << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}