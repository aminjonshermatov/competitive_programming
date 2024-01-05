#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

std::size_t reverse(std::size_t num, std::size_t lg) {
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
decltype(auto) fft(std::vector<std::complex<f80>>& vs, bool invert = false) {
  const auto n = vs.size();
  const auto lg = 31 - __builtin_clz(n);

  for (std::size_t i = 0; i < n; i++) {
    if (auto rv = reverse(i, lg); i < rv) {
      swap(vs[i], vs[rv]);
    }
  }

  for (std::size_t len = 2; len <= n; len <<= 1) {
    const auto ang = pi * 2 / len * (invert ? -1 : 1);
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

  if (invert) {
    for (auto& x : vs) {
      x /= n;
    }
  }
}

template <std::integral T>
decltype(auto) multiple(const std::vector<T>& A, const std::vector<T>& B) {
  std::size_t n;
  for (n = 1; n < A.size() + B.size(); n *= 2) { }
  std::vector<std::complex<f80>> x(n), y(n);
  for (std::size_t i = 0; i < n; ++i) {
    x[i] = std::complex<f80>(i < A.size() ? A[i] : 0, 0);
    y[i] = std::complex<f80>(i < B.size() ? B[i] : 0, 0);
  }
  fft(x);
  fft(y);
  for (std::size_t i = 0; i < n; ++i) {
    x[i] *= y[i];
  }
  fft(x, true);
  std::vector<T> ret(n);
  for (std::size_t i = 0; i < n; ++i) {
    ret[i] = std::round(x[i].real());
  }
  return ret;
}

void solve() {
  std::string s;
  std::cin >> s;

  const auto n = int(s.size());
  std::vector<int> as(n), bs(n);
  for (int i = 0; i < n; ++i) {
    as[i] += s[i] - '0';
    bs[n - i - 1] += s[i] - '0';
  }

  auto c = multiple(as, bs);
  for (int i = n; i < 2 * n - 1; ++i) {
    std::cout << c[i] << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}