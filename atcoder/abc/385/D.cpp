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
  int64_t x, y;
  Scan(n, m, x, y);
  std::map<int64_t, std::set<int64_t>> byX, byY;
  for (int _ = 0; _ < n; ++_) {
    int64_t xx, yy;
    Scan(xx, yy);
    byX[xx].emplace(yy);
    byY[yy].emplace(xx);
  }
  auto ret = 0;
  if (byX[x].contains(y)) {
    byX[x].erase(y);
    byY[y].erase(x);
    ++ret;
  }
  for (int _ = 0; _ < m; ++_) {
    char d;
    int64_t c;
    Scan(d, c);
    auto nx = x, ny = y;
    switch (d) {
      case 'U':
        ny += c;
        break;
      case 'D':
        ny -= c;
        break;
      case 'L':
        nx -= c;
        break;
      case 'R':
        nx += c;
        break;
      default:
        assert(false);
    }
    if (x == nx) {
      if (y < ny) {
        for (; byX.contains(x) && !byX[x].empty();) {
          auto it = byX[x].lower_bound(y);
          if (it == byX[x].end() || *it > ny) {
            break;
          }
          ++ret;
          y = *it;
          assert(byX[x].contains(y));
          assert(byY[y].contains(x));
          byX[x].erase(y);
          byY[y].erase(x);
        }
      } else {
        for (; byX.contains(x) && !byX[x].empty();) {
          auto it = byX[x].upper_bound(y);
          if (it == byX[x].begin() || *std::prev(it) < ny) {
            break;
          }
          ++ret;
          y = *std::prev(it);
          assert(byX[x].contains(y));
          assert(byY[y].contains(x));
          byX[x].erase(y);
          byY[y].erase(x);
        }
      }
    } else {
      assert(y == ny);
      if (x < nx) {
        for (; byY.contains(y) && !byY[y].empty();) {
          auto it = byY[y].lower_bound(x);
          if (it == byY[y].end() || *it > nx) {
            break;
          }
          ++ret;
          x = *it;
          assert(byX[x].contains(y));
          assert(byY[y].contains(x));
          byX[x].erase(y);
          byY[y].erase(x);
        }
      } else {
        for (; byY.contains(y) && !byY[y].empty();) {
          auto it = byY[y].upper_bound(x);
          if (it == byY[y].begin() || *std::prev(it) < nx) {
            break;
          }
          ++ret;
          x = *std::prev(it);
          assert(byX[x].contains(y));
          assert(byY[y].contains(x));
          byX[x].erase(y);
          byY[y].erase(x);
        }
      }
    }
    x = nx;
    y = ny;
  }
  Println(x, y, ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
