//
// Created by aminjon on 1/1/23.
//
#include <bits/stdc++.h>

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

constexpr i64 Mod = 998244353;
using Mint = Z<Mod>;
