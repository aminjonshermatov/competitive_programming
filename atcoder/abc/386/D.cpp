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
  int n, m;
  Scan(n, m);
  std::vector<int> xs(m), ys(m);
  std::string cs(m, '#');
  for (int i = 0; i < m; ++i) {
    Scan(xs[i], ys[i], cs[i]);
  }
  // bbb..bww...ww
  std::map<int, int> ls, rs;
  std::set<int> common;
  for (int i = 0; i < m; ++i) {
    if (cs[i] == 'B') {
      if (ls.contains(xs[i])) {
        ls[xs[i]] = std::max(ls[xs[i]], ys[i]);
      } else {
        ls[xs[i]] = ys[i];
      }
    } else {
      if (rs.contains(xs[i])) {
        rs[xs[i]] = std::min(rs[xs[i]], ys[i]);
      } else {
        rs[xs[i]] = ys[i];
      }
    }
    common.emplace(xs[i]);
  }
  auto prv = n;
  bool ok = true;
  for (auto x : common) {
    const auto fL = ls.contains(x);
    const auto fR = rs.contains(x);
    if (fL && fR) {
      ok &= ls[x] <= prv;
      ok &= ls[x] < rs[x];
      prv = std::min(prv, rs[x] - 1);
    } else if (fL) {
      ok &= ls[x] <= prv;
    } else if (fR) {
      prv = std::min(prv, rs[x] - 1);
    }
  }
  Println(ok ? "Yes" : "No");
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
