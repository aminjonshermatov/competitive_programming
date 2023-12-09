//
// Created by Aminjon Shermatov !Yandex on 09.12.2023.
//
#include <bits/stdc++.h>

template <typename T, std::size_t B = sizeof(T) * __CHAR_BIT__>
struct XorBasis {
  std::array<T, B> basis{};
  int tried, added;
  XorBasis() : tried(0), added(0) { basis.fill(-1); }
  void add(T x) {
    ++tried;
    for (; x > 0;) {
      int ib;
      if constexpr (std::is_same<T, int32_t>()) {
        ib = sizeof(T) * __CHAR_BIT__  - 1 - __builtin_clz(x);
      } else {
        ib = sizeof(T) * __CHAR_BIT__  - 1 - __builtin_clzll(x);
      }
      if (basis[ib] == -1) {
        ++added;
        basis[ib] = x;
      }
      x ^= basis[ib];
    }
  }
  // returns count number of subsets that xor of elements equal to `x`, count = 2 ^ ret, or -1 if it doesn't exist
  [[nodiscard]] int subsetCount(T x) const {
    for (; x > 0;) {
      int ib;
      if constexpr (std::is_same<T, int32_t>()) {
        ib = sizeof(T) * __CHAR_BIT__  - 1 - __builtin_clz(x);
      } else {
        ib = sizeof(T) * __CHAR_BIT__  - 1 - __builtin_clzll(x);
      }
      if (basis[ib] == -1) break;
      x ^= basis[ib];
    }
    return x == 0 ? tried - added : -1;
  }
  // let F(S) = xor of all elements in S, return max value F(S'), where S' is all possible subsets of S
  [[nodiscard]] T maximumXor() const {
    T max = 0;
    for (int ib = B - 1; ib >= 0; --ib) {
      if (basis[ib] == -1 || max >> ib & 1) continue;
      max ^= basis[ib];
    }
    return max;
  }
};
