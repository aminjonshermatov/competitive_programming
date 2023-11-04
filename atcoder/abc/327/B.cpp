#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

void solve() {
  i64 n;
  std::cin >> n;

  auto pw = [&](__int128 a, i64 b) -> __int128 {
    __int128 res = 1;
    for (; b > 0; b >>= 1, a *= a) {
      if (b & 1) res *= a;
    }
    return res;
  };

  i64 x = 1;
  while (pw(x, x) < n) ++x;
  dbg(x);
  if (pw(x, x) != n) {
    std::cout << "-1\n";
  } else {
    std::cout << x << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}