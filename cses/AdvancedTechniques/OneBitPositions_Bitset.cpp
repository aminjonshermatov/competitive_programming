#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("tree-vectorize")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

constexpr int N = 2e5 + 1;
using Bs = std::bitset<N>;

void solve() {
  std::string s;
  std::cin >> s;

  const Bs x(s);
  auto tmp = x >> 1;
  std::vector<std::size_t> res(s.size());
  for (std::size_t shift = 1; shift < s.size(); ++shift, tmp >>= 1) {
    res[shift] = (x & tmp).count();
  }
  for (std::size_t i = 1; i < s.size(); ++i) {
    std::cout << res[i] << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}