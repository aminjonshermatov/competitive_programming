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

  std::vector nxt(n, -1), prv(n, -1), head(n, 0), tail(n, 0);
  std::ranges::iota(head, 0);
  std::ranges::iota(tail, 0);
  for (int i = 0; i < q; ++i) {
    int c, p;
    Scan(c, p);
    --c, --p;

    auto tailC = tail[c];
    if (prv[c] != -1) {
      assert(nxt[prv[c]] == c);
      nxt[prv[c]] = -1;
      tail[c] = prv[c];
    } else {
      head[c] = tail[c] = -1;
    }
    nxt[p] = c;
    prv[c] = p;
    tail[p] = tailC;
  }
  for (int i = 0; i < n; ++i) {
    auto c = 0;
    for (auto x = head[i]; x != -1; x = nxt[x]) {
      ++c;
    }
    Print(c);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
