//
// Created by aminjon on 12/30/23.
//
#include <bits/stdc++.h>

auto Reverse(const std::size_t num, const std::size_t lg) noexcept {
  std::size_t res = 0UZ;
  for (std::size_t i = 0; i < lg; i++) {
    if ((num >> i & 1) == 1) {
      res |= 1 << (lg - 1 - i);
    }
  }
  return res;
}

using F80 = long double;
const F80 pi = std::acos(-1.);

auto FFT(std::vector<std::complex<F80>>& vs, const bool inverse = false) {
  const auto n = vs.size();
  const auto lg = std::__lg(n);

  for (std::size_t i = 0; i < n; i++) {
    if (auto rv = Reverse(i, lg); i < rv) {
      swap(vs[i], vs[rv]);
    }
  }

  for (std::size_t len = 2; len <= n; len <<= 1) {
    const auto ang = pi * 2 / len * (inverse ? -1 : 1);
    std::complex<F80> wn(std::cos(ang), std::sin(ang));
    for (std::size_t i = 0; i < n; i += len) {
      std::complex<F80> w(1);
      for (std::size_t j = 0; j < len / 2; j++, w *= wn) {
        const auto u = vs[i + j], v = vs[i + j + len / 2] * w;
        vs[i + j] = u + v;
        vs[i + j + len / 2] = u - v;
      }
    }
  }
  if (inverse) {
    for (auto& x : vs) {
      x /= n;
    }
  }
}

template <std::integral T>
std::vector<T> Multiple(const std::vector<T>& as, const std::vector<T>& bs) {
  std::size_t n = 1UZ << std::__lg(2 * std::max(2UZ, as.size() + bs.size()) - 1);
  std::vector<std::complex<F80>> x(n), y(n);

  std::copy(as.begin(), as.end(), x.begin());
  std::copy(bs.begin(), bs.end(), y.begin());
  FFT(x), FFT(y);
  for (std::size_t i = 0; i < n; ++i) {
    x[i] *= y[i];
  }
  FFT(x, true);
  std::vector<T> ret;
  ret.reserve(x.size());
  std::transform(x.begin(), x.end(), std::back_inserter(ret), [](auto&& complex) { return std::round(complex.real()); });
  return ret;
}

// A[0...(n-1)], B[0...(m-1)], n >= m
// returns C[0...(n-m)], where C[i] = sum_j B[j]*A[i+j]
// i.e. dot-product array on window of size m, with shifts
template <std::integral T>
std::vector<T> Correlation(const std::vector<T>& as, const std::vector<T>& bs) {
  assert(as.size() >= bs.size() && !as.empty());
  std::size_t n = 1UZ << std::__lg(2 * std::max(2UZ, as.size() + bs.size()) - 1);
  std::vector<std::complex<F80>> x(n), y(n);

  std::copy(as.begin(), as.end(), x.begin());
  std::copy(bs.rbegin(), bs.rend(), y.begin());
  FFT(x), FFT(y);
  for (std::size_t i = 0; i < n; ++i) {
    x[i] *= y[i];
  }
  FFT(x, true);
  x.resize(as.size());
  x.erase(x.begin(), x.begin() + bs.size() - 1);
  std::vector<T> ret;
  ret.reserve(x.size());
  std::transform(x.begin(), x.end(), std::back_inserter(ret), [](auto&& complex) { return std::round(complex.real()); });
  return ret;
}