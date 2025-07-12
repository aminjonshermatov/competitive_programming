#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void Scan(auto&& ... args) noexcept { (std::cin >> ... >> args); }
constexpr void Print(auto&& ... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void Println(auto&& ... args) noexcept { Print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

int64_t Slow(const int64_t n) {
  int64_t tot = 0;
  for (int64_t a = 3; a <= n; ++a) {
    for (int64_t b = 1; b < a; ++b) {
      for (int64_t c = 1; c < b; ++c) {
        tot += a % b == c;
      }
    }
  }
  return tot;
}

int64_t Fast1(const int64_t n) {
  int64_t tot = 0;
  for (int64_t a = 3; a <= n; ++a) {
    tot += a - 1;
    for (int b = 1; b < a; ++b) {
      tot -= a % b == 0;
    }
  }
  return tot;
}

template <int P>
class Z {
 public:
  static_assert(0 < P && P <= std::numeric_limits<int>::max() / 2);

  constexpr Z() noexcept = default;
  constexpr Z(int64_t y) noexcept : X_(Norm(y)) { }

  static constexpr int GetMod() noexcept { return P; }

  [[nodiscard]] constexpr static int Norm(int64_t y) noexcept {
    if (y < -GetMod() || y >= GetMod()) {
      y %= GetMod();
    }
    if (y < 0) {
      y += GetMod();
    }
    return static_cast<int>(y);
  }

  [[nodiscard]] constexpr int Val() const noexcept { return X_; }
  constexpr explicit operator int() const noexcept { return X_; }

  constexpr Z operator-() const noexcept {
    return {GetMod() - X_};
  }
  [[nodiscard]] constexpr Z Inverse() const noexcept {
    return Pow(GetMod() - 2);
  }

  constexpr Z& operator+=(Z other) noexcept {
    X_ = Norm(X_ + other.Val());
    return *this;
  }
  constexpr Z& operator-=(Z other) noexcept {
    X_ = Norm(X_ - other.Val());
    return *this;
  }
  constexpr Z& operator*=(Z other) noexcept {
    X_ = Norm(X_ * 1LL * other.Val());
    return *this;
  }
  constexpr Z& operator/=(Z other) noexcept {
    return *this *= other.Inverse();
  }

  constexpr Z& operator++() noexcept {
    operator+=(1);
    return *this;
  }
  constexpr Z operator++(int) const noexcept {
    auto z = *this;
    ++(*this);
    return z;
  }
  constexpr Z& operator--() noexcept {
    operator-=(1);
    return *this;
  }
  constexpr Z operator--(int) const noexcept {
    auto z = *this;
    --(*this);
    return z;
  }

  constexpr Z operator+(Z other) const noexcept {
    return {X_ + other.Val()};
  }
  constexpr Z operator-(Z other) const noexcept {
    return {X_ - other.Val()};
  }
  constexpr Z operator*(Z other) const noexcept {
    return {X_ * 1LL * other.Val()};
  }
  constexpr Z operator/(Z other) const noexcept {
    return other.Inverse() * X_;
  }

  constexpr bool operator==(Z other) const noexcept {
    return Val() == other.Val();
  }
  constexpr bool operator!=(Z other) const noexcept {
    return Val() != other.Val();
  }

  [[nodiscard]] Z Pow(int64_t n) const {
    auto ret = Z(*this);
    Z res = 1;
    for (; n > 0; n >>= 1, ret *= ret) {
      if (n % 2 == 1) {
        res *= ret;
      }
    }
    return res;
  }

  friend std::istream& operator>>(std::istream& in, Z& z) {
    int64_t y;
    in >> y;
    z = Z{y};
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const Z& z) {
    return out << z.Val();
  }

 private:
  int X_{0};
};

constexpr int kMod = 998244353;
using Mint = Z<kMod>;

Mint Fast2(const int64_t n) {
  auto tot = Mint(n) * (n + 1) / 2;
  for (int64_t d = 1; d <= n;) {
    const auto x = n / d;
    const auto lst = n / x;
    tot -= Mint(lst - d + 1) * x;
    d = lst + 1;
  }
  return tot;
}

void Solve() {
  int64_t n;
  Scan(n);

  Println(Fast2(n));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Solve();
}
