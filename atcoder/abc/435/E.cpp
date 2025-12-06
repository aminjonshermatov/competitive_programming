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
  int n, q;
  Scan(n, q);

  auto tot = 0;
  std::set<std::pair<int, int>> segs;
  while (q-- > 0) {
    int l, r;
    Scan(l, r);

    auto nl = l, nr = r;
    for (;;) {
      auto it = segs.lower_bound(std::pair(l, 0));
      if (it != segs.end() && it->first <= nr) {
        tot -= it->second - it->first + 1;
        nl = std::min(nl, it->first);
        nr = std::max(nr, it->second);
        segs.erase(it);
      } else if (it != segs.begin() && nl <= std::prev(it)->second) {
        it = std::prev(it);
        tot -= it->second - it->first + 1;
        nl = std::min(nl, it->first);
        nr = std::max(nr, it->second);
        segs.erase(it);
      } else {
        break;
      }
    }
    tot += nr - nl + 1;
    segs.emplace(nl, nr);
    dbg(nl,nr);
    dbg(segs);
    Print(n - tot);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
