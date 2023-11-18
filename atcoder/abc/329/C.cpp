#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  std::array<int, 27> mx{};
  int n;
  std::cin >> n;
  char prv = 'z' + 1;
  int cur = 0;
  for (int i = 0; i < n; ++i) {
    char c;
    std::cin >> c;
    if (prv != c) {
      mx[prv - 'a'] = std::max(mx[prv - 'a'], cur);
      cur = 0;
    }
    prv = c;
    mx[c - 'a'] = std::max(mx[c - 'a'], ++cur);
  }
  using i64 = int64_t;
  dbg(mx);
  i64 tot = 0;
  for (int i = 0; i < 26; ++i) {
    tot += mx[i];
  }
  std::cout << tot << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}