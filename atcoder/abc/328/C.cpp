#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, q;
  std::string s;
  std::cin >> n >> q >> s;

  std::vector<int> cand;
  for (int i = 0; i + 1 < n; ++i) {
    if (s[i] == s[i + 1]) {
      cand.emplace_back(i);
    }
  }

  while (q-- > 0) {
    int l, r;
    std::cin >> l >> r;
    --l, --r;
    std::cout << lower_bound(cand.begin(), cand.end(), r) - lower_bound(cand.begin(), cand.end(), l) << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}