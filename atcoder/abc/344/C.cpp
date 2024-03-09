#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  using i64 = int64_t;
  int n;
  std::cin >> n;
  std::vector<i64> as(n);
  for (auto& a : as) {
    std::cin >> a;
  }
  int m;
  std::cin >> m;
  std::vector<i64> bs(m);
  for (auto& b : bs) {
    std::cin >> b;
  }
  int l;
  std::cin >> l;
  std::vector<i64> cs(l);
  for (auto& c : cs) {
    std::cin >> c;
  }
  std::set<i64> xs;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int k = 0; k < l; ++k) {
        xs.emplace(as[i] + bs[j] + cs[k]);
      }
    }
  }
  int q;
  std::cin >> q;
  while (q-- > 0) {
    i64 x;
    std::cin >> x;
    std::cout << (xs.contains(x) ? "Yes" : "No") << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}