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
  }
  std::vector<int> lt(n), gt(n);
  for (int i = 1; i < n; ++i) {
    lt[i] = lt[i - 1] + (ps[i - 1] < ps[i]);
    gt[i] = gt[i - 1] + (ps[i - 1] > ps[i]);
  }
  auto pf = [&](auto&& xs, int l, int r) {
    assert(0 <= l && l <= r && r < n);
    return xs[r] - (l > 0 ? xs[l - 1] : 0);
  };
  int64_t tot = 0;
  for (int i = 0; i + 3 < n; ++i) {
    if (ps[i] > ps[i + 1]) {
      continue;
    }
    // inc till `x`
    int x;
    {
      auto lo = i + 1, hi = n;
      while (hi - lo > 1) {
        const auto mid = std::midpoint(lo, hi);
        (pf(lt, i + 1, mid) == (mid - i) ? lo : hi) = mid;
      }
      x = lo;
    }
    if (x + 1 >= n) {
      continue;
    }
    assert(ps[x] > ps[x + 1]);
    int y;
    {
      auto lo = x + 1, hi = n;
      while (hi - lo > 1) {
        const auto mid = std::midpoint(lo, hi);
        (pf(gt, x + 1, mid) == (mid - x) ? lo : hi) = mid;
      }
      y = lo;
    }

    if (y + 1 >= n) {
      continue;
    }
    auto lo = y + 1, hi = n;
    while (hi - lo > 1) {
      const auto mid = std::midpoint(lo, hi);
      (pf(lt, y, mid) == (mid - y) ? lo : hi) = mid;
    }
    dbg(i,x,y,lo);
    tot += lo - y;
  }
  Println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
