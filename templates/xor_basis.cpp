//
// Created by Aminjon Shermatov on 09.12.2023.
//
#include <bits/stdc++.h>

template <typename T, std::size_t B = sizeof(T) * __CHAR_BIT__>
struct XorBasis {
  std::array<T, B> basis{};
  int tried, added;
  XorBasis() : tried(0), added(0) { basis.fill(-1); }
  __attribute__((target("avx2"), optimize("O3", "unroll-loops"))) void add(T x) {
    ++tried;
    for (; x > 0;) {
      int ib;
      if constexpr (std::is_same<T, int32_t>()) {
        ib = sizeof(T) * __CHAR_BIT__  - 1 - __builtin_clz(x);
      } else if constexpr (std::is_same<T, int64_t>()) {
        ib = sizeof(T) * __CHAR_BIT__  - 1 - __builtin_clzll(x);
      } else {
        ib = std::log2(x);
      }
      if (basis[ib] == -1) {
        ++added;
        basis[ib] = x;
      }
      x ^= basis[ib];
    }
  }
  // returns count number of subsets that xor of elements equal to `x`, count = 2 ^ ret, or -1 if it doesn't exist
  __attribute__((target("avx2"), optimize("O3", "unroll-loops"))) [[nodiscard]] int subsetCount(T x) const {
    for (; x > 0;) {
      int ib;
      if constexpr (std::is_same<T, int32_t>()) {
        ib = sizeof(T) * __CHAR_BIT__  - 1 - __builtin_clz(x);
      } else if constexpr (std::is_same<T, int64_t>()) {
        ib = sizeof(T) * __CHAR_BIT__  - 1 - __builtin_clzll(x);
      } else {
        ib = std::log2(x);
      }
      if (basis[ib] == -1) break;
      x ^= basis[ib];
    }
    return x == 0 ? tried - added : -1;
  }
  // let F(S) = xor of all elements in S, return max value F(S'), where S' is all possible subsets of S
  __attribute__((target("avx2"), optimize("O3", "unroll-loops"))) [[nodiscard]] T maximumXor() const {
    T max = 0;
    for (int ib = B - 1; ib >= 0; --ib) {
      if (basis[ib] == -1 || max >> ib & 1) continue;
      max ^= basis[ib];
    }
    return max;
  }
};
