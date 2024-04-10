//
// Created by aminjon on 4/10/24.
//
#include <bits/stdc++.h>

// https://noshi91.github.io/Library/algorithm/concave_max_plus_convolution.cpp.html
// https://codeforces.com/blog/entry/98663

inline decltype(auto) monotone_maxima(int h, int w, auto&& f) {
  using T = decltype(f(0, 0));
  std::vector<T> ret(h);
  auto dnq = [&](auto&& self, int l, int r, int opt_l, int opt_r) -> void {
    const auto mid = l + (r - l) / 2;
    auto best_col = opt_l;
    auto best_val = -std::numeric_limits<T>::max() / 2; // maximization
    for (int col = opt_l; col < opt_r; ++col) {
      if (const std::integral auto val = f(mid, col); val > best_val) { // maximization
        best_col = col;
        best_val = val;
      }
    }
    ret[mid] = best_val;
    if (l < mid) {
      self(self, l, mid, opt_l, best_col + 1);
    }
    if (mid + 1 < r) {
      self(self, mid + 1, r, best_col, opt_r);
    }
  };
  dnq(dnq, 0, h, 0, w);
  return ret;
}

template <std::integral T> inline decltype(auto) concave_max_plus_convolution(const std::vector<T>& a, const std::vector<T>& b) {
  const auto na = int(a.size());
  const auto nb = int(b.size());
  return monotone_maxima(na + nb - 1, na, [&](int i, int j) -> T {
    if (i < j || i - j >= nb) {
      return -std::numeric_limits<T>::max() / 2; // maximization
    }
    return a[j] + b[i - j];
  });
}