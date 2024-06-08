#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.hpp"
#else
#define dbg(...) 42
#endif

constexpr void scan(auto&&... args) noexcept { (std::cin >> ... >> args); }
constexpr void print(auto&&... args) noexcept { ((std::cout << args << ' '), ...); }
constexpr void println(auto&&... args) noexcept { print(std::forward<decltype(args)>(args)...); std::cout << '\n'; }

template <int P> class Z {
  int x = 0;
public:
  static_assert(P <= std::numeric_limits<int>::max() / 2);

  constexpr Z() noexcept = default;
  constexpr Z(long long y) noexcept : x(norm(y)) { }

  static constexpr int getMod() noexcept { return P; }
  [[nodiscard]] constexpr static int norm(long long y) noexcept {
    if (y < -getMod() || y >= getMod()) {
      y %= getMod();
    }
    if (y < 0) {
      y += getMod();
    }
    return static_cast<int>(y);
  }

  [[nodiscard]] constexpr int val() const noexcept { return x; }
  constexpr explicit operator int() const noexcept { return x; }

  constexpr Z operator-() const noexcept {
    return {getMod() - x};
  }
  [[nodiscard]] constexpr Z inverse() const noexcept {
    return pow(getMod() - 2);
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
    x = norm(x * 1LL * other.val());
    return *this;
  }
  constexpr Z& operator/=(Z other) noexcept {
    return *this *= other.inverse();
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
    return {x + other.val()};
  }
  constexpr Z operator-(Z other) const noexcept {
    return {x - other.val()};
  }
  constexpr Z operator*(Z other) const noexcept {
    return {x * 1LL * other.val()};
  }
  constexpr Z operator/(Z other) const noexcept {
    return other.inverse() * x;
  }

  constexpr bool operator==(Z other) const noexcept {
    return val() == other.val();
  }
  constexpr bool operator!=(Z other) const noexcept {
    return val() != other.val();
  }

  [[nodiscard]] Z pow(long long n) const {
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
    long long y;
    in >> y;
    z = Z{y};
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const Z& z) {
    return out << z.val();
  }
};

constexpr int Mod = 998244353;
using Mint = Z<Mod>;

void solve() {
  int n, m;
  scan(n, m);
  std::vector<int> as(m), bs(m);
  for (int i = 0; i < m; ++i) {
    scan(as[i], bs[i]);
  }

  Mint ret{};
  println(ret);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}