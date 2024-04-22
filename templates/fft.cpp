//
// Created by aminjon on 12/30/23.
//
#include <bits/stdc++.h>

std::size_t reverse(std::size_t num, std::size_t lg) noexcept {
  std::size_t res = 0;
  for (std::size_t i = 0; i < lg; i++) {
    if (num >> i & 1) {
      res |= 1 << (lg - 1 - i);
    }
  }
  return res;
}

using f80 = long double;
const f80 pi = std::acos(-1);

void fft(std::vector<std::complex<f80>>& vs, bool inverse = false) {
  const auto n = vs.size();
  const auto lg = std::__lg(n);

  for (std::size_t i = 0; i < n; i++) {
    if (auto rv = reverse(i, lg); i < rv) {
      swap(vs[i], vs[rv]);
    }
  }

  for (std::size_t len = 2; len <= n; len <<= 1) {
    const auto ang = pi * 2 / len * (inverse ? -1 : 1);
    std::complex<f80> wn(std::cos(ang), std::sin(ang));
    for (std::size_t i = 0; i < n; i += len) {
      std::complex<f80> w(1);
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
std::vector<T> multiple(const std::vector<T>& as, const std::vector<T>& bs) {
  std::size_t n = 1 << std::__lg(2 * as.size() - 1);
  std::vector<std::complex<f80>> x(n), y(n);

  std::copy(as.begin(), as.end(), x.begin());
  std::copy(bs.begin(), bs.end(), y.begin());
  fft(x), fft(y);
  for (std::size_t i = 0; i < n; ++i) {
    x[i] *= y[i];
  }
  fft(x, true);
  std::vector<T> ret;
  ret.reserve(x.size());
  std::transform(x.begin(), x.end(), std::back_inserter(ret),
                 [](auto&& complex) { return std::round(complex.real()); });
  return ret;
}

// A[0...(n-1)], B[0...(m-1)], n >= m
// returns C[0...(n-m)], where C[i] = sum_j B[j]*A[i+j]
// i.e. dot-product array on window of size m, with shifts
template <std::integral T>
std::vector<T> correlation(const std::vector<T>& as, const std::vector<T>& bs) {
  assert(as.size() >= bs.size() && !as.empty());
  std::size_t n = 1 << std::__lg(2 * as.size() - 1);
  std::vector<std::complex<f80>> x(n), y(n);

  std::copy(as.begin(), as.end(), x.begin());
  std::copy(bs.rbegin(), bs.rend(), y.begin());
  fft(x), fft(y);
  for (std::size_t i = 0; i < n; ++i) {
    x[i] *= y[i];
  }
  fft(x, true);
  x.resize(as.size());
  x.erase(x.begin(), x.begin() + bs.size() - 1);
  std::vector<T> ret;
  ret.reserve(x.size());
  std::transform(x.begin(), x.end(), std::back_inserter(ret),
                 [](auto&& complex) { return std::round(complex.real()); });
  return ret;
}