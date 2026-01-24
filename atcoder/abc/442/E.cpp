#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

struct Point final {
  int64_t X = 0, Y = 0;
};

auto Cross(const Point& a, const Point& b) {
  return a.X * b.Y - a.Y * b.X;
}
auto Cmp(const Point& a, const Point& b) {
  const int ah = a.Y < 0 || (a.Y == 0 && a.X < 0);
  const int bh = b.Y < 0 || (b.Y == 0 && b.X < 0);
  if (ah != bh) {
    return ah < bh;
  }
  return Cross(a, b) > 0;
}

void Solve() {
  int n, q;
  Scan(n, q);
  std::vector<Point> pts(n);
  for (auto& [x, y] : pts) {
    Scan(x, y);
  }

  std::vector<int> ord(n);
  std::ranges::iota(ord, 0);
  std::ranges::sort(ord, [&](const int i, const int j) {
    return Cmp(pts[i], pts[j]);
  });
  std::ranges::reverse(ord);
  std::vector pos(n, 0);
  for (int i = 0; i < n; ++i) {
    pos[ord[i]] = i;
  }

  dbg(ord);
  dbg(pos);

  std::vector lft(n, 0), rgt(n, n);
  for (int i = 1; i < n; ++i) {
    lft[i] = Cmp(pts[ord[i]], pts[ord[i - 1]]) ? i : lft[i - 1];
  }
  for (int i = n - 2; i >= 0; --i) {
    rgt[i] = Cmp(pts[ord[i + 1]], pts[ord[i]]) ? (i + 1) : rgt[i + 1];
  }
  dbg(lft);
  dbg(rgt);

  for (int i = 0; i < q; ++i) {
    int a, b;
    Scan(a, b);
    --a, --b;
    const auto x = lft[pos[a]];
    const auto y = rgt[pos[b]];
    dbg(a,b,pos[a],pos[b],x,y);
    if (x < y) {
      Println(y - x);
    } else {
      Println(n - (x - y));
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
