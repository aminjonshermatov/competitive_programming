#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("tree-vectorize")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int_fast64_t;
using i32 = int_fast32_t;

constexpr auto inf = std::numeric_limits<i64>::max() / 2;
constexpr i32 N = 3002;
static i64 cs[N], pf[N], sf[N], pfComplex[N], sfComplex[N], cost[N * N], dp[2][N];
static i32 nodes[N * 4], nxt, n;

inline i64 eval(i32 L, i32 x) { return L == -1 ? inf : cost[L * N + x] + dp[nxt ^ 1][L - 1]; }
inline void add(i32 L) {
  i32 id = 0, lb = 0, rb = n;
  for (;;) {
    auto mid = lb + (rb - lb) / 2;

    // f(x) = cost[L][x] + dp[nxt ^ 1][L - 1], for some `L`
    auto fLeft = eval(L, lb) < eval(nodes[id], lb);
    auto fMid = eval(L, mid) < eval(nodes[id], mid);

    if (fMid) {
      std::swap(L, nodes[id]);
    }
    if (rb - lb == 1) {
      return;
    }
    id = id * 2 + 1 + (fLeft == fMid);
    (fLeft != fMid ? rb : lb) = mid;
  }
}
inline i64 qry(i32 x) {
  i32 id = 0, lb = 0, rb = n;
  auto ret = inf;
  for (;;) {
    ret = std::min(ret, eval(nodes[id], x));
    if (rb - lb == 1) {
      return ret;
    }
    auto mid = lb + (rb - lb) / 2;
    id = id * 2 + 1 + (x >= mid);
    (x < mid ? rb : lb) = mid;
  }
}
inline i64 C(i32 l, i32 m, i32 r) {
  return pfComplex[m] - pfComplex[l - 1] - pf[l - 1] * (m - l + 1) + sfComplex[m] - sfComplex[r + 1] - sf[r + 1] * (r - m + 1);
}

void solve() {
  i32 k;
  std::cin >> n >> k;
  for (i32 i = 1; i <= n; ++i) {
    std::cin >> cs[i];
  }

  pf[0] = pfComplex[0] = 0;
  for (i32 i = 1; i <= n; ++i) {
    pfComplex[i] = pfComplex[i - 1] + pf[i - 1];
    pf[i] = pf[i - 1] + cs[i];
  }
  sf[n + 1] = sfComplex[n + 1] = 0;
  for (i32 i = n; i >= 1; --i) {
    sfComplex[i] = sfComplex[i + 1] + sf[i + 1];
    sf[i] = sf[i + 1] + cs[i];
  }

  for (i32 l = 1; l <= n; ++l) {
    i32 best_mid = l;
    for (i32 r = l; r <= n; ++r) {
      while (best_mid < r && C(l, best_mid, r) > C(l, best_mid + 1, r)) {
        ++best_mid;
      }
      cost[l * N + r] = C(l, best_mid, r);
    }
  }

  nxt = 1;
  std::fill(dp[nxt ^ 1], dp[nxt ^ 1] + n + 1, inf);
  dp[nxt ^ 1][0] = 0;
  for (i32 _ = 1; _ <= k; ++_, nxt ^= 1) {
    std::memset(nodes, -1, sizeof nodes);
    for (i32 r = _; r <= n; ++r) {
      add(r);
      dp[nxt][r] = qry(r);
    }
  }
  std::cout << dp[nxt ^ 1][n] << '\n';
}

int32_t main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

#ifdef LOCAL
  auto s = std::chrono::high_resolution_clock::now();
#endif
  solve();
#ifdef LOCAL
  std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - s).count() << '\n';
#endif
}