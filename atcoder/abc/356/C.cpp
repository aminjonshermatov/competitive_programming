#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void solve() {
  int n, m, k;
  scan(n, m, k);
  std::vector<int> ks(m, 0);
  std::vector<bool> res(m);
  for (int i = 0; i < m; ++i) {
    int sz;
    scan(sz);
    for (int j = 0; j < sz; ++j) {
      int x;
      scan(x);
      --x;
      ks[i] |= 1 << x;
    }
    char f;
    scan(f);
    res[i] = f == 'o';
  }
  int ret{};
  for (int a = 0; a < (1 << n); ++a) {
    int cur = 0;
    for (auto tmp = a; tmp > 0;) {
      const int i = std::__lg(tmp);
      cur |= 1 << i;
      tmp ^= 1 << i;
    }
    bool ok = true;
    for (int i = 0; i < m; ++i) {
      if (res[i]) {
        ok &= __builtin_popcount(cur & ks[i]) >= k;
      } else {
        ok &= __builtin_popcount(cur & ks[i]) < k;
      }
    }
    ret += ok;
  }
  println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}