#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::string s, t;
  std::cin >> s >> t;

  std::vector cache(n, std::vector<std::array<int, 2>>(m, {-1, -1}));
  auto dp = [&](auto &f, int id, int last, int need_cover) -> bool {
    if (id >= n) return last == 0 && need_cover == 0;
    if (cache[id][last][need_cover] != -1) return cache[id][last][need_cover];

    bool loc = 0;
    if (s[id] == t[last]) {
      loc |= f(f, id + 1, (last + 1) % m, need_cover);
      if (s[id] == t[0]) {
        loc |= f(f, id + 1, 1 % m, 0);
      }
    } else {
      if (n - id < m) return false;
      int j = 0;
      while (j < m && s[id] != t[j]) ++j;
      if (j < m && s[id] == t[j]) {
        if (j == 0) {
          loc |= f(f, id + 1, 1 % m, 0);
        } else if (last == 0) {
          loc |= f(f, id + 1, (j + 1) % m, 1);
        }
      }
    }
    return cache[id][last][need_cover] = loc;
  };
  std::cout << (dp(dp, 0, 0, 0) ? "Yes" : "No") << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}