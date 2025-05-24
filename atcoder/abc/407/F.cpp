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
  std::vector<int64_t> as(n);
  for (int i = 0; i < n; ++i) {
    Scan(as[i]);
  }

  std::set<int> seen;
  seen.emplace(-1);
  seen.emplace(n);
  std::vector<int> ord(n);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return as[i] > as[j];
  });
  std::vector<int> ls(n), rs(n);
  for (auto id : ord) {
    auto lo = seen.lower_bound(id);
    assert(lo != seen.begin());
    lo = std::prev(lo);
    auto up = seen.upper_bound(id);
    assert(up != seen.end());
    ls[id] = *lo + 1;
    rs[id] = *up - 1;
    assert(ls[id] <= id && id <= rs[id]);
    seen.emplace(id);
  }
  dbg(ls);
  dbg(rs);

  std::vector<int64_t> ret(n + 1);
  for (int i = 0; i < n; ++i) {
    const auto x = i - ls[i];
    const auto y = rs[i] - i;
    // why not n^2
    if (x < y) {
      for (int a = 0; a <= x; ++a) {
        ret[a] += as[i];
        ret[y + a + 1] -= as[i];
      }
    } else {
      for (int b = 0; b <= y; ++b) {
        ret[b] += as[i];
        ret[b + x + 1] -= as[i];
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    if (i > 0) {
      ret[i] += ret[i - 1];
    }
    Print(ret[i]);
  }
  Println();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  Solve();
}
