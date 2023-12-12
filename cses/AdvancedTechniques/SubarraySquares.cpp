#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using namespace std;
using i64 = int64_t;
using ll = i64;

// https://github.com/ShahjalalShohag/code-library/blob/main/Dynamic%20Programming%20Optimizations/Convex%20Hull%20Trick.cpp
struct CHT {
  vector<ll> m, b;
  int ptr = 0;

  bool bad(int l1, int l2, int l3) {
    return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query min),(slope inc+query max)
    return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  > 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query max), (slope inc+query min)
  }

  void add(ll _m, ll _b) {
    m.push_back(_m);
    b.push_back(_b);
    int s = m.size();
    while(s >= 3 && bad(s - 3, s - 2, s - 1)) {
      s--;
      m.erase(m.end() - 2);
      b.erase(b.end() - 2);
    }
  }

  ll f(int i, ll x) {
    return m[i] * x + b[i];
  }

  //(slope dec+query min), (slope inc+query max) -> x increasing
  //(slope dec+query max), (slope inc+query min) -> x decreasing
  ll query(ll x) {
    if(ptr >= m.size()) ptr = m.size() - 1;
    while(ptr < m.size() - 1 && f(ptr + 1, x) < f(ptr, x)) ptr++;
    return f(ptr, x);
  }

  ll bs(int l, int r, ll x) {
    int mid = (l + r) / 2;
    if(mid + 1 < m.size() && f(mid + 1, x) < f(mid, x)) return bs(mid + 1, r, x); // > for max
    if(mid - 1 >= 0 && f(mid - 1, x) < f(mid, x)) return bs(l, mid - 1, x); // > for max
    return f(mid, x);
  }
};

void solve() {
  int n, k;
  std::cin >> n >> k;
  std::vector<i64> as(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> as[i];
  }

  std::vector<i64> pf(n + 1);
  pf[0] = 0;
  for (int i = 1; i <= n; ++i) {
    pf[i] = pf[i - 1] + as[i];
  }

  constexpr i64 inf = 1e18;
  std::vector<i64> dp(n + 1, inf), ndp(n + 1);
  dp[0] = 0;
  for (int i = 1; i <= k; ++i) {
    std::fill(ndp.begin(), ndp.end(), inf);
    CHT lc;
    lc.add(0, 0);
    for (int r = 1; r <= n; ++r) {
      auto best_l = lc.query(pf[r]);
      ndp[r] = best_l + pf[r] * pf[r];
      lc.add(pf[r] * -2, dp[r] + pf[r] * pf[r]);
      /*for (int l = 1; l <= r; ++l) {
        // dp[l-1] + (pf[r] - pf[l-1])^2
        // dp[l-1] + (pf[l-1])^2 - 2*pf[r]*pf[l-1] + (pf[r])^2

        ndp[r] = std::min(ndp[r], dp[l - 1] + (pf[r] - pf[l - 1]) * (pf[r] - pf[l - 1]));
      }*/
    }
    dp.swap(ndp);
  }
  std::cout << dp.back() << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // auto s = std::chrono::high_resolution_clock::now();
  solve();
  // std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s).count() << '\n';
}