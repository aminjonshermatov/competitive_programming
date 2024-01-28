#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define dbg(...) 42
#endif

using i64 = int64_t;

template <typename T> T power(T a, i64 b) noexcept {
  T res = 1;
  for (; b > 0; b >>= 1, a *= a) {
    if (b & 1) {
      res *= a;
    }
  }
  return res;
}

template <i64 P> struct Z {
  i64 x = 0;
  constexpr Z() noexcept = default;
  constexpr Z(i64 x) noexcept : x(norm(x % getMod())) { }

  static i64 getMod() noexcept { return P; }
  [[nodiscard]] constexpr i64 norm(i64 y) const noexcept {
    if (y < 0) {
      y += getMod();
    }
    if (y >= getMod()) {
      y -= getMod();
    }
    return y;
  }

  [[nodiscard]] constexpr i64 val() const noexcept { return x; }
  constexpr explicit operator i64() const noexcept { return x; }

  constexpr Z operator-() const noexcept {
    return Z(getMod() - x);
  }
  [[nodiscard]] constexpr Z inv() const noexcept {
    return power(*this, getMod() - 2);
  }

  constexpr Z& operator+=(Z other) noexcept {
    x = norm(x + other.val());
    return *this;
  }
  constexpr Z& operator-=(Z other) noexcept {
    x = norm(x - other.val());
    return *this;
  }
  constexpr Z& operator*=(Z other) noexcept {
    x = norm((x * other.val()) % getMod());
    return *this;
  }
  constexpr Z& operator/=(Z other) noexcept {
    return *this *= other.inv();
  }

  constexpr Z operator+(Z other) const noexcept {
    return {x + other.val()};
  }
  constexpr Z operator-(Z other) const noexcept {
    return {norm(x - other.val())};
  }
  constexpr Z operator*(Z other) const noexcept {
    return {norm((x * other.val()) % getMod())};
  }
  constexpr Z operator/(Z other) const noexcept {
    return {other.inv() * x};
  }

  constexpr bool operator==(Z other) const noexcept {
    return val() == other.val();
  }
  constexpr bool operator!=(Z other) const noexcept {
    return val() != other.val();
  }

  template<i64 Mod> friend std::istream& operator>>(std::istream &in, Z<Mod> &z) {
    i64 y;
    in >> y;
    z = Z{y};
    return in;
  }
  template<i64 Mod> friend std::ostream& operator<<(std::ostream &out, const Z<Mod> &z) {
    return out << z.val();
  }
};

constexpr i64 Mod = 1e9 + 7;
using Mint = Z<Mod>;

void solve() {
  int H, W, n;
  std::cin >> H >> W >> n;
  std::vector<int> R(n + 2), C(n + 2);
  R[0] = C[0] = 1;
  for (int i = 1; i <= n; ++i) {
    std::cin >> R[i] >> C[i];
  }
  R[n + 1] = H, C[n + 1] = W;

  std::vector<Mint> fact(H + W + 1), ifact(H + W + 1);
  fact[0] = ifact[0] = 1;
  for (int i = 1; i <= H + W; ++i) {
    fact[i] = fact[i - 1] * i;
    ifact[i] = ifact[i - 1] / i;
  }
  auto nCr = [&fact, &ifact](int n, int r) {
    assert(r <= n);
    return fact[n] * ifact[n - r] * ifact[r];
  };
  std::vector<int> ord(n + 2);
  std::iota(ord.begin(), ord.end(), 0);
  std::ranges::sort(ord, [&](int i, int j) {
    return R[i] + C[i] < R[j] + C[j];
  });

  std::vector<Mint> dp(n + 2);
  for (auto i : ord) {
    dp[i] = nCr(R[i] + C[i] - 2, R[i] - 1);
    for (int j = 1; j <= n + 1; ++j) {
      if (i != j && R[j] <= R[i] && C[j] <= C[i]) {
        dp[i] -= nCr(R[i] - R[j] + C[i] - C[j], R[i] - R[j]) * dp[j];
      }
    }
  }
  std::cout << dp[n + 1] << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}
