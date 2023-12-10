#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
using i64 = int64_t;

struct Line {
  mutable i64 k, m, p;
  bool operator<(const Line& o) const { return k < o.k; } // minimum, (`<` if maximum)
  bool operator<(i64 x) const { return p < x; }
};

struct LineContainer : std::multiset<Line, std::less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static constexpr auto  inf = std::numeric_limits<i64>::max();
  static i64 div(i64 a, i64 b) { /* floored division */ return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(i64 k, i64 m) { // y=kx+m
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  i64 query(i64 x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

void solve() {
  int n, x;
  std::cin >> n >> x;
  std::vector<i64> ss(n + 1), fs(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> ss[i];
  }
  fs[0] = x;
  for (int i = 1; i <= n; ++i) {
    std::cin >> fs[i];

  }

  LineContainer lc;
  lc.add(-fs[0], 0);
  i64 ans;
  for (int i = 1; i <= n; ++i) {
    auto dpj = lc.query(ss[i]);
    lc.add(-fs[i], dpj);
    if (i == n) {
      ans = -dpj;
    }
    /*for (int j = 0; j < i; ++j) {
      dp[i] = std::min(dp[i], dp[j] + ss[i] * fs[j]);
    }*/
  }
  std::cout << ans << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}