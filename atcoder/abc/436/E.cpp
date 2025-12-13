#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

void Solve() {
  int n;
  Scan(n);
  std::vector<int> ps(n);
  for (int i = 0; i < n; ++i) {
    Scan(ps[i]);
    --ps[i];
  }

  std::vector vis(n, false);
  auto ret = 0LL;
  for (int i = 0; i < n; ++i) {
    if (vis[i]) {
      continue;
    }
    auto loc = -1;
    auto cur = i;
    do {
      vis[cur] = true;
      ++loc;
      cur = ps[cur];
    } while (!vis[cur]);
    dbg(i,loc+1);
    ret += loc * 1LL * (loc + 1) / 2;
  }
  Println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
