#pragma GCC target("avx512vl")
#pragma GCC target("avx512f")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("lzcnt")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("tree-vectorize")
#include <bits/stdc++.h>
#include <immintrin.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

constexpr int N = 2e5 + 32;
static int __attribute__((aligned(64))) X1[N], Y1[N], X2[N], Y2[N], X3[N], Y3[N], X4[N], Y4[N];

void solve() {
  int n;
  scan(n);

  int ptr_1 = 0, ptr_2 = 0, ptr_3 = 0, ptr_4 = 0;
  for (int i = 0; i < n; ++i) {
    int x, y;
    scan(x, y);
    int mask = (x & 2) | (y & 1);
    if (mask == 0) {
      X1[ptr_1] = x;
      Y1[ptr_1++] = y;
    } else if (mask == 1) {
      X2[ptr_2] = x;
      Y2[ptr_2++] = y;
    } else if (mask == 2) {
      X3[ptr_3] = x;
      Y3[ptr_3++] = y;
    } else if (mask == 3) {
      X4[ptr_4] = x;
      Y4[ptr_4++] = y;
    } else {
      assert(false);
    }
  }
  int aux_1 = (16 - (ptr_1 % 16)) % 16;
  int aux_2 = (16 - (ptr_2 % 16)) % 16;
  int aux_3 = (16 - (ptr_3 % 16)) % 16;
  int aux_4 = (16 - (ptr_4 % 16)) % 16;
  for (int i = 0; i < aux_1; ++i) {
    X1[ptr_1 + i] = Y1[ptr_1 + i] = 0;
  }
  for (int i = 0; i < aux_2; ++i) {
    X2[ptr_2 + i] = Y2[ptr_2 + i] = 0;
  }
  for (int i = 0; i < aux_3; ++i) {
    X3[ptr_3 + i] = Y3[ptr_3 + i] = 0;
  }
  for (int i = 0; i < aux_4; ++i) {
    X4[ptr_4 + i] = Y4[ptr_4 + i] = 0;
  }
  int64_t tot = 0;
  for (int i = 0; i < ptr_1; ++i) {
    const auto xi = _mm512_set_epi32(X1[i], X1[i], X1[i], X1[i], X1[i], X1[i], X1[i], X1[i], X1[i], X1[i], X1[i], X1[i], X1[i], X1[i], X1[i], X1[i]);
    const auto yi = _mm512_set_epi32(Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i], Y1[i]);
    for (int j = 0; j + 15 < ptr_1 + aux_1; j += 16) {
      __m512i xj = _mm512_load_epi32(&X1[j]);
      __m512i yj = _mm512_load_epi32(&Y1[j]);
      tot += _mm512_reduce_add_epi32(_mm512_max_epi32(_mm512_abs_epi32(_mm512_sub_epi32(xi, xj)), _mm512_abs_epi32(_mm512_sub_epi32(yi, yj))));
    }
    tot -= (X1[i] + Y1[i]) * 1LL * aux_1;
  }
  for (int i = 0; i < ptr_2; ++i) {
    const auto xi = _mm512_set_epi32(X2[i], X2[i], X2[i], X2[i], X2[i], X2[i], X2[i], X2[i], X2[i], X2[i], X2[i], X2[i], X2[i], X2[i], X2[i], X2[i]);
    const auto yi = _mm512_set_epi32(Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i], Y2[i]);
    for (int j = 0; j + 15 < ptr_2 + aux_2; j += 16) {
      __m512i xj = _mm512_load_epi32(&X2[j]);
      __m512i yj = _mm512_load_epi32(&Y2[j]);
      tot += _mm512_reduce_add_epi32(_mm512_max_epi32(_mm512_abs_epi32(_mm512_sub_epi32(xi, xj)), _mm512_abs_epi32(_mm512_sub_epi32(yi, yj))));
    }
    tot -= (X2[i] + Y2[i]) * 1LL * aux_2;
  }
  for (int i = 0; i < ptr_3; ++i) {
    const auto xi = _mm512_set_epi32(X3[i], X3[i], X3[i], X3[i], X3[i], X3[i], X3[i], X3[i], X3[i], X3[i], X3[i], X3[i], X3[i], X3[i], X3[i], X3[i]);
    const auto yi = _mm512_set_epi32(Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i], Y3[i]);
    for (int j = 0; j + 15 < ptr_3 + aux_3; j += 16) {
      __m512i xj = _mm512_load_epi32(&X3[j]);
      __m512i yj = _mm512_load_epi32(&Y3[j]);
      tot += _mm512_reduce_add_epi32(_mm512_max_epi32(_mm512_abs_epi32(_mm512_sub_epi32(xi, xj)), _mm512_abs_epi32(_mm512_sub_epi32(yi, yj))));
    }
    tot -= (X3[i] + Y3[i]) * 1LL * aux_3;
  }
  for (int i = 0; i < ptr_4; ++i) {
    const auto xi = _mm512_set_epi32(X4[i], X4[i], X4[i], X4[i], X4[i], X4[i], X4[i], X4[i], X4[i], X4[i], X4[i], X4[i], X4[i], X4[i], X4[i], X4[i]);
    const auto yi = _mm512_set_epi32(Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i], Y4[i]);
    for (int j = 0; j + 15 < ptr_4 + aux_4; j += 16) {
      __m512i xj = _mm512_load_epi32(&X4[j]);
      __m512i yj = _mm512_load_epi32(&Y4[j]);
      tot += _mm512_reduce_add_epi32(_mm512_max_epi32(_mm512_abs_epi32(_mm512_sub_epi32(xi, xj)), _mm512_abs_epi32(_mm512_sub_epi32(yi, yj))));
    }
    tot -= (X4[i] + Y4[i]) * 1LL * aux_4;
  }
  println(tot / 2);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}