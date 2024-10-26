#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&& ... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

using i64 = int64_t;

void solve() {
  int n;
  i64 k;
  scan(n, k);
  std::vector<int> ps(n);
  for (int i = 0; i < n; ++i) {
    scan(ps[i]);
    --ps[i];
  }

  std::vector<int> id(n, -1), offset(n, 0);
  std::vector<std::vector<int>> cs;
  for (int i = 0; i < n; ++i) {
    if (id[i] != -1) {
      continue;
    }
    const auto cId = static_cast<int>(cs.size());
    cs.emplace_back();
    auto j = i;
    while (id[j] == -1) {
      id[j] = cId;
      offset[j] = static_cast<int>(cs.back().size());
      cs.back().emplace_back(ps[j]);
      j = ps[j];
    }
  }
  dbg(id);
  dbg(offset);
  dbg(cs);
  std::vector<int> ret(n);
  for (int i = 0; i < n; ++i) {
    const int mod = cs[id[i]].size();
    int res = 1, cur = 2;
    for (auto x = k; x > 0; x >>= 1) {
      if (x & 1) {
        res = ((res * 1LL * cur) % mod + mod) % mod;
      }
      cur = ((cur * 1LL * cur) % mod + mod) % mod;
    }
    res = (res + mod - 1) % mod;
    ret[i] = cs[id[i]][(offset[i] + res) % cs[id[i]].size()];
  }
  for (int i = 0; i < n; ++i) {
    print(ret[i] + 1);
  }
  println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}