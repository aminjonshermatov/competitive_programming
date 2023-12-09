//
// Created by aminjon on 3/10/23.
//
#include <bits/stdc++.h>

/*
dp[i] = min(dp[j] + (h[j] - h[i])^2 - w[i])
dp[i] = min(dp[j] + h^2[j] - 2h[i]h[j]) + h^2[i] - w[i]

note: dp[j] + h^2[j] - 2h[i]h[j]
y(i) = ...(j)
y = kx + m, where k = -2h[j], x = h[i], m = dp[j] + h^2[j]
*/
// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
using i64 = int64_t;

struct Line {
  mutable i64 k, m, p;
  bool operator<(const Line& o) const { return k > o.k; } // minimum, (`<` if maximum)
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
