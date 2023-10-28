//
// Created by aminjon on 1/1/23.
//
#include <bits/stdc++.h>

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