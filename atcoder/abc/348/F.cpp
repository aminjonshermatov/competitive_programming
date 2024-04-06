#include <bits/stdc++.h>
#include <immintrin.h>

#pragma GCC target("avx512vl")
#pragma GCC target("avx512f")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("lzcnt")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("tree-vectorize")

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

constexpr int N = 2020;
static int __attribute__((aligned(64))) g[N * N];

void solve() {
  int n, m;
  std::cin >> n >> m;
  int mm = (16 - (m % 16)) % 16;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> g[i * (m + mm) + j];
    }
    for (int j = 0; j < mm; ++j) {
      g[i * (m + mm) + j + m] = 0;
    }
  }
  m += mm;

  int tot = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int cnt = 0;
      for (int k = 0; k + 15 < m; k += 16) {
        __m512i ii = _mm512_load_epi32(&g[i * m + k]);
        __m512i jj = _mm512_load_epi32(&g[j * m + k]);
        cnt += __builtin_popcount(_mm512_cmpeq_epi16_mask(ii, jj));
      }
      tot += (cnt - mm) & 1;
    }
  }
  std::cout << tot << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}