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
  int k;
  std::array<int, 26> cnt{};
  scan(k);
  for (auto&& c : cnt) {
    scan(c);
  }

  std::vector<Mint> fact(k + 1), ifact(k + 1);
  fact[0] = 1;
  for (int i = 1; i <= k; ++i) {
    fact[i] = fact[i - 1] * i;
  }
  ifact[k] = Mint(1) / fact[k];
  for (int i = k - 1; i >= 0; --i) {
    ifact[i] = ifact[i + 1] * (i + 1);
  }

  std::vector<Mint> dp(k + 1);
  dp[0] = 1;
  for (int c = 0; c < 26; ++c) {
    std::vector<Mint> ndp = dp;
    for (int len = 0; len < k; ++len) {
      for (int x = 1; x <= cnt[c] && len + x <= k; ++x) {
        ndp[len + x] += dp[len] * ifact[len] * fact[len + x] * ifact[x];
      }
    }
    std::swap(dp, ndp);
  }
  Mint tot{};
  for (int len = 1; len <= k; ++len) {
    tot += dp[len];
  }
  println(tot);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve();
}